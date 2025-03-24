// CPSC 3220 single-use barrier test driver with one barrier instance
//
// compile with "gcc -Wall single_use_barrier.c driver.c -pthread" or
//   "gcc -Wall -D VERBOSE single_use_barrier.c driver.c -pthread"
//
// run with "./a.out" or "valgrind --tool=helgrind ./a.out"
//
// five threads cooperate to sum the values in the 5x5 subarray
//   of a 6x5 array
//
// 1) each thread is assigned a unique column and stores
//      the column sum in an extra sixth row
// 2) each thread checks into the shared barrier
// 3) each thread prints the total sum by adding the values
//      in the sixth row
//
//   thread0  thread1  thread2  thread3  thread4
//
//   [ a00  ] [ a01  ] [ a02  ] [ a03  ] [ a04 ]
//   [ a10  ] [ a11  ] [ a12  ] [ a13  ] [ a14 ]
//   [ a20  ] [ a21  ] [ a22  ] [ a23  ] [ a24 ]
//   [ a30  ] [ a31  ] [ a32  ] [ a33  ] [ a34 ]
//   [ a40  ] [ a41  ] [ a42  ] [ a43  ] [ a44 ]
//   [ sum0 ] [ sum1 ] [ sum2 ] [ sum3 ] [ sum4 ]

#include "su_barrier.h"

#define THREADS 5


int array[ THREADS + 1 ][ THREADS ];


// an argument vector for each thread is used to combine
//   multiple arguments to pass to the thread since only
//   one function argument is allowed for pthread_create()

typedef struct{
    single_use_barrier_t *rbp;  // pointer to barrier instance
    int tid;                    // thread id
} argvec_t;


// function for each worker thread

void *worker( void *ap ){
    single_use_barrier_t *rb = ((argvec_t *)ap)->rbp;  // extract arguments
    int thread_id = ((argvec_t *)ap)->tid;

    int i, j, sum;

    // find column sum for this thread's column

    sum = 0;
    for( i = 0; i < THREADS; i++ ){
        sum += array[i][thread_id];
    }
    array[THREADS+1][thread_id] = sum;

    // barrier

    (rb->checkin)( rb );

    // find total sum

    sum = 0;
    for( j = 0; j < THREADS; j++ ){
        sum += array[THREADS+1][j];
    }
    printf( "total sum is %d\n", sum );

    return NULL;
}


int main(){
    pthread_t threads[ THREADS ];   // thread info blocks for pthreads
    argvec_t args[ THREADS ];       // unique argument vectors
    single_use_barrier_t
      *array_processing_barrier;    // barrier instance
    int i, j, counter = 0;

    // fill in values for the NxN subarray in the test array

    for( i = 0; i < THREADS; i++ ){
        for( j = 0; j < THREADS; j++ ){
            array[i][j] = counter++;
        }
    }

    // create a barrier

    array_processing_barrier = new_rb( THREADS );
    if( array_processing_barrier == NULL ){
        printf( "**** could not create a barrier\n" );
        exit( 0 );
    }

    // create the threads with a pointer to the shared barrier
    //   and a thread id

    for( i = 0; i < THREADS; i++ ){
        args[i].rbp = array_processing_barrier;
        args[i].tid = i;
        if( pthread_create( &threads[i], NULL, &worker, (void *)(&args[i]) ) ){
            printf( "**** could not create worker thread %d\n", i );
            exit( 0 );
        }
    }

    // join all worker threads

    for( i = 0; i < THREADS; i++ ){
        if( pthread_join( threads[i], NULL ) ){
            printf( "**** could not join thread %d\n", i );
            exit( 0 );
        }
    }

    // call the destructor-like function for the barrier instance

    array_processing_barrier = delete_rb( array_processing_barrier );

    return 0;
}
