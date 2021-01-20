#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your identifying information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "nighthawk",
    /* First member's full name */
    "Jonathan Whitaker",
    /* First member's UID */
    "U0752100",
    /* Second member's full name (leave blank if none) */
    "Daniel Rushton",
    /* Second member's UID (leave blank if none) */
    "U0850493"
};



// CONSTANTS
#define ALIGNMENT         8         // memory alignment factor
#define WSIZE             4         // Size in bytes of a single word 
#define DSIZE             8         // Size in bytes of a double word
#define INITSIZE          16        // Initial size of free list before first free block added
#define MINBLOCKSIZE      16        /* Minmum size for a free block, includes 4 bytes for header/footer
                                       and space within the payload for two pointers to the prev and next
                                       free blocks */

// MACROS
/* NOTE: Most of these macros came from the text book on Page 857 (Fig. 9.43). We added the
 * NEXT_FREE and PREV_FREE macros to traverse the free list */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)
#define MAX(x, y) ((x) > (y)? (x) : (y))
#define PACK(size, alloc) ((size) | (alloc))
#define GET(p)        (*(size_t *)(p))
#define PUT(p, val)   (*(size_t *)(p) = (val))
#define GET_SIZE(p)  (GET(p) & ~0x1)
#define GET_ALLOC(p) (GET(p) & 0x1)
#define HDRP(bp)     ((void *)(bp) - WSIZE)
#define FTRP(bp)     ((void *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

#define NEXT_BLKP(bp) ((void *)(bp) + GET_SIZE(HDRP(bp)))
#define PREV_BLKP(bp) ((void *)(bp) - GET_SIZE(HDRP(bp) - WSIZE))
#define NEXT_FREE(bp)(*(void **)(bp))
#define PREV_FREE(bp)(*(void **)(bp + WSIZE))


// PROTOTYPES
static void *extend_heap(size_t words);
static void *find_fit(size_t size);
static void *coalesce(void *bp);
static void place(void *bp, size_t asize);
static void remove_freeblock(void *bp);
static void insertb(void* bp);
// static int mm_check();


// Private variables represeneting the heap and free list within the heap
static char *heap_listp = 0;  /* Points to the start of the heap */
static char *free_listp = 0;  /* Poitns to the frist free block */


/* 
 * mm_init - Initializes the heap like that shown below.
 *  ____________                                                    _____________
 * |  PROLOGUE  |                8+ bytes or 2 ptrs                |   EPILOGUE  |
 * |------------|------------|-----------|------------|------------|-------------|
 * |   HEADER   |   HEADER   |        PAYLOAD         |   FOOTER   |    HEADER   |
 * |------------|------------|-----------|------------|------------|-------------|
 * ^            ^            ^       
 * heap_listp   free_listp   bp 
 */
int mm_init(void)
{
  // Initialize the heap with freelist prologue/epilogoue and space for the
  // initial free block. (32 bytes total)
  if ((heap_listp = mem_sbrk(INITSIZE + MINBLOCKSIZE)) == (void *)-1)
      return -1; 
  PUT(heap_listp,             PACK(MINBLOCKSIZE, 1));           // Prologue header 
  PUT(heap_listp +    WSIZE,  PACK(MINBLOCKSIZE, 0));           // Free block header 

  PUT(heap_listp + (2*WSIZE), PACK(0,0));                       // Space for next pointer 
  PUT(heap_listp + (3*WSIZE), PACK(0,0));                       // Space for prev pointer 
  
  PUT(heap_listp + (4*WSIZE), PACK(MINBLOCKSIZE, 0));           // Free block footer 
  PUT(heap_listp + (5*WSIZE), PACK(0, 1));                      // Epilogue header 

  // Point free_list to the first header of the first free block
  free_listp = heap_listp + (WSIZE);

  return 0;
}

