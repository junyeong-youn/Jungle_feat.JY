#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "mm.h"
#include "memlib.h"

team_t team = {
    /* Team name */
    "j2team",
    /* First member's full name */
    "Smith",
    /* First member's email address */
    "22@naver.com",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""};

#define WSIZE 4
#define DSIZE 8
#define MAXFREESIZE 16
#define CHUNKSIZE (1 << 12) //2의 12승

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define ALIGN(p) (((size_t)(p) + (7)) & ~0x7)
#define PACK(size, alloc) ((size) | (alloc)) //size와alloc을 합친다(size자체가 8단위라서 000이라 상관없음)

#define GET(p) (*(unsigned int *)(p))              //p를 받는다
#define PUT(p, val) (*(unsigned int *)(p) = (val)) //value값을 넣는다

#define GET_SIZE(p) (GET(p) & ~0x7) // 0x 는 16진수를 뜻함. 00000007이니깐 반대면 FFFFFFF8이 된다.
#define GET_ALLOC(p) (GET(p) & 0x1) //0001

#define HDRP(bp) ((char *)(bp)-WSIZE)
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(((char *)(bp)-WSIZE)))
#define PREV_BLKP(bp) ((char *)(bp)-GET_SIZE(((char *)(bp)-DSIZE)))

#define NEXT_FREE(bp) (*(void)**)(bp + WSIZE))
#define PREV_FREE(bp) (*(void)**)(bp))

static char *heap_listp;
static char *free_listp;

extern int mm_init(void);
extern void *mm_malloc(size_t size);
extern void mm_free(void *ptr);
static void *coalesce(void *bp);
static void *extend_heap(size_t words);
static void *find_fit(size_t asize);
static void place(void *bp, size_t asize);
void *mm_realloc(void *bp, size_t size);

int mm_init(void)
{
    if ((heap_listp = mem_sbrk(2 * WSIZE + MAXFREESIZE)) == (void *)-1)
        return -1;
    PUT(heap_listp, 1);
    PUT(heap_listp + (1 * WSIZE), PACK(MAXFREESIZE, 1));
    PUT(heap_listp + (2 * WSIZE), NULL);
    PUT(heap_listp + (3 * WSIZE), NULL);
    PUT(heap_listp + (4 * WSIZE), PACK(MAXFREESIZE, 1));
    PUT(heap_listp + (5 * WSIZE), PACK(0, 1));

    free_listp = heap_listp + 2*WSIZE;

    NEXT_FREE(free_listp) = NULL;

    if (extend_heap(CHUNKSIZE / WSIZE) == NULL)
        return -1;

    return 0;
}

static void *extend_heap(size_t words)
{
    char *bp;
    size_t size;
    size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;

    if ((long)(bp = mem_sbrk(size)) == -1)
        return NULL;

    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));

    return coalesce(bp);
}

void mm_free(void *bp)
{
    size_t size = GET_SIZE(HDRP(bp));

    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    coalesce(bp);
}

