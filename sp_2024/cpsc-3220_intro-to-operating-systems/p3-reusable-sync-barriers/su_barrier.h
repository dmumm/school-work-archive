// CPSC 3220 single use barrier header
//
// implementation of OSPP Figure 5.12 using pthreads
//
// implemented in C with an OO flavor to allow multiple
//   instances of the barrier type to be created and used

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct single_use_barrier_tag{

    // synchronization variables

    pthread_mutex_t lock;
    pthread_cond_t all_checked_in;

    // state variables

    int num_entered;
    int num_threads;

    // identifier to help in debugging

    int barrier_id;

    // public method

    void (*checkin)();

} single_use_barrier_t;


// constructor-like and destructor-like functions

single_use_barrier_t *new_rb( int );
single_use_barrier_t *delete_rb( single_use_barrier_t *rb );
