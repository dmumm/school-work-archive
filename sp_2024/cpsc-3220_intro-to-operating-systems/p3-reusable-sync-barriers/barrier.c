// CPSC 3220 Project 3
// Implementation of a reusable barrier, OSPP Figure 5.12, using pthreads with an OO flavor.
// Allows multiple instances of the barrier type to be created and used.

#include "barrier.h"

// Global counter
static int barrier_counter = 0;

/**
 * Checks in at the reusable barrier. Threads calling this function will wait until all threads have checked in.
 * Once all threads have checked in, they are all allowed to proceed. If threads are already proceeding,
 * a thread calling this function will wait until it is safe to proceed to the next barrier point.
 *
 * @param self A pointer to the reusable barrier object.
 *
 */
void reusable_barrier_checkin(reusable_barrier_t * self)
{
    pthread_mutex_lock(&self->lock);

    #ifdef VERBOSE
        printf("checkin for barrier %d\n", self->barrier_id);
    #endif

    self->num_entered++;

    if (self->num_entered < self->num_threads) {
        while (self->num_entered < self->num_threads) {
            pthread_cond_wait(&self->all_checked_in, &self->lock); // Wait for all threads to check in if they haven't already
        }
    }
    else {
        self->num_leaving = 0;
        pthread_cond_broadcast(&self->all_checked_in);
    }

    self->num_leaving++;

    if (self->num_leaving < self->num_threads) {
        while (self->num_leaving < self->num_threads) {
            pthread_cond_wait(&self->all_leaving, &self->lock); // Wait for all threads to leave if they haven't already
        }
    }
    else {
        self->num_entered = 0;
        pthread_cond_broadcast(&self->all_leaving); // Broadcast to all threads that they can leave
    }

    pthread_mutex_unlock(&self->lock);
}

/**
 * Creates and initializes a new reusable barrier object for synchronizing a specific number of threads.
 *
 * @param number_of_threads The number of threads that must reach the barrier before any can proceed.
 * @return A pointer to the newly created reusable barrier object, or NULL if the object could not be created.
 *
 * The function allocates memory for a reusable_barrier_t object and initializes it. If the allocation or initialization
 * fails, it returns NULL.
 *
 */
reusable_barrier_t * new_rb(int number_of_threads)
{
    reusable_barrier_t * rb = malloc(sizeof(reusable_barrier_t));
    if (rb == NULL) return NULL;

    rb->num_entered = 0;
    rb->num_leaving = 0;
    rb->num_threads = number_of_threads;
    rb->barrier_id = barrier_counter++;

    if (pthread_mutex_init(&rb->lock, NULL) != 0 ||
        pthread_cond_init(&rb->all_checked_in, NULL) != 0 ||
        pthread_cond_init(&rb->all_leaving, NULL) != 0) {
        delete_rb(rb);
        return NULL;
    }

    rb->checkin = reusable_barrier_checkin;

    #ifdef VERBOSE
        printf("Barrier %d created\n", rb->barrier_id);
    #endif

    return rb;
}

/**
 * Destroys a reusable barrier object and frees its allocated memory. It should be called when the barrier is no
 * longer needed, to clean up resources.
 *
 * @param rb A pointer to the reusable barrier object to be deleted.
 * @return Always returns NULL as an indication that the barrier has been deleted.

 * This function destroys the mutex and condition variables associated with the barrier and frees the memory
 * allocated for the barrier object.
 *
 */
reusable_barrier_t * delete_rb(reusable_barrier_t * rb)
{
    if (rb != NULL) {
        pthread_cond_destroy(&rb->all_checked_in);
        pthread_cond_destroy(&rb->all_leaving);
        pthread_mutex_destroy(&rb->lock);
        free(rb);

        #ifdef VERBOSE
            printf("Barrier %d deleted\n", rb->barrier_id);
        #endif
    }

    return NULL;
}