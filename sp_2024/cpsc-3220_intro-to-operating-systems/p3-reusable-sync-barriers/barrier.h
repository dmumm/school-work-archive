// CPSC 3220 Project 3
// Implementation of a reusable barrier using pthreads with an OO flavor.
// Allows multiple instances of the barrier type to be created and used.

#ifndef BARRIER_H
#define BARRIER_H

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct reusable_barrier_tag {

    pthread_mutex_t lock;                           // Synchronization lock
    pthread_cond_t all_checked_in;                  // Condition variable for checking in
    pthread_cond_t all_leaving;                     // Condition variable for leaving

    int num_entered;                                // Number of threads entered
    int num_leaving;                                // Number of threads leaving
    int num_threads;                                // Total number of threads

    int barrier_id;                                 // Identifier for debugging

    void (*checkin)(struct reusable_barrier_tag *); // Method for checking in

} reusable_barrier_t;

// Constructor and deconstructor like prototypes
reusable_barrier_t * new_rb(int number_of_threads);
reusable_barrier_t * delete_rb(reusable_barrier_t * rb);

#endif // BARRIER_H
