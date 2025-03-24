#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

int is_ptr_valid(void *addr, size_t bytes, bool write)
{

    pid_t child;

    child = fork();
    assert(child >= 0);

    if (child == 0)
    {
        void *data = malloc(bytes);
        if (write)
        {
            // write to memory
            memcpy(addr, data, bytes);
        }
        else
        {
            // read from memory
            memcpy(data, addr, bytes);
        }
        exit(0);
    }
    int status;
    pid_t result = waitpid(child, &status, 0);
    assert(result >= 0);

    return (status == 0);
}

int main(void)
{
    int something;
    int *nums = malloc(sizeof(int) * 40);

    printf("ptr #1 %d\n", is_ptr_valid(&something, sizeof(int), true));
    printf("ptr #2 %d\n", is_ptr_valid((void *)(uintptr_t)112233, sizeof(int), false));
    printf("ptr #3 %d\n", is_ptr_valid(NULL, sizeof(int), true));
    printf("ptr #4 %d\n", is_ptr_valid(nums, sizeof(int) * 40000, true));
    return 0;
}