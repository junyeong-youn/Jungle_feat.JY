#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include "mm.h"
#include "memlib.h"
team_t team = {
    /* Team name */
    "3-1",
    /* First member's full name */
    "empty",
    /* First member's email address */
    "emptynought@kakao.com",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};
// ------------------- Edit Start ------------------- //
/* find_fit strategy */
#define NEXT_FITx
#define TESTx
/* Basic constants and macros */
#define WSIZE       4       /* Word and header/footer size (bytes) */
#define DSIZE       8       /* Double word size (bytes) */
#define MINBLOCK    16
#define CHUNKSIZE   (1<<12) /* Extend heap by this amount (bytes) */     
#define MAX(x, y) ((x) > (y)? (x) : (y))
#define PACK(size, alloc)   ((size) | (alloc))
#define ALIGN(size) (((size) + (DSIZE-1)) & ~0x7)
#define GET(p)      (*(unsigned int *)(p))
#define PUT(p, val) (*(unsigned int *)(p) = (val))
#define GET_SIZE(p)  (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)
#define HDRP(bp)    ((char *)(bp) - WSIZE)            
#define FTRP(bp)    ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)     
#define PREV_BLKP(bp) ((void *)(bp) - GET_SIZE(HDRP(bp) - WSIZE))
#define NEXT_BLKP(bp) ((void *)(bp) + GET_SIZE(HDRP(bp)))
#define PREDP(bp)    (*(char **)(bp))
#define SUCCP(bp)    (*(char **)(bp + WSIZE))
static void *coalesce(void *bp);
static void *extend_heap(size_t words);
static void *find_fit(size_t asize);
static void place(void *bp, size_t asize);
static void byeBlock(void *bp);
void* heap_listp;           /* ���� �� ó�� ��ġ�� ����Ű�� �ִ� ������, find_fit�� �ϴ� �������� �ȴ�*/
void* free_listp;           /* ���� ����� ���� ��ġ�� ����Ű�� �ִ� ������ */
#ifdef NEXT_FIT
void* next_fitp;           /* Next_fit ��� �� Ž�� ���� ��ġ�� ������ ������ */
#endif 
// CLEAR
int mm_init(void)
{
    /* Create the initial empty heap */
    /* 4 ���� ũ�� ��ŭ�� �߰��Ѵ�, Alignment padding, Prologue header, Prologue footer, Epilogue header�� �� ���� Ȯ�� */
#ifdef TEST
    if ((heap_listp = mem_sbrk(4 * WSIZE)) == (void *)-1)
        return -1; 
    PUT(heap_listp, 0);                                       
    // Root Block
    PUT(heap_listp + (1*WSIZE), PACK(MINBLOCK, 1));           // Prologue header 
    PUT(heap_listp + (2*WSIZE), NULL);                   // Space for next pointer 
    PUT(heap_listp + (3*WSIZE), NULL);                   // Space for prev pointer 
    PUT(heap_listp + (4*WSIZE), PACK(MINBLOCK, 1));           // Free block footer 
    PUT(heap_listp + (5*WSIZE), PACK(0, 1));                  // Epilogue header 
    // free_listp = heap_listp + (DSIZE);
    if (free_listp = extend_heap(CHUNKSIZE/WSIZE) == NULL){
        return -1;
    }
#else
    if((heap_listp = mem_sbrk(4*WSIZE)) == (void *)-1)
        return -1;
    PUT(heap_listp, 0);                             /* Alignment padding */
    PUT(heap_listp + (1*WSIZE), PACK(DSIZE, 1));    /* Prologue header */
    PUT(heap_listp + (2*WSIZE), PACK(DSIZE, 1));    /* Prologue footer */
    PUT(heap_listp + (3*WSIZE), PACK(0, 1));        /* Epilogue header */
    free_listp = NULL;
    if (extend_heap(CHUNKSIZE/WSIZE) == NULL){
        return -1;
    }
#endif
    #ifdef NEXT_FIT
        next_fitp = free_listp;
    #endif
    return 0;
}
// CLEAR
static void *extend_heap(size_t words)
{
    char *bp;
    size_t asize;
    asize = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;
    if(asize < MINBLOCK)
        asize = MINBLOCK;
    /* mem_sbrk�� ���� break�� �ڷ� �Ű� �� ������ size��ŭ Ű��� */
    if ((long)(bp = mem_sbrk(asize)) == -1)
        return NULL;
    /* Initialize free block header/footer and the epilogue header */
    /* Ȯ���� ũ��� ���� ��� header�� footer�� �߰��Ͽ� ���� ������� ������ش� */
    PUT(HDRP(bp), PACK(asize, 0));           /* Free block header */
    PUT(FTRP(bp), PACK(asize, 0));           /* Free block footer */
    /* ũ�⸦ Ȯ���ϸ鼭 ������� epilogue header�� �߰��� ���� �ڿ� ������ش� */
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));   /* New epilogue header */
    /* Coalesce if the previous block was free */
    /* �� ������ Ȯ���ϸ鼭 Ȯ�� ���� ����� ���� �����̾��ٸ� �����ش� */
    return coalesce(bp);
}
// CLEAR
void *mm_malloc(size_t size)
{
    size_t asize;       /* Adjusted block size */
    size_t extendsize;  /* Amount to extend heap if no fit */
    char *bp;
    if (size == 0)
        return NULL;
    // asize = MAX(ALIGN(size) + DSIZE, MINBLOCK);
    if (size <= DSIZE) {
        asize = MINBLOCK;       // ����� Ǫ�͸� ����ؾ� �Ѵ�
    }
    else{
        asize = DSIZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE);
    }
    if ((bp = find_fit(asize)) != NULL) {
        /* ������ ������ �� ��ġ�� asize ��ŭ�� ���� �Ҵ� �� ������ ��ȯ*/
        place(bp, asize);
        return bp;
    }
    /* No fit found. Get more memory and place the block */
    /* ���� ������ ������ ã�� ���ߴٸ� �� �߰� �⺻ ������ CHUNKSIZE�� �ʿ��� ũ���� asize�� Ȯ���ؼ�
     * �� ū ���� Ȯ���� ũ��� ���Ѵ� */
    extendsize = MAX(asize, CHUNKSIZE);
    /* extendsize ��ŭ extend_heap ���� �� ������ �߰��ϰ� �����͸� ��ȯ */
    if ((bp = extend_heap(extendsize/WSIZE)) == NULL)
        return NULL;
    /* ��ȯ�� ������ ��ġ�� asize ��ŭ�� ũ�⸦ �Ҵ� */
    place(bp, asize);
    return bp;
}
static void *find_fit(size_t asize){
    /* Next-fit search */
#ifdef NEXT_FIT
    void *start_ptr = next_fitp;
    for(; next_fitp != NULL; next_fitp = SUCCP(next_fitp))
        if (asize <= GET_SIZE(HDRP(next_fitp)))
	        return next_fitp;
    if(free_listp != NULL){
        for(next_fitp = free_listp; next_fitp != start_ptr; next_fitp = SUCCP(next_fitp))
            if (asize <= GET_SIZE(HDRP(next_fitp)))
                return next_fitp;
    }
#else
    void *bp;
    for (bp = free_listp; bp != NULL; bp = SUCCP(bp)){
        if (asize <= GET_SIZE(HDRP(bp))) {
            return bp;
        }
    }
#endif
    /* ������ ������ ������ NULL�� �����Ѵ� */
    return NULL; /* No fit */
}
// CLEAR
static void place(void *bp, size_t asize){
    /* �Ҵ簡���� ���� ��ü ũ�� */
    size_t csize = GET_SIZE(HDRP(bp));
    /* �Ҵ簡���� ������ ��ü ũ��� �Ҵ��Ϸ��� ������ ũ���� ���� 16���� ũ��
     * ������ ũ�Ⱑ �ּ��� ��� ��� �Ҵ��� �����ϹǷ� ������ �и��Ѵ� */
    if ((csize - asize) >= (MINBLOCK)) {
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        byeBlock(bp);
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(csize - asize, 0));
        PUT(FTRP(bp), PACK(csize - asize, 0));
        coalesce(bp);
    }
    /* ���̰� 16���� ���� ���� �Ҵ��� �����ϱ� ���� ��� ������ ����ؾ� �ϹǷ� ������ ��� ä��� */
    else {
        PUT(HDRP(bp), PACK(csize, 1));
        PUT(FTRP(bp), PACK(csize, 1));
        byeBlock(bp);
    }
}
void mm_free(void *bp)
{
    if(!bp) return;
    /* ��ȯ ��û�� ������ ũ�⸦ Ȯ�� */
    size_t size = GET_SIZE(HDRP(bp));
    /* header�� footer�� ���� ���� ǥ�ø� �Ѵ� */
    PUT(HDRP(bp), PACK(size, 0));           /* Free block header */
    PUT(FTRP(bp), PACK(size, 0));           /* Free block footer */
    /* ���� ������ ������ְ� �� �� ������ Ȯ���ؼ� ��ĥ �� ������ ��ģ�� */
    coalesce(bp);
}
static void *coalesce(void *bp)
{
    // ���� ��� �Ҵ� ����, ���� ��� �Ҵ� ����, ���� ����� ũ�� Ȯ�� */
    #ifdef TEST
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    int check = 0;
    // if(PREV_BLKP(bp) == bp && check <= 0){
    //     printf("free_listp :%p\n", free_listp);
    //     printf("PREV_BLKP(bp) :%p, bp : %p\n", PREV_BLKP(bp), bp);
    //     printf("\n");
    //     check += 1;
    // }
    #else
    // size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp))) || PREV_BLKP(bp) == bp;
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    #endif
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));
    if(prev_alloc && next_alloc){                   /* Case 1 */
    }
    /* ���� ����� ���� ����̸� ���� ��ϰ� ��ģ�� */
    else if (prev_alloc && !next_alloc) {           /* Case 2 */
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        byeBlock(NEXT_BLKP(bp));
        PUT(HDRP(bp), PACK(size, 0));      
        PUT(FTRP(bp), PACK(size, 0));
    }
    else if (!prev_alloc && next_alloc) {           /* Case 3 */
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        bp = PREV_BLKP(bp);
        byeBlock(bp);
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));            
    }
    /* ���� ��ϰ� ���� ����� �������̸� �� ��� ��ο� ��ģ�� */
    else {                                              /* Case 4 */
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(HDRP(NEXT_BLKP(bp)));
        byeBlock(PREV_BLKP(bp)); 
        byeBlock(NEXT_BLKP(bp)); 
        bp = PREV_BLKP(bp);
        PUT(HDRP(bp), PACK(size, 0));               
        PUT(FTRP(bp), PACK(size, 0));          
    }
    #ifdef TEST
    SUCCP(bp) = free_listp;
    PREDP(free_listp) = bp;
    PREDP(bp) = NULL;
    free_listp = bp;
    #else
    if (free_listp == NULL){
        free_listp = bp;
        PREDP(bp) = NULL;
        SUCCP(bp) = NULL;
    }
    else{
        SUCCP(bp) = free_listp;
        PREDP(free_listp) = bp;
        PREDP(bp) = NULL;
        free_listp = bp;
    }
    #endif
