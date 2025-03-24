/* Dylan Mumm */

/* CPSC 3220-002 - Spring 2024 - program 1: Boundary Tag
 *
 * These functions implement operations on a free list of memory
 * allocation blocks for dynamic memory allocation based on the
 * boundary tag method.
 *
 * The blocks, whether free or allocated, have both top and end
 * tag blocks of 16 bytes each:
 *   1 byte tag of free (=0) or allocated (=1)
 *   11 byte character string signature for error detection
 *   4 byte size
 *
 * The tag block data structure is declared as:
 *   struct tag_block {
 *     char tag;
 *     char sig[11];
 *     unsigned int size;
 *   };
 *
 * The signature is inserted using strcpy(), e.g., if tb is a
 * pointer to a struct tag_block, then a top signature is inserted
 * as strcpy(tb->sig,"top_memblk"); - note the 10-character limit.
 *
 * The free list is a circular, doubly-linked, integrated free list
 * with backward and forward pointers placed at the top of the
 * available memory in a free block (just below the top tag block).
 *
 * Free blocks are searched in a first-fit policy. The address
 * returned to the caller is the payload area just beyond the top
 * tag.
 *
 *     +---------------+
 *     | top tag block |
 *     +---------------+<-- address returned by alloc_mem() to caller
 *     |    payload    |
 *     +---------------+
 *     | end tag block |
 *     +---------------+
 *
 * There is a special free list header node placed at the end of
 * the memory region, and this doubly-linked node is maintained
 * even when the list is empty. (The empty status is indicated when
 * the free list starting address points to free list header node.)
 *
 *     free_list->.->+-----------+<--.
 *                '--| back_link |   |
 *                   +-----------+   |
 *                   | fwd_link  |---'
 *                   +-----------+
 *
 *
 *     free_list---->+-----------+<-    +---------------+
 *                .--| back_link |  \   | top tag block |
 *                |  +-----------+ .-\->+---------------+<-- ...
 *                |  | fwd_link  |-   --| back_link     |
 *                |  +-----------+      | fwd_link      |--> ...
 *                |                     |               |
 *                |                     | (unused)      |
 *                |                     |               |
 *                |                     +---------------+
 *                |                     | end tag block |
 *                |                     +---------------+
 *                |
 *                `----------------------------------------> ...
 *
 * Blocks are allocated in multiples of 16 bytes by rounding up
 * a request size to a multiple or 16 when necessary. An allocated
 * block will be 32 bytes more than the rounded request size.
 * (Note: in the special case where there is less than 48 bytes
 * remaining when satisfying a request for the last remaining free
 * block, the complete remaining free block will be allocated.)
 *
 * Released blocks of memory will be coalesced with free blocks
 * in adjacent memory locations when possible. If a released block
 * cannot be coalesced with adjacent free blocks, it will be added
 * at the head of the free list. (There is no need to keep the free
 * list in sorted order by address since the boundary tags are used
 * for identifying and examining the adjacent blocks.)
 *
 * Special end and top tag blocks are added at the top and end of
 * the memory region, respectively, to simplify coalescing logic.
 * That is, a released block at the top of the memory region will
 * not have to do a special case test but instead find that what
 * appears to be the block above it is (permanently) allocated.
 * Likewise, a released block at the end of the memory region will
 * not have to do a special case test but instead find that what
 * appears to be the block below it is (permanently) allocated.
 *
 * Here is the initial state of the memory area. Note that there
 * are 80 bytes beyond the size of the area that can be allocated
 * because of the four tag blocks (= 4 * 16) and the free list
 * header node (= 2 * 8 for 8-byte pointers).
 *
 *       =============  special ending tag block at start of region
 *       | tag=1     |    1 byte, this tag is always equal to one
 *       | signature |   11 bytes = "end_region"
 *       | empty     |    4 bytes = 0
 *       =============
 *       | tag       |    1 byte, 0 if free, 1 when allocated
 *       | signature |   11 bytes = "top_memblk"
 *       | size      |    4 bytes for size of free block
 *       +-----------+ - - - - - - - - - - - - - - - - - - - - - - - -
 * ptr-->| back_link |    8 bytes, used when part of free list       A
 *       | fwd_link  |    8 bytes, used when part of free list       |
 *       |           |                                               |
 *       |           |                              size of free block
 *         ...            INITIAL FREE BLOCK          (multiple of 16)
 *       |           |                                               |
 *       |           |                                               V
 *       +-----------+ - - - - - - - - - - - - - - - - - - - - - - - -
 *       | tag       |    1 bytes, 0 if free, 1 when allocated
 *       | signature |   11 bytes = "end_memblk"
 *       | size      |    4 bytes for size of free block
 *       =============  special starting tag block at end of region
 *       | tag=1     |    1 byte, this tag is always equal to one
 *       | signature |   11 bytes = "top_region"
 *       | empty     |    4 bytes = 0
 *       =============  free list header node
 * free->| back_link |    8 bytes, points to self if empty or to last node
 *       | fwd_link  |    8 bytes, points to hdr back_link if empty or to
 *       =============      first node
 *
 * To give some example addresses and block sizes, assume that the data
 * structure starts at 0x100 and has 0x300 bytes to allocate.
 *
 * addr
 *       =============  special ending tag block at start of region
 * 0x100 |       1   |    1 byte, this tag is always equal to one
 * 0x101 |<signature>|   11 bytes = "end_region"
 * 0x10c |       0   |    4 bytes = 0, size
 *       =============
 * 0x110 |       0   |    1 byte, free = 0
 * 0x111 |<signature>|   11 bytes = "top_memblk"
 * 0x11c |   0x300   |    4 bytes, size
 *       +-----------+ - - - - - - - - - - - - - - - - - - - - - - - -
 * 0x120 |   0x440   |    8 bytes, used when part of free list       A
 * 0x128 |   0x440   |    8 bytes, used when part of free list       |
 *       |           |                                               |
 *       |           |                              size of free block
 *         ...            INITIAL FREE BLOCK   (multiple of 16 = 0x10)
 *       |           |                               0x300 = 768 bytes
 *       |           |                                               V
 *       +-----------+ - - - - - - - - - - - - - - - - - - - - - - - -
 * 0x420 |       0   |    1 bytes, free = 0
 * 0x421 |<signature>|   11 bytes = "end_memblk"
 * 0x42c |   0x300   |    4 bytes, size
 *       =============  special starting tag block at end of region
 * 0x430 |       1   |    1 byte, this tag is always equal to one
 * 0x431 |<signature>|   11 bytes = "top_region"
 * 0x43c |       0   |    4 bytes = 0
 *       =============  free list header node
 * 0x440 |   0x120   |    8 bytes, points to self if empty or to last node
 * 0x448 |   0x120   |    8 bytes, points to hdr back_link if empty or to
 *       =============      first node
 *
 * When a large enough free block is found, an allocation is made from
 * the higher-address end of the free block (so that only the size of
 * the free list block needs to change and not the free list pointers
 * to that block). Thus, if we allocate 0x60 bytes from the 0x300-byte
 * free block above, the data structures will now be:
 *
 *       =============  special ending tag block at start of region
 * 0x100 |       1   |    1 byte, this tag is always equal to one
 * 0x101 |<signature>|   11 bytes = "end_region"
 * 0x10c |       0   |    4 bytes = 0, size
 *       =============
 * 0x110 |       0   |    1 byte, free = 0
 * 0x111 |<signature>|   11 bytes = "top_memblk"
 * 0x11c |   0x280   |    4 bytes, size
 *       +-----------+ - - - - - - - - - - - - - - - - - - - - - - - -
 * 0x120 |   0x440   |    8 bytes, used when part of free list       A
 * 0x128 |   0x440   |    8 bytes, used when part of free list       |
 *       |           |                                               |
 *         ...            ADJUSTED FREE BLOCK        0x280 = 640 bytes
 *       |           |                                               V
 *       +-----------+ - - - - - - - - - - - - - - - - - - - - - - - -
 * 0x3a0 |       0   |    1 byte, free = 0
 * 0x3a1 |<signature>|   11 bytes = "end_memblk"
 * 0x3ac |   0x280   |    4 bytes, size
 *       =============
 * 0x3b0 |       1   |    1 byte, allocated = 1
 * 0x3b1 |<signature>|   11 bytes = "top_memblk"
 * 0x3bc |    0x60   |    4 bytes, size
 *       +-----------+ - - - - - - - - - - - - - - - - - - - - - - - -
 * 0x3c0 |           |                                               A
 *         ...            ALLOCATED BLOCK              0x60 = 96 bytes
 *       |           |                                               V
 *       +-----------+ - - - - - - - - - - - - - - - - - - - - - - - -
 * 0x420 |       1   |    1 byte, allocated = 1
 * 0x421 |<signature>|   11 bytes = "end_memblk"
 * 0x42c |    0x60   |    4 bytes, size
 *       =============  special starting tag block at end of region
 * 0x430 |       1   |    1 byte, this tag is always equal to one
 * 0x431 |<signature>|   11 bytes = "top_region"
 * 0x43c |       0   |    4 bytes = 0
 *       =============  free list header node
 * 0x440 |   0x120   |    8 bytes, points to self if empty or to last node
 * 0x448 |   0x120   |    8 bytes, points to hdr back_link if empty or to
 *       =============      first node
 *
 * In the normal case, each allocation uses 32 bytes beyond the
 * requested amount since additional tag blocks will be needed. For the
 * example above, 0x300 - 0x60 - 0x20 = 0x280, or, in decimal,
 *
 *  768   starting free space of 768 bytes (0x300 bytes)
 * - 96   minus request of 96 bytes (0x60 bytes)
 * - 32   minus extra tag block space of 32 bytes (0x20 bytes)
 * ----
 *  640   equals resulting free space of 640 bytes (0x280 bytes)
 *
 * When there is not at least 48 bytes left over in a free block after
 * an allocation, the whole free block is allocated. In this case, the
 * additional tags are not needed since the existing tags can be used.
 * (Of course, the whole block is then removed from the free list.)
 *
 * When there is not enough free memory available to satisfy a request,
 * a NULL pointer should be returned. A request to allocate zero bytes
 * should also return a NULL pointer.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define FREE 0
#define USED 1
#define END_REGION_SIG "end_region"
#define TOP_REGION_SIG "top_region"
#define SIG_LENGTH 11
#define FALSE 0
#define TRUE 1
#define MATCH 0
#define TAG_SIZE sizeof(struct tag_block)
#define INCREMENT_SIZE 16
#define TAG_OVERHEAD (TAG_SIZE + TAG_SIZE)
#define MIN_BLOCK_SIZE (TAG_OVERHEAD + INCREMENT_SIZE)



 /* global data structures */

struct tag_block {
    char tag;
    char sig[11];
    unsigned int size;
};

struct free_block {
    struct free_block * back_link;
    struct free_block * fwd_link;
};

extern struct free_block * free_list;
extern char * region_base;

/* signature check macro */

#define SIGCHK(w,x,y,z) {                                                 \
	struct tag_block *scptr = (struct tag_block *)(w);                    \
	if(strncmp((char *)(scptr)+1,(x),(y))!=0){                            \
		printf("*** sigchk fail\n");                                      \
		printf("*** at %s, offset is 0x%x, sig is %s\n",                  \
			(z),((unsigned int)(((char *)w)-region_base)),(char *)(w)+1); \
	}                                                                     \
}

#define TOPSIGCHK(a,b) {SIGCHK((a),"top_",4,(b))}
#define ENDSIGCHK(a,b) {SIGCHK((a),"end_",4,(b))}


int strings_equal(const char * left, const char * right, size_t size)
{
    return strncmp(left, right, size) == 0;
}

void updateFreeListAfterAllocation(struct tag_block * allocated_block, struct tag_block * new_free_block)
{

    typedef struct free_block FreeBlock;

    // assert(allocated_block->tag == USED);
    // assert(new_free_block == NULL || new_free_block->tag == FREE);

    FreeBlock * allocated_block_node = (FreeBlock *)((char *)allocated_block + TAG_SIZE);

    // Remove the allocated block from the free list
    if (allocated_block_node->back_link->fwd_link == allocated_block_node) {
        allocated_block_node->back_link->fwd_link = allocated_block_node->fwd_link;
    }
    if (allocated_block_node->fwd_link->back_link == allocated_block_node) {
        allocated_block_node->fwd_link->back_link = allocated_block_node->back_link;
    }

    // if the list becomes empty, make it point to itself
    if (allocated_block_node->fwd_link == allocated_block_node) {
        free_list->fwd_link = free_list;
        free_list->back_link = free_list;
    }

    // Insert the new free block into the free list
    if (new_free_block != NULL) {
        FreeBlock * new_free_block_ptr = (FreeBlock *)((char *)new_free_block + TAG_SIZE);

        // If the list is empty, initialize it with the new block
        if (free_list->fwd_link == free_list) {
            free_list->fwd_link = new_free_block_ptr;
            free_list->back_link = new_free_block_ptr;
            new_free_block_ptr->fwd_link = free_list;
            new_free_block_ptr->back_link = free_list;
        }
        else {
            // Insert the new block at the beginning of the non-empty list
            new_free_block_ptr->fwd_link = free_list->fwd_link;
            new_free_block_ptr->back_link = free_list;
            free_list->fwd_link->back_link = new_free_block_ptr;
            free_list->fwd_link = new_free_block_ptr;
        }

        // assert(new_free_block_ptr->back_link == free_list);
        // if (new_free_block != NULL && free_list->fwd_link != free_list) {
        //     assert(new_free_block_ptr->fwd_link->back_link == new_free_block_ptr);
        // }
        // assert(new_free_block_ptr->back_link->fwd_link == new_free_block_ptr && new_free_block_ptr->fwd_link->back_link == new_free_block_ptr); // New free block should be properly linked


    }



    // // if (free_list->fwd_link == free_list) {
    // //     assert(free_list->back_link == free_list); // Free list is empty
    // // }
    // else {
    //     struct tag_block * first_free_tag_block = (struct tag_block *)((char *)free_list->fwd_link - TAG_SIZE);
    //     // assert(first_free_tag_block->tag == FREE);
    // }
    // FreeBlock * ptr = free_list;
    // do {
    //     // assert(ptr->fwd_link->back_link == ptr && ptr->back_link->fwd_link == ptr); // Each block should be correctly linked to its neighbors
    //     ptr = ptr->fwd_link;
    // } while (ptr != free_list);
    // FreeBlock * next_block = ptr->fwd_link;
    // if (next_block != free_list) {
    //     struct tag_block * current_tag_block = (struct tag_block *)((char *)ptr - TAG_SIZE);
    //     struct tag_block * next_tag_block = (struct tag_block *)((char *)next_block - TAG_SIZE);
    //     // assert((char *)current_tag_block + current_tag_block->size + TAG_OVERHEAD <= (char *)next_tag_block); // Blocks should not overlap
    // }


}

