// CPSC 3220 reusable barrier test driver
//
// compile with "gcc -Wall single_use_barrier.c driver.c -pthread" or
//   "gcc -Wall -D VERBOSE single_use_barrier.c driver.c -pthread"
//
// run with "./a.out" or "valgrind --tool=helgrind ./a.out"

#include "barrier.h"

#define THREADS 5

// initial vector contents

int vec[5] = { 1,2,3,4,5 };

// an argument vector for each thread is used to combine
//   multiple arguments to pass to the thread since only
//   one function argument is allowed for pthread_create()

typedef struct {
    reusable_barrier_t * rbp;  // pointer to barrier instance
    int tid;                  // thread id
} argvec_t;


// function for each worker thread

void * worker(void * ap)
{
    reusable_barrier_t * rb = ((argvec_t *)ap)->rbp;  // extract arguments
    int thread_id = ((argvec_t *)ap)->tid;
    int i, sum;

    // sum vector contents

    sum = 0;
    for (i = 0; i < 5; i++) {
        sum += vec[i];
    }

    // first use of barrier

    (rb->checkin)(rb);

    // replace the value of a vector entry

    vec[thread_id] = sum;

    // second use of barrier

    (rb->checkin)(rb);

    // sum vector contents and display

    sum = 0;
    for (i = 0; i < 5; i++) {
        sum += vec[i];
    }

    printf("sum = %d\n", sum);

    return NULL;
}


int main()
{
    pthread_t threads[THREADS];    // thread info blocks for pthreads
    argvec_t args[THREADS];        // unique argument vectors
    reusable_barrier_t * barrier;
    int i;

    // create a barrier with five threads

    barrier = new_rb(5);
    if (barrier == NULL) {
        printf("**** could not create a barrier\n");
        exit(0);
    }

    // create five worker threads with a pointer to the barrier

    for (i = 0; i < 5; i++) {
        args[i].rbp = barrier;
        args[i].tid = i;
        if (pthread_create(&threads[i], NULL, &worker, (void *)(&args[i]))) {
            printf("**** could not create worker thread %d\n", i);
            exit(0);
        }
    }

    // join all worker threads

    for (i = 0; i < THREADS; i++) {
        if (pthread_join(threads[i], NULL)) {
            printf("**** could not join thread %d\n", i);
            exit(0);
        }
    }

    // call the destructor-like function for the barrier instances

    barrier = delete_rb(barrier);

    return 0;
}
