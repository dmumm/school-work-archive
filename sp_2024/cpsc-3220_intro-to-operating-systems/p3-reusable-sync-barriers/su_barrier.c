// CPSC 3220 single use barrier method implementations
//
// implementation of OSPP Figure 5.12 using pthreads
//
// implemented in C with an OO flavor to allow multiple
//   instances of the barrier type to be created and used


#include "su_barrier.h"


void single_use_barrier_checkin(single_use_barrier_t * self)
{
    pthread_mutex_lock(&self->lock);

#ifdef VERBOSE
    printf("checkin for barrier %d\n", self->barrier_id);
#endif

    self->num_entered++;
    if (self->num_entered < self->num_threads) {
        while (self->num_entered < self->num_threads) {
            pthread_cond_wait(&self->all_checked_in, &self->lock);
        }
    }
    else {
        pthread_cond_broadcast(&self->all_checked_in);
    }

    pthread_mutex_unlock(&self->lock);
}


single_use_barrier_t * new_rb(int number_of_threads)
{
    single_use_barrier_t * rb;
    static int barrier_counter = 0;
    int rc;  // return code

    // this function does not need locking operations since the lock
    //   is created in this function

    rb = malloc(sizeof(single_use_barrier_t));  // obtain memory for struct
    if (rb == NULL) return NULL;

    rb->num_entered = 0;                          // set data fields
    rb->num_threads = number_of_threads;

    rb->barrier_id = barrier_counter++;

    rc = pthread_mutex_init(&rb->lock, NULL);  // initialize synch vars
    if (rc != 0) {
        free(rb);
        return NULL;
    }
    rc = pthread_cond_init(&rb->all_checked_in, NULL);
    if (rc != 0) {
        free(rb);
        return NULL;
    }

    rb->checkin = &single_use_barrier_checkin;     // set method pointer

#ifdef VERBOSE
    printf("barrier %d created\n", rb->barrier_id);
#endif

    return rb;
}


single_use_barrier_t * delete_rb(single_use_barrier_t * rb)
{

    // this function does not need locking operations since the lock
    //   is destroyed in this function

    pthread_cond_destroy(&rb->all_checked_in);
    pthread_mutex_destroy(&rb->lock);

    free(rb);

#ifdef VERBOSE
    printf("barrier %d deleted\n", rb->barrier_id);
#endif

    return NULL;
}