#ifdef NEXT_FIT
    if (next_fitp > bp && next_fitp < NEXT_BLKP(bp))
    next_fitp = bp;
#endif
    return bp;
}
// CREAR
void *mm_realloc(void *ptr, size_t size)
{
    /* ���Ҵ��� ��û�� ũ�Ⱑ 0�̸� ������ ����޶�� �ǹ��̹Ƿ� �׳� free�ϰ� �����Ѵ� */
    if (size == 0){
        mm_free(ptr);
        return 0;
    }
    /* ���� NULL �� �����ͷ� ��û�� �Ѵٸ� melloc�� ������ ������ �Ѵ� */
    if (ptr == NULL){
        return mm_malloc(size);
    }
    /* ���ο� ������ �Ҵ� �޾Ƽ� �� ������ �����͸� ��ȯ�޴´� */
    void *newptr = mm_malloc(size);
    /* ��ȯ ���� �����Ͱ� NULL �̸� �� ��ü ��������
     * �Ҵ� ������ ������ ���ٴ� �̾߱��̹Ƿ� 0�� ��ȯ�Ѵ� */
    if (newptr == NULL){
        return 0;
    }
    /* �Ҵ� ������ ������ ������
     * ���� ������ ũ�⸦ Ȯ���ϰ�*/
    size_t oldsize = GET_SIZE(HDRP(ptr));
    /* ���� ������ ũ�Ⱑ �Űܰ� ������ ũ�⺸�� ũ�ٸ�
     * �ű� �� �ִ� ũ��� �����Ѵ� */
    if (size < oldsize){
        oldsize = size;
    }
    /* ���ο� ��ġ�� ���� ��ġ�� �ִ� oldsize ��ŭ ����� */
    memcpy(newptr, ptr, oldsize);
    /* ���� ������ ��ȯ�ϰ� ���ο� ��ġ �����͸� ��ȯ�Ѵ� */
    mm_free(ptr);
    return newptr;
}
#ifdef TEST
static void byeBlock(void *bp){
    if(PREDP(bp) == NULL){
        free_listp = SUCCP(bp);
    }
    else{
        SUCCP(PREDP(bp)) = SUCCP(bp);
    }
    if(SUCCP(bp) != NULL)
        PREDP(SUCCP(bp)) = PREDP(bp);
}
#else
static void byeBlock(void *bp){
    if(PREDP(bp) == NULL){
        free_listp = SUCCP(bp);
    }
    else{
        SUCCP(PREDP(bp)) = SUCCP(bp);
    }
    if(SUCCP(bp) != NULL)
        PREDP(SUCCP(bp)) = PREDP(bp);
}
#endif