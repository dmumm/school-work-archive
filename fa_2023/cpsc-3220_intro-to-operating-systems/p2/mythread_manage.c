#include "mythread_common.h"

/* ### Initialize ### */

void threadInit()
{
    interruptDisable();

    // Initialize thread queue
    threadQueueHead = NULL;

    // Initialize thread IDs
    active = 0;
    awaiting = 0;
    nextThreadID = 0;

    // Initialize locks
    for (int i = 0; i < NUM_LOCKS; i++)
    {
        locks[i] = LOCK_UNLOCKED;
        for (int j = 0; j < CONDITIONS_PER_LOCK; j++)
        {
            conditionalVariable[i][j] = -1;
        }
    }

    // Initialize main context
    getcontext(&mainContext);
    mainContext.uc_stack.ss_size = STACK_SIZE;
    mainContext.uc_stack.ss_flags = 0;
    active = add_tcb(mainContext);
    thread(active)->state = THREAD_RUNNING;

    interruptEnable();
}

/* ### Management ### */

// Add a new thread to the queue, return its ID
int threadCreate(thFuncPtr funcPtr, void *argPtr)
{

    interruptDisable();

    ucontext_t newContext;
    getcontext(&newContext);

    newContext.uc_stack.ss_sp = malloc(STACK_SIZE);
    newContext.uc_stack.ss_size = STACK_SIZE;
    newContext.uc_stack.ss_flags = 0;
    newContext.uc_link = &mainContext;



makecontext(&newContext, (void (*)(void))funcPtr, ARG_COUNT, argPtr);

    // Add new thread to queue
    int newThreadID = add_tcb(newContext);
    switchThread(active, newThreadID);

    interruptEnable();

    return newThreadID;
}

// Saves the current thread's context, and switches to the next thread
// Returns when the current thread is switched back to naturally in queue
void threadYield()
{
    interruptDisable();

   Thread_Control_Block *next = pick_next_tcb();
    if(! next)
    {
        interruptEnable();
        return;
    }

    switchThread(active, next->id);

    interruptEnable();
}

// Wait for the specified thread to finish
// Returns when the specified thread is finished
void threadJoin(int target, void **result)
{
    interruptDisable();

    Thread_Control_Block *target_tcb = thread(target);
    if(! target_tcb)
    {
        interruptEnable();
        return;
    }

    while(target_tcb->state != THREAD_DONE
    &&    target_tcb->state != THREAD_EXITED)
    {
        awaiting = target;
        thread(active)->state = THREAD_WAITING;
        interruptEnable();
        threadYield();
        interruptDisable();
    }

    if(result) {
        *result = target_tcb->result;
    }

    interruptEnable();

    return;
}

void threadExit(void *result) {

    interruptDisable();
    Thread_Control_Block *activeThread = thread(active);

    if (active != MAIN) {
        activeThread->state = THREAD_DONE;
        activeThread->result = result;
        interruptEnable();
        threadYield();
        return;
    }
    exit(MAIN);
}