void *mm_malloc(size_t size)
{  
  
  if (size == 0)
      return NULL;

  size_t asize;       // Adjusted block size 
  size_t extendsize;  // Amount to extend heap by if no fit 
  char *bp;

  /* The size of the new block is equal to the size of the header and footer, plus
   * the size of the payload. Or MINBLOCKSIZE if the requested size is smaller.
   */
  asize = MAX(ALIGN(size) + DSIZE, MINBLOCKSIZE);
  
  // Search the free list for the fit 
  if ((bp = find_fit(asize))) {
    place(bp, asize);
    return bp;
  }

  // Otherwise, no fit was found. Grow the heap larger. 
  extendsize = MAX(asize, MINBLOCKSIZE);
  if ((bp = extend_heap(extendsize/WSIZE)) == NULL)
    return NULL;

  // Place the newly allocated block
  place(bp, asize);

  return bp;
}


void mm_free(void *bp)
{ 
  
  // Ignore spurious requests 
  if (!bp)
      return;

  size_t size = GET_SIZE(HDRP(bp));

  /* Set the header and footer allocated bits to 0, thus
   * freeing the block */
  PUT(HDRP(bp), PACK(size, 0));
  PUT(FTRP(bp), PACK(size, 0));

  // Coalesce to merge any free blocks and add them to the list 
  coalesce(bp);
}

void *mm_realloc(void *ptr, size_t size)
{
  // If ptr is NULL, realloc is equivalent to mm_malloc(size)
  if (ptr == NULL)
    return mm_malloc(size);

  // If size is equal to zero, realloc is equivalent to mm_free(ptr)
  if (size == 0) {
    mm_free(ptr);
    return NULL;
  }
    
  /* Otherwise, we assume ptr is not NULL and was returned by an earlier malloc or realloc call.
   * Get the size of the current payload */
  size_t asize = MAX(ALIGN(size) + DSIZE, MINBLOCKSIZE);
  size_t current_size = GET_SIZE(HDRP(ptr));

  void *bp;
  char *next = HDRP(NEXT_BLKP(ptr));
  size_t newsize = current_size + GET_SIZE(next);

  /* Case 1: Size is equal to the current payload size */
  if (asize == current_size)
    return ptr;

  // Case 2: Size is less than the current payload size 
  if ( asize <= current_size ) {

    if( asize > MINBLOCKSIZE && (current_size - asize) > MINBLOCKSIZE) {  

      PUT(HDRP(ptr), PACK(asize, 1));
      PUT(FTRP(ptr), PACK(asize, 1));
      bp = NEXT_BLKP(ptr);
      PUT(HDRP(bp), PACK(current_size - asize, 1));
      PUT(FTRP(bp), PACK(current_size - asize, 1));
      mm_free(bp);
      return ptr;
    }

    // allocate a new block of the requested size and release the current block
    bp = mm_malloc(asize);
    memcpy(bp, ptr, asize);
    mm_free(ptr);
    return bp;
  }

  // Case 3: Requested size is greater than the current payload size 
  else {

    // next block is unallocated and is large enough to complete the request
    // merge current block with next block up to the size needed and free the 
    // remaining block.
    if ( !GET_ALLOC(next) && newsize >= asize ) {

      // merge, split, and release
      remove_freeblock(NEXT_BLKP(ptr));
      PUT(HDRP(ptr), PACK(asize, 1));
      PUT(FTRP(ptr), PACK(asize, 1));
      bp = NEXT_BLKP(ptr);
      PUT(HDRP(bp), PACK(newsize-asize, 1));
      PUT(FTRP(bp), PACK(newsize-asize, 1));
      mm_free(bp);
      return ptr;
    }  
    
    // otherwise allocate a new block of the requested size and release the current block
    bp = mm_malloc(asize); 
    memcpy(bp, ptr, current_size);
    mm_free(ptr);
    return bp;
  }

}


static void *extend_heap(size_t words)
{
  char *bp;
  size_t asize;

  /* Adjust the size so the alignment and minimum block size requirements
   * are met. */ 
  asize = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;
  if (asize < MINBLOCKSIZE)
    asize = MINBLOCKSIZE;
  
  // Attempt to grow the heap by the adjusted size 
  if ((bp = mem_sbrk(asize)) == (void *)-1)
    return NULL;

  /* Set the header and footer of the newly created free block, and
   * push the epilogue header to the back */
  PUT(HDRP(bp), PACK(asize, 0));
  PUT(FTRP(bp), PACK(asize, 0));
  PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); /* Move the epilogue to the end */

  // Coalesce any partitioned free memory 
  return coalesce(bp); 
}


static void *find_fit(size_t size)
{
  // First-fit search 
  void *bp;

  /* Iterate through the free list and try to find a free block
   * large enough */
  for (bp = free_listp; GET_ALLOC(HDRP(bp)) == 0; bp = NEXT_FREE(bp)) {
    if (size <= GET_SIZE(HDRP(bp))) 
      return bp; 
  }
  // Otherwise no free block was large enough
  return NULL; 
}


static void remove_freeblock(void *bp)
{
  if(bp) {
    if (PREV_FREE(bp))
      NEXT_FREE(PREV_FREE(bp)) = NEXT_FREE(bp);
    else
      free_listp = NEXT_FREE(bp);
    if(NEXT_FREE(bp) != NULL)
      PREV_FREE(NEXT_FREE(bp)) = PREV_FREE(bp);
  }
}


static void *coalesce(void *bp)
{
  // Determine the current allocation state of the previous and next blocks 
  size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp))) || PREV_BLKP(bp) == bp;
  size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));

  // Get the size of the current free block
  size_t size = GET_SIZE(HDRP(bp));

  /* If the next block is free, then coalesce the current block
   * (bp) and the next block */
  if (prev_alloc && !next_alloc) {           // Case 2 (in text) 
    size += GET_SIZE(HDRP(NEXT_BLKP(bp)));  
    remove_freeblock(NEXT_BLKP(bp));
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
  }

  /* If the previous block is free, then coalesce the current
   * block (bp) and the previous block */
  else if (!prev_alloc && next_alloc) {      // Case 3 (in text) 
    size += GET_SIZE(HDRP(PREV_BLKP(bp)));
    bp = PREV_BLKP(bp); 
    remove_freeblock(bp);
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
  } 

  /* If the previous block and next block are free, coalesce
   * both */
  else if (!prev_alloc && !next_alloc) {     // Case 4 (in text) 
    size += GET_SIZE(HDRP(PREV_BLKP(bp))) + 
            GET_SIZE(HDRP(NEXT_BLKP(bp)));
    remove_freeblock(PREV_BLKP(bp));
    remove_freeblock(NEXT_BLKP(bp));
    bp = PREV_BLKP(bp);
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
  }

  // Insert the coalesced block at the front of the free list 
  insertb(bp);

  // Return the coalesced block 
  return bp;
}

static void insertb(void* bp){
    if(NEXT_FREE(free_listp)){
        NEXT_FREE(bp) = NEXT_FREE(free_listp);
    }
    else{
        NEXT_FREE(bp) = NULL;
    }
    NEXT_FREE(free_listp) = bp;
    PREV_FREE(bp)=free_listp;
    if (NEXT_FREE(bp) != NULL)
        PREV_FREE((NEXT_FREE(bp))) = bp;
}


static void place(void *bp, size_t asize)
{  
  // Gets the total size of the free block 
  size_t fsize = GET_SIZE(HDRP(bp));

  // Case 1: Splitting is performed 
  if((fsize - asize) >= (MINBLOCKSIZE)) {

    PUT(HDRP(bp), PACK(asize, 1));
    PUT(FTRP(bp), PACK(asize, 1));
    remove_freeblock(bp);
    bp = NEXT_BLKP(bp);
    PUT(HDRP(bp), PACK(fsize-asize, 0));
    PUT(FTRP(bp), PACK(fsize-asize, 0));
    coalesce(bp);
  }

  // Case 2: Splitting not possible. Use the full free block 
  else {

    PUT(HDRP(bp), PACK(fsize, 1));
    PUT(FTRP(bp), PACK(fsize, 1));
    remove_freeblock(bp);
  }
}