static void *coalesce(void *bp)
{
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    if (prev_alloc && next_alloc) //앞에 얼록 중간 프리 뒤에 얼록
    {
        if (NEXT_FREE(free_listp) == NULL)
        {
            NEXT_FREE(free_listp) = bp;
            NEXT_FREE(bp) = NULL;
            PREV_FREE(bp) = free_listp;
        }
        else
        {
            NEXT_FREE(bp) = NEXT_FREE(free_listp);
            NEXT_FREE(free_listp) = bp;
            PREV_FREE(bp) = free_listp;
            PREV_FREE(NEXT_FREE(bp)) = bp;
            return bp;
        }
    }
    else if (prev_alloc && !next_alloc) //case2 앞에 얼록 중간 프리 뒤에 프리
    {
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        if (NEXT_FREE(NEXT_BLKP(bp)) != NULL)
        { //2-1-1 NEXT==EXIST
            NEXT_FREE(PREV_FREE(NEXT_BLKP(bp))) = NEXT_FREE(NEXT_BLKP(bp));
            PREV_FREE(NEXT_FREE(NEXT_BLKP(bp))) = PREV_FREE(NEXT_BLKP(bp)); //next bp 에서 prev free next free를 비교해서 현재 next bp를 빼고 연결 해준다. 2번
            PREV_FREE(NEXT_BLKP(bp)) = NULL;
            NEXT_FREE(NEXT_BLKP(bp)) = NULL;
            PUT(HDRP(bp), PACK(size , 0));
            PUT(FTRP(bp), PACK(size , 0));//free가 늘어나니까 프리의 헤더의 사이즈 바꾸고 푸터 위치랑 사이즈를 바꾼다.
            NEXT_FREE(bp) = NEXT_FREE(free_listp);
            NEXT_FREE(free_listp) = bp;//NEXT_FREE(root)을 bp에 연결하고 ROOT에 BP를 연결
            PREV_FREE(bp)=free_listp; //bp의 NEXT의 PREV를 BP로 바꿈
            PREV_FREE((NEXT_FREE(bp))) = bp;//BP의 PREV를 ROOT로 바꿈
        }
        else
        { //2-1-2 NEXT==NULL 
            PREV_FREE(NEXT_BLKP(bp)) = NULL;
            PUT(HDRP(bp), PACK(size , 0));
            PUT(FTRP(bp), PACK(size , 0));//free가 늘어나니까 프리의 헤더의 사이즈 바꾸고 푸터 위치랑 사이즈를 바꾼다.
            NEXT_FREE(bp) = NEXT_FREE(free_listp);
            NEXT_FREE(free_listp) = bp;//NEXT_FREE(root)을 bp에 연결하고 ROOT에 BP를 연결
            PREV_FREE(bp)=free_listp; //bp의 NEXT의 PREV를 BP로 바꿈
            PREV_FREE((NEXT_FREE(bp))) = bp;//BP의 PREV를 ROOT로 바꿈
        }
        
    }
    else if (!prev_alloc && next_alloc) // 앞에 프리 중간 프리 뒤에 얼록
    {
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        if (NEXT_FREE(PREV_BLKP(bp)) != NULL){ //전bp의 NEXTFREE 값이 있으면
            NEXT_FREE(PREV_FREE(PREV_BLKP(bp))) = NEXT_FREE(PREV_BLKP(bp));
            PREV_FREE(NEXT_FREE(PREV_BLKP(bp))) = PREV_FREE(PREV_BLKP(bp));
            NEXT_FREE(NEXT_BLKP(bp)) = NULL;
            PREV_FREE(NEXT_BLKP(bp)) = NULL;
            PUT(FTRP(bp), PACK(size, 0));
            PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
            bp = PREV_BLKP(bp);

            NEXT_FREE(bp) = NEXT_FREE(free_listp);
            NEXT_FREE(free_listp) = bp;//NEXT_FREE(root)을 bp에 연결하고 ROOT에 BP를 연결
            PREV_FREE(bp)=free_listp; //bp의 NEXT의 PREV를 BP로 바꿈
            PREV_FREE((NEXT_FREE(bp))) = bp;//BP의 PREV를 ROOT로 바꿈
        }
        else{ // 전bp의 NEXTFREE 값이 널이면
            PREV_FREE(NEXT_BLKP(bp)) = NULL;
            PUT(FTRP(bp), PACK(size, 0));
            PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
            bp = PREV_BLKP(bp);

            NEXT_FREE(bp) = NEXT_FREE(free_listp);
            NEXT_FREE(free_listp) = bp;//NEXT_FREE(root)을 bp에 연결하고 ROOT에 BP를 연결
            PREV_FREE(bp)=free_listp; //bp의 NEXT의 PREV를 BP로 바꿈
            PREV_FREE((NEXT_FREE(bp))) = bp;//BP의 PREV를 ROOT로 바꿈

        }
    }
    else //다 프리일때
    {
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(FTRP(NEXT_BLKP(bp)));
        if(NEXT_FREE(NEXT_BLKP(bp)) != NULL && NEXT_FREE(PREV_BLKP(bp)) != NULL){// 둘다 NEXTFREE값이 있으면
            PREV_FREE(NEXT_BLKP(bp)) = NULL;
            PREV_FREE(PREV_BLKP(bp)) = NULL;
            PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
            PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
            bp = PREV_BLKP(bp);

            NEXT_FREE(bp) = NEXT_FREE(free_listp);
            NEXT_FREE(free_listp) = bp;//NEXT_FREE(root)을 bp에 연결하고 ROOT에 BP를 연결
            PREV_FREE(bp)=free_listp; //bp의 NEXT의 PREV를 BP로 바꿈
            PREV_FREE((NEXT_FREE(bp))) = bp;//BP의 PREV를 ROOT로 바꿈


        }
        else if (NEXT_FREE(NEXT_BLKP(bp)) != NULL){ //후bp의 NEXTFREE 값이 있으면
            PREV_FREE(NEXT_BLKP(bp)) = NULL;
            NEXT_FREE(PREV_FREE(PREV_BLKP(bp))) = NEXT_FREE(PREV_BLKP(bp));
            PREV_FREE(NEXT_FREE(PREV_BLKP(bp))) = PREV_FREE(PREV_BLKP(bp));
            NEXT_FREE(PREV_BLKP(bp)) = NULL;
            PREV_FREE(PREV_BLKP(bp)) = NULL;
            PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
            PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
            bp = PREV_BLKP(bp);

            NEXT_FREE(bp) = NEXT_FREE(free_listp);
            NEXT_FREE(free_listp) = bp;//NEXT_FREE(root)을 bp에 연결하고 ROOT에 BP를 연결
            PREV_FREE(bp)=free_listp; //bp의 NEXT의 PREV를 BP로 바꿈
            PREV_FREE((NEXT_FREE(bp))) = bp;//BP의 PREV를 ROOT로 바꿈
        
        }
        else if (NEXT_FREE(PREV_BLKP(bp)) != NULL){ //전bp의 NEXTFREE 값이 있으면
            NEXT_FREE(PREV_FREE(NEXT_BLKP(bp))) = NEXT_FREE(NEXT_BLKP(bp));
            PREV_FREE(NEXT_FREE(NEXT_BLKP(bp))) = PREV_FREE(NEXT_BLKP(bp));
            NEXT_FREE(NEXT_BLKP(bp)) = NULL;
            PREV_FREE(NEXT_BLKP(bp)) = NULL;
            PREV_FREE(PREV_BLKP(bp)) = NULL;
            PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
            PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
            bp = PREV_BLKP(bp);

            NEXT_FREE(bp) = NEXT_FREE(free_listp);
            NEXT_FREE(free_listp) = bp;//NEXT_FREE(root)을 bp에 연결하고 ROOT에 BP를 연결
            PREV_FREE(bp)=free_listp; //bp의 NEXT의 PREV를 BP로 바꿈
            PREV_FREE((NEXT_FREE(bp))) = bp;//BP의 PREV를 ROOT로 바꿈
        
        }
        else{
            NEXT_FREE(PREV_FREE(NEXT_BLKP(bp))) = NEXT_FREE(NEXT_BLKP(bp));
            PREV_FREE(NEXT_FREE(NEXT_BLKP(bp))) = PREV_FREE(NEXT_BLKP(bp));
            NEXT_FREE(NEXT_BLKP(bp)) = NULL;
            PREV_FREE(NEXT_BLKP(bp)) = NULL;
            NEXT_FREE(PREV_FREE(PREV_BLKP(bp))) = NEXT_FREE(PREV_BLKP(bp));
            PREV_FREE(NEXT_FREE(PREV_BLKP(bp))) = PREV_FREE(PREV_BLKP(bp));
            NEXT_FREE(PREV_BLKP(bp)) = NULL;
            PREV_FREE(PREV_BLKP(bp)) = NULL;
            PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
            PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
            bp = PREV_BLKP(bp);

            NEXT_FREE(bp) = NEXT_FREE(free_listp);
            NEXT_FREE(free_listp) = bp;//NEXT_FREE(root)을 bp에 연결하고 ROOT에 BP를 연결
            PREV_FREE(bp)=free_listp; //bp의 NEXT의 PREV를 BP로 바꿈
            PREV_FREE((NEXT_FREE(bp))) = bp;//BP의 PREV를 ROOT로 바꿈
        }
        
    }
    return bp;
}



    void *mm_malloc(size_t size)
{
    size_t asize;
    size_t extendsize;
    char *bp;

    if (heap_listp == 0){
        mm_init();
    }

    if (size == 0)
        return NULL;

    asize = MAX(ALIGN(size) + DSIZE, 4*WSIZE);

    if ((bp = find_fit(asize)) != NULL)
    {
        place(bp, asize);
        return bp;
    }

    extendsize = MAX(asize, CHUNKSIZE);
    if ((bp = extend_heap(extendsize / WSIZE)) == NULL)
        return NULL;
    place(bp, asize);
    return bp;
}

static void *find_fit(size_t asize)
{
    void *bp;

    for (bp = free_listp; GET_ALLOC(HDRP(bp)) == 0; bp = NEXT_FREE(bp))
    {
        if (asize <= GET_SIZE(HDRP(bp)))
        {
            return bp;
        }
    }
    return NULL;
}

static void place(void *bp, size_t asize)
{
    size_t csize = GET_SIZE(HDRP(bp));

    if ((csize - asize) >= (2 * DSIZE))
    {   
        PREV_FREE(NEXT_FREE(bp)) = PREV_FREE(bp);
        NEXT_FREE(PREV_FREE(bp)) = NEXT_FREE(bp);
        NEXT_FREE(bp) = NEXT_FREE(free_listp);
        NEXT_FREE(free_listp) = bp;//NEXT_FREE(root)을 bp에 연결하고 ROOT에 BP를 연결
        PREV_FREE(bp)=free_listp; //bp의 NEXT의 PREV를 BP로 바꿈
        PREV_FREE((NEXT_FREE(bp))) = bp;//BP의 PREV를 ROOT로 바꿈

        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(csize - asize, 0));
        PUT(FTRP(bp), PACK(csize - asize, 0));
        coalesce(bp);
    }
    else
    {
        PUT(FTRP(bp), 0);
        PUT(HDRP(bp), PACK(csize, 1));
        PUT(FTRP(bp), PACK(csize, 1));
        PREV_FREE(NEXT_FREE(bp)) = PREV_FREE(bp);
        NEXT_FREE(PREV_FREE(bp)) = NEXT_FREE(bp);

    }
}

void *mm_realloc(void *bp, size_t size)
{
    void *old_dp = bp;
    void *new_dp;
    size_t copySize;
    new_dp = mm_malloc(size);
    if (new_dp == NULL)
        return NULL;
    copySize = GET_SIZE((char *)old_dp - WSIZE);
    if (size < copySize)
        copySize = size;
    memcpy(new_dp, old_dp, copySize);
    mm_free(old_dp);
    return new_dp;
}