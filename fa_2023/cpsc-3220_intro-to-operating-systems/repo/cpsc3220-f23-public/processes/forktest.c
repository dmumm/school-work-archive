

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int x = 5;
    int *px = &x;

    printf("Before (%d)\n", getpid());
    pid_t pid = fork();

    if (pid == 0)
    {
        printf("I'm the child!\n");
        sleep(2);
        printf("Child out.\n");
        // exit(0);
    }
    else
    {
        // waitpid(pid, NULL, 0);
        printf("I'm the parent!\n");
    }
    (*px)++;
    printf("After %d (%d)\n", x, getpid());
}