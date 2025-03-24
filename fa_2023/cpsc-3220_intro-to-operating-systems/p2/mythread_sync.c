#include "mythread_common.h"

void threadLock(int lockNum) {
    interruptDisable();
    while (locks[lockNum] == LOCK_LOCKED) {
        interruptEnable();
        threadYield();
        interruptDisable();
    }
    locks[lockNum] = LOCK_LOCKED;
    interruptEnable();
}

void threadUnlock(int lockNum) {
    interruptDisable();
    locks[lockNum] = LOCK_UNLOCKED;
    interruptEnable();
}


void threadSignal(int lockNum, int cond_id) {
    interruptDisable();
    if (conditionalVariable[lockNum][cond_id] == MAIN) {
        interruptEnable();
        return;
    }
    conditionalVariable[lockNum][cond_id]--;
    Thread_Control_Block *tcb = threadQueueHead;
    while (tcb) {
        if (tcb->lock_id == lockNum && tcb->cond_id == cond_id) {
            tcb->q_idx--;
        }
        tcb = tcb->next;
    }
    interruptEnable();
}


void threadWait(int lockNum, int cond_id) {



    Thread_Control_Block *tcb = thread(active);
    tcb->lock_id = lockNum;
    tcb->cond_id = cond_id;
    conditionalVariable[lockNum][cond_id]++;
    tcb->q_idx = conditionalVariable[lockNum][cond_id];

    locks[lockNum] = LOCK_UNLOCKED;
    while (tcb->q_idx > MAIN) {
        interruptEnable();
        threadYield();
        interruptDisable();
    }

    tcb->lock_id = UNINITIALIZED;
    tcb->q_idx = UNINITIALIZED;
    tcb->cond_id = UNINITIALIZED;

    interruptEnable();
    threadLock(lockNum);
}