/* void *alloc_mem( unsigned int amount )
 *
 * input parameter
 *   amount is the number of bytes requested
 *
 * return value
 *   alloc_mem() returns a pointer to the start of the allocated
 *   block of free memory, beyond the allocation tag block. Note
 *   that the size of the beginning and ending tag blocks is over
 *   and above the number of bytes requested in "amount". If a
 *   suitable block cannot be found, alloc_mem() returns NULL.
 *   A request for zero bytes also returns NULL.
 *
 * description
 *   alloc_mem() rounds up the "amount" of memory requested to
 *   the nearest positive multiple of 16 bytes. It then searches
 *   in a first-fit manner for a block of free memory that can
 *   satisfy the requested amount of memory. There must be at
 *   least 48 bytes remaining in the free block after the
 *   allocation (i.e., enough leftover space for two tag blocks
 *   and a 16-byte remaining free area); otherwise, the whole
 *   free area must be allocated. If there is free memory left
 *   over, it is left at the top of the free block. When a
 *   suitable block is found, alloc_mem() sets the tags, sizes,
 *   and signatures appropriately and returns a pointer to the
 *   beginning of the allocated memory (i.e., to the location
 *   immediately below the starting tag block).
 */

void * alloc_mem(unsigned int amount)
{
    // assert(free_list != NULL);
    // assert(free_list->fwd_link != NULL);
    // assert(free_list->back_link != NULL);

    if (amount == 0) { return NULL; }

    typedef struct tag_block TagBlock;
    typedef struct free_block FreeBlock;

    const unsigned int og_amount = amount;
    // const char * start_block = region_base + INCREMENT_SIZE;

    // Round up the amount to the nearest positive multiple of 16 bytes
    if (og_amount % INCREMENT_SIZE != 0)
    {
        unsigned int remainder = og_amount % INCREMENT_SIZE;
        amount += INCREMENT_SIZE - remainder;
    }
    // assert(amount % INCREMENT_SIZE == 0);

    // Search for a free block that can satisfy the requested amount of memory
    FreeBlock * current_free_block = free_list;
    TagBlock * best_block = NULL;
    if (current_free_block == NULL) { return NULL; } // If the free list is corrupted, exit
    if (current_free_block == free_list->fwd_link) { return NULL; } // If the free list is empty, return NULL

    FreeBlock * start_block = current_free_block;
    do
    {
        TagBlock * current_tag_block = (TagBlock *)((char *)current_free_block - TAG_SIZE);
        if (strcmp(current_tag_block->sig, TOP_REGION_SIG) != MATCH)
        {
            // assert(current_tag_block->tag == FREE);
            if (current_tag_block->size >= amount)
            {
                if (best_block == NULL || current_tag_block->size < best_block->size)
                {
                    best_block = current_tag_block;
                }
            }
        }
        current_free_block = current_free_block->fwd_link;

    } while (current_free_block != start_block); // Check if we have come full circle


    // If no suitable block is found, return NULL
    if (best_block == NULL) { return NULL; }

    TagBlock * allocated_block = best_block;
    allocated_block->tag = USED;

    TagBlock * new_free_block = NULL;
    char * allocated_block_ptr = (char *)allocated_block;

    // Handle Splitting
    unsigned int total_size = allocated_block->size;
    unsigned int remaining_size = total_size - amount;
    if (remaining_size >= MIN_BLOCK_SIZE) {

        // Calculate the address for the new free block
        new_free_block = (TagBlock *)(allocated_block_ptr + amount + TAG_SIZE);
        new_free_block->tag = FREE;
        new_free_block->size = remaining_size - TAG_OVERHEAD;

        allocated_block->size = amount;

    }
    // printf("Allocating block at %p with size %u\n", allocated_block, amount);
    // if (new_free_block != NULL) {
    //     printf("New free block at %p with size %u\n", new_free_block, remaining_size);
    // }
    updateFreeListAfterAllocation(allocated_block, new_free_block);

    // // If there is not at least 48 bytes remaining in a free block after an allocation, the whole free block is allocated
    // if (allocated_block->size - amount < TAG_OVERHEAD + INCREMENT_SIZE)
    // {
    //     allocated_block->tag = USED;
    //     TOPSIGCHK(allocated_block, "allocating block entirety");
    //     ENDSIGCHK(allocated_block, "allocating block entirety");
    //     // strcpy(allocated_block->sig, "top_memblk");
    //     // TagBlock * end_tag = (TagBlock *)((char *)allocated_block + allocated_block->size + TAG_SIZE);
    //     // end_tag->tag = USED;
    //     // strcpy(end_tag->sig, "end_memblk");
    //     // end_tag->size = allocated_block->size;
    //     // return (void *)((char *)allocated_block + TAG_SIZE);
    // }
    // else // split the block
    // {
    //     new_free_block = (TagBlock *)((char *)allocated_block + amount + TAG_SIZE);
    //     new_free_block->tag = FREE;
    //     new_free_block->size = allocated_block->size - amount - TAG_OVERHEAD;

    //     allocated_block->tag = USED;
    //     allocated_block->size = amount;

    //     TOPSIGCHK(allocated_block, "allocating block segment");
    //     ENDSIGCHK(allocated_block, "creating new free block");
    // }

    // if (free_list->fwd_link != free_list) {
    //     assert(free_list->fwd_link->back_link == free_list);
    //     assert(free_list->back_link->fwd_link == free_list);
    // }


    return (void *)((char *)allocated_block + TAG_SIZE);
}



/* void release_mem( void *ptr )
 *
 * input parameter
 *   ptr is a pointer to the start of a block of memory that
 *   had been previously allocated by alloc_mem(); note that a
 *   tag block immediately precedes this address for a valid
 *   address.
 *
 * return value
 *   release_mem() returns a code of 0 for valid pointers and
 *   a nonzero for invalid pointers:
 *     1 = null pointer
 *     2 = unaligned pointer (not on a multiple of 16)
 *     3 = pointer to what appears to be a free block in which
 *         either the top tag or end tag is 0 (indicating free)
 *
 * description
 *   If the pointer yields a valid allocated block then the
 *   block is returned into the free list, possibly with
 *   coalescing taking place. The four possible valid cases
 *   can be processed as described below, and each valid case
 *   results in a return value of zero.
 *
 *   1) Both above and below blocks are allocated - add the
 *      returned block to the free list at the head of free
 *      list (thus the size of free list increases by one
 *      node); change the tags from allocated to free.
 *
 *   2) Above block is free but below block is allocated -
 *      coalesce the returned block with the block above;
 *      change the tags and sizes appropriately (thus the free
 *      list size and all the free list node pointers remain
 *      the same; you are only updating other fields in an
 *      existing free list node); change the signatures in the
 *      previous ending tag block of the block above and the
 *      starting tag block of the returned block (so that
 *      signature checks will fail if a dangling pointer is
 *      later used)
 *
 *   3) Above block is allocated but below block is free -
 *      coalesce the returned block with the block below;
 *      change the tags and sizes appropriately and change the
 *      free list pointers in the backward and forward free
 *      nodes to point to the top of the newly-merged free
 *      block (pointers change but the size of the free list
 *      does not change); change signatures in the ending tag
 *      block of the returned block and the previous starting
 *      tag block of the block below (so that signature checks
 *      will fail if a dangling pointer is later used)
 *
 *   4) Both above and below block are free - coalesce the
 *      returned block with both the above and below blocks
 *      into a single free block and remove the node for the
 *      bottom block (thus reducing the size of the free list
 *      by one node); change the tags and sizes appropriately;
 *      change signatures in all tag blocks except in the
 *      starting tag block of the block above and in the ending
 *      tag block of the block below (so that signature checks
 *      will fail if a dangling pointer is later used)
 *
 *   As mentioned in cases 2, 3, and 4, you can change the
 *   signatures in any unused tag blocks to hint strings, e.g.,
 *   "old_top_mb" and "old_end_mb". Since the signature check
 *   macro prints a failing character string, you can use it
 *   in conjunction wit these hints to help in debugging. You
 *   can also include an event count number in the hint string
 *   by using sprintf(), such as,
 *     sprintf(hint_string,"old_top%03d",event_count);
 *   Remember that the hint string should be at most ten
 *   printable characters and a terminating null character
 *   (since the signature field is 11 bytes).
 */

unsigned int release_mem(void * ptr)
{

    /* for student to provide */
    return 0; //TODO: remove this line

}
