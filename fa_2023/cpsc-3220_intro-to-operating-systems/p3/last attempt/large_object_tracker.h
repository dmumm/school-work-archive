#ifndef LARGE_OBJECT_TRACKER_H
#define LARGE_OBJECT_TRACKER_H

#include <stddef.h>
#include <sys/mman.h>  // For mmap and munmap
#include <stdio.h> // For fprintf


typedef struct large_object_record {
    void *address;              // Pointer to the allocated memory
    size_t size;                // Size of the allocation
    struct large_object_record *next;  // Next record in the list
} large_object_record_t;

typedef struct large_object_tracker {
    large_object_record_t *head;  // Head of the list of large object records
} large_object_tracker_t;

// Function to initialize the large object tracker
void init_large_object_tracker(large_object_tracker_t *tracker);

// Function to track a new large allocation
// Arguments:
//   - tracker: Pointer to the large object tracker
//   - address: Pointer to the allocated memory
//   - size: Size of the allocation
void track_large_allocation(large_object_tracker_t *tracker, void *address, size_t size);

// Function to untrack a large allocation
// Arguments:
//   - tracker: Pointer to the large object tracker
//   - address: Pointer to the allocated memory
void untrack_large_allocation(large_object_tracker_t *tracker, void *address);

// Function to check if an address is a tracked large allocation
// Arguments:
//   - tracker: Pointer to the large object tracker
//   - address: Pointer to the memory address to check
// Returns:
//   - Non-zero if the address is a tracked large allocation, 0 otherwise
int is_large_allocation_tracked(const large_object_tracker_t *tracker, void *address);

#endif // LARGE_OBJECT_TRACKER_H
