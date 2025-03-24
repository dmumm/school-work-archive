#include "large_object_tracker.h"

// Function to initialize the large object tracker
void init_large_object_tracker(large_object_tracker_t *tracker)
{
    fprintf(stderr,"Init Large Object Tracker!\n");
    if (tracker != NULL) {
        tracker->head = NULL;
    }
}

// Function to track a new large allocation
void track_large_allocation(large_object_tracker_t *tracker, void *address, size_t size)
{
    fprintf(stderr,"Track Large Allocation!\n");

    if (tracker == NULL || address == NULL) return;

    // TODO: account for overhead when allocating and freeing large data
    // Embed the tracking record at the beginning of the allocated block
    large_object_record_t *record = (large_object_record_t *)address;
    record->address = (char *)address + sizeof(large_object_record_t);
    record->size = size;
    record->next = tracker->head;
    tracker->head = record;
}

// Function to untrack a large allocation
void untrack_large_allocation(large_object_tracker_t *tracker, void *address)
{
    fprintf(stderr,"Untrack Large Allocation!\n");
    if (tracker == NULL || tracker->head == NULL || address == NULL) return;

    // Adjust address to point to the actual start of the allocation
    large_object_record_t *actual_address = (large_object_record_t *)((char *)address - sizeof(large_object_record_t));

    // Remove the record from the list
    large_object_record_t **indirect = &tracker->head;
    while ((*indirect) != actual_address) {
        if (*indirect == NULL) return;  // Address not found
        indirect = &(*indirect)->next;
    }
    *indirect = actual_address->next;
}

// Function to check if an address is a tracked large allocation
int is_large_allocation_tracked(const large_object_tracker_t *tracker, void *address)
{
    fprintf(stderr,"Is Large Allocation Tracked!\n");
    if (tracker == NULL || address == NULL) return 0;

    large_object_record_t *current = tracker->head;
    while (current != NULL)
    {
        if (current->address == address)
        {
            return 1;
        }
        current = current->next;
    }

    return 0;
}
