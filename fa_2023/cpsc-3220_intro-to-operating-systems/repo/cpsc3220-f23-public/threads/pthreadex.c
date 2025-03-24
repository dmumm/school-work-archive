#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>

#define BIG 100000000L

uint64_t sum = 0;
pthread_mutex_t ourlock = PTHREAD_MUTEX_INITIALIZER;

void count_to_big()
{

	for (int i = 0; i < BIG; i++)
	{
		pthread_mutex_lock(&ourlock);
		sum += i; // critical section
		pthread_mutex_unlock(&ourlock);
	}
	/*pthread_mutex_lock(&ourlock);
	sum += mysum; // critical section
	pthread_mutex_unlock(&ourlock);*/
}

void *mythreadfunc(void *arg)
{
	count_to_big();
	return NULL;
}

int main(int argc, char **argv)
{
	pthread_t t[2];
	pthread_create(&t[0], NULL, mythreadfunc, NULL);
	pthread_create(&t[1], NULL, mythreadfunc, NULL);

	pthread_join(t[0], NULL);
	pthread_join(t[1], NULL);

	printf("The result is %lu\n", sum);
	return 0;
}
