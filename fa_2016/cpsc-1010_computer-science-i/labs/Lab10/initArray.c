/*

	arrayInitWithInput() initializes an array composed
	of integers the user inputs

	arrayInitWithRand() initializes an array composed
	of random integers

*/

#include "defs.h"

void arrayInitWithInput(int array[])
{
	int i;
	for (i = 0; i < SIZE; i++)
		scanf("%d", &array[i]);
}

void arrayInitWithRand(int array[])
{
	int i;
	for (i = 0; i < SIZE ; i++)
		array[i] = rand() % 50 + 1;
}
