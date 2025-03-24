

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>

jmp_buf jumppoint;

void mysignalhandler(int sig)
{
    printf("ha ha, I won't die.");
    longjmp(jumppoint, 1);
}

int main()
{
    signal(SIGINT, mysignalhandler);
    signal(SIGTERM, mysignalhandler);
    signal(SIGSEGV, mysignalhandler);

    while (true)
    {
        printf("Wasting your cycles - %d\n", getpid());

        memset(&jumppoint, 0, sizeof(jmp_buf));
        if (setjmp(jumppoint) == 0)
        {
            int *p = NULL;
            *p = 45;
        }
        else
        {
            printf("stuff hit the fan\n");
        }

        sleep(1);
    }
}