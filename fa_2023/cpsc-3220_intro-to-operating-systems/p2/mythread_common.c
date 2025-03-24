#include "mythread_common.h"

/* ### Global Declrataions */

int active;
int awaiting;
int nextThreadID;

int locks[NUM_LOCKS];
int conditionalVariable[NUM_LOCKS][CONDITIONS_PER_LOCK];

Thread_Control_Block *threadQueueHead;

ucontext_t mainContext;


/* ### Global assignments */

int interruptsAreDisabled = 0;

/* ### Helper declarations ### */

void interruptDisable()
{
    assert(!interruptsAreDisabled);
    interruptsAreDisabled = 1;
}

void interruptEnable()
{
    assert(interruptsAreDisabled);
    interruptsAreDisabled = 0;
}

void* wrapper(thFuncPtr funcPtr, void* argPtr)
{
    interruptEnable();
    void* result = funcPtr(argPtr);
    threadExit(result);
    return result;
}

/* ### TCB  ### */


Thread_Control_Block *create_tcb(ucontext_t context)
{
    Thread_Control_Block *tcb = malloc(sizeof(Thread_Control_Block));
    tcb->id = nextThreadID;
    tcb->state = THREAD_STANDBY;
    tcb->q_idx = UNINITIALIZED;
    tcb->cond_id = UNINITIALIZED;
    tcb->lock_id = UNINITIALIZED;
    tcb->context = context;
    tcb->next = NULL;
    nextThreadID++;
    return tcb;
}

Thread_Control_Block *thread(int id)
{
    Thread_Control_Block *tcb = threadQueueHead;
    while (tcb) {
        if (tcb->id == id) {
            return tcb;
        }
        tcb = tcb->next;
    }
    return NULL;
}

Thread_Control_Block *push_back(ucontext_t context)
{
    Thread_Control_Block *tcb = create_tcb(context);
    Thread_Control_Block *last, *iter = threadQueueHead;
    if (!iter) {
        threadQueueHead = tcb;
        return tcb;
    }
    while (iter) {
        last = iter;
        iter = iter->next;
    }
    last->next = tcb;
    return tcb;
}

Thread_Control_Block *pick_next_tcb()
{
    Thread_Control_Block *tcb = threadQueueHead;
    Thread_Control_Block *current_tcb = thread(active);
    Thread_Control_Block *waiting_for_tcb = thread(awaiting);

    if(current_tcb->state == THREAD_WAITING
    && waiting_for_tcb->state == THREAD_DONE)
    {
        current_tcb->state = THREAD_RUNNING;
        tcb = waiting_for_tcb;
        awaiting = UNINITIALIZED;
        return tcb;
    }

    int i = 0;
    while (tcb
    && tcb->state != THREAD_STANDBY
    && !(tcb->state == THREAD_WAITING && tcb->id != active))
    {
        tcb = tcb->next;
        i++;
    }

    for (; i >= 0; i--) rotate_tcb();
    return tcb;
}

void rotate_tcb()
{
    if(threadQueueHead == NULL
    || threadQueueHead->next == NULL)
    {
        return;
    }

    Thread_Control_Block *tail_tcb = threadQueueHead;

    while (tail_tcb)
    {
        if (!tail_tcb->next) break;

        tail_tcb = tail_tcb->next;
    }

    tail_tcb->next = threadQueueHead;

    threadQueueHead = threadQueueHead->next;

    tail_tcb->next->next = NULL;
}

int add_tcb(ucontext_t context)
{
    return push_back(context)->id;
}

void switchThread(int active_id, int next_id) {
    if (active_id == next_id)
        return;

    Thread_Control_Block* active_tcb = thread(active_id);
    Thread_Control_Block* next_tcb = thread(next_id);
    ucontext_t* active_context = &(active_tcb->context);
    ucontext_t* next_context = &(next_tcb->context);

    if (active_tcb->state == THREAD_RUNNING)
    {
        active_tcb->state = THREAD_STANDBY;
    }

    active = next_id;
    next_tcb->state = THREAD_RUNNING;

    getcontext(active_context);
    swapcontext(active_context, next_context);

    if(next_tcb->state == THREAD_RUNNING)
    {
        next_tcb->state = THREAD_STANDBY;
    }

    if(active_tcb->state == THREAD_STANDBY)
    {
        active_tcb->state = THREAD_RUNNING;
    }

    active = active_id;
}