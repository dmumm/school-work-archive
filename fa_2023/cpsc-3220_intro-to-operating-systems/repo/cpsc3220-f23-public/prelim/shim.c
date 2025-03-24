#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

typedef int (*randlikefunction)(void);

__attribute__((constructor)) void shim_init()
{
    printf("Init!\n");
}

__attribute__((destructor)) void shim_destroy()
{
    printf("Done!\n");
}

int rand(void)
{
    randlikefunction oldrand = dlsym(RTLD_NEXT, "rand");
    if (oldrand != NULL)
    {
        return oldrand() % 100;
    }
    else
    {
        printf("AAAAAAAAH! my shim doesn't work.");
        return 5;
    }
}
