#ifndef MYTHREADS_COMMON_H
#define MYTHREADS_COMMON_H

#define _GNU_SOURCE

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <ucontext.h>

#include "mythreads.h"

/* ### Macros ### */

#define ARG_COUNT 3

#define UNINITIALIZED -1

#define THREAD_STANDBY 0
#define THREAD_RUNNING 1
#define THREAD_WAITING 2
#define THREAD_DONE 3
#define THREAD_EXITED 4

#define LOCK_UNLOCKED -1
#define LOCK_LOCKED 0

#define MAIN 0

typedef struct Thread_Control_Block Thread_Control_Block;


/* ### Global declarations ### */

struct Thread_Control_Block {
    int id;
    int state;
    int q_idx;
    int lock_id;
    int cond_id;

    int* result;

    ucontext_t context;

    Thread_Control_Block* next;
};

extern int active;
extern int awaiting;
extern int nextThreadID;

extern int locks[NUM_LOCKS];
extern int conditionalVariable[NUM_LOCKS][CONDITIONS_PER_LOCK];

extern Thread_Control_Block *threadQueueHead;

extern ucontext_t mainContext;

/* ### Helper declarations ### */

void interruptDisable();
void interruptEnable();
void* wrapper(thFuncPtr funcPtr, void* argPtr);

/* ### TCB declarations ### */

Thread_Control_Block *create_tcb(ucontext_t context);
Thread_Control_Block *thread(int id);
Thread_Control_Block *push_back(ucontext_t context);
Thread_Control_Block *pick_next_tcb();

void rotate_tcb();
int add_tcb(ucontext_t context);

void switchThread(int active_id, int next_id);

#endif // MYTHREADS_COMMON_H
