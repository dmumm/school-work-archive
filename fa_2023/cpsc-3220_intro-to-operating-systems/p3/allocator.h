#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif // _GNU_SOURCE

#include <fcntl.h>
#include <stddef.h>
#include <sys/mman.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <assert.h>

#define PAGESIZE 4096
#define NUM_SIZE_CLASSES 10
#define LARGE_OBJECT_IDENTIFIER 0xDEADBEEF
// Number of size classes (2, 4, 8, ..., 1024)

typedef struct page page_t;  // Forward declaration of page_t

typedef struct block {
    page_t* page; // Pointer to the page that owns this block
    struct block* next; // Pointer to the next block
    // The data follows immediately after the block structure in memory
} block_t;

struct page { // Complete definition of page_t
    size_t block_size;       // Size of each block in this page
    page_t* next;            // Pointer to the next page
    block_t* free_list;      // Pointer to the first free block
    // Blocks start immediately after the page structure in memory
};

typedef struct metadata {
    size_t size;
    unsigned long identifier; // Identifier to distinguish large objects}
} metadata_t;

void __attribute__ ((constructor)) shim_init();
void __attribute__ ((destructor)) shim_destroy();

/**
 * @brief Allocates memory
 * @param size Number of bytes to allocate
 * @return void* A pointer to the allocated memory, or NULL if allocation failed
 */
void* my_malloc(size_t size);

/**
 * @brief Free memory
 * @param ptr Pointer to the memory to free
 */
void my_free(void* ptr);

/**
 * @brief Allocate zero-initialized memory
 * @param nitems Number of elements to allocate.
 * @param size Number of bytes to allocate.
 * @return void* Pointer to the allocated memory.
 */
void* my_calloc(size_t nitems, size_t size);

/**
 * @brief Reallocate memory
 * @param ptr Pointer to the memory to reallocate
 * @param size New size of the allocation
 * @return void* A pointer to the reallocated memory, or NULL if reallocation failed
 */
void* my_realloc(void* ptr, size_t size);

#endif // ALLOCATOR_H