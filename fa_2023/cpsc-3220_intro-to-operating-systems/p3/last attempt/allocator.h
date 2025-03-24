#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif // _GNU_SOURCE

#include <stddef.h> // For size_t
#include <stdlib.h>  // For EXIT_FAILURE
#include <string.h>  // For memset
#include <sys/mman.h>  // For mmap and munmap
#include <assert.h>
#include <stdio.h>
#include "page.h"
#include "large_object_tracker.h"

#define NUM_SIZE_CLASSES 11  // Number of size classes (2, 4, 8, ..., 1024)


// Allocator state structure
typedef struct allocator_state {
    page_list_t page_lists[NUM_SIZE_CLASSES]; // Array of page lists for each size class
    large_object_tracker_t large_object_tracker; // Tracker for large object allocations
} allocator_state_t;


// Allocator interface functions

void allocator_init(allocator_state_t *state);

void allocator_destroy(allocator_state_t *state);

// Allocate memory
// Arguments:
//   - size: Number of bytes to allocate
// Returns:
//   - A pointer to the allocated memory, or NULL if allocation failed
void *malloc(size_t size);

// Free memory
// Arguments:
//   - ptr: Pointer to the memory to free
void free(void *ptr);

// Allocate zero-initialized memory
// Arguments:
//   - nmemb: Number of elements to allocate
//   - size: Size of each element
// Returns:
//   - A pointer to the allocated memory, or NULL if allocation failed
void *calloc(size_t nmemb, size_t size);

// Reallocate memory
// Arguments:
//   - ptr: Pointer to the memory to reallocate
//   - size: New size of the allocation
// Returns:
//   - A pointer to the reallocated memory, or NULL if reallocation failed
void *realloc(void *ptr, size_t size);

#endif // ALLOCATOR_H
