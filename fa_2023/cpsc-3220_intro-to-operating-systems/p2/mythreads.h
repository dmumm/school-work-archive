#define STACK_SIZE (16*1024)
#define NUM_LOCKS 10
#define CONDITIONS_PER_LOCK 10

// the type of function used to run your threads
typedef void *(*thFuncPtr) (void *);

extern void threadInit();

// thread management functions
extern int threadCreate(thFuncPtr funcPtr, void *argPtr);
extern void threadYield();
extern void threadJoin(int thread_id, void **result);

// exits the current thread -- calling this in the main thread should terminate the program
extern void threadExit(void *result);

// synchronization functions
extern void threadLock(int lockNum);
extern void threadUnlock(int lockNum);
extern void threadWait(int lockNum, int conditionNum);
extern void threadSignal(int lockNum, int conditionNum);

//this needs to be defined in your library. Don't forget it or some of my tests won't compile.
//control atomicity
//---should be defined in your library
//---your library will set this variable to 1 whenever it
//   wants to disable preemption
extern int interruptsAreDisabled;