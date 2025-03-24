#include "myalloc.h"

void* malloc(size_t size)
{
    return my_malloc(size);
}

void free(void* ptr)
{
    my_free(ptr);
}

void* calloc(size_t nitems, size_t size)
{
    return my_calloc(nitems, size);
}

void* realloc(void* ptr, size_t size)
{
    return my_realloc(ptr, size);
}