/*
	Dylan Mumm
	CpSc 1010 Lab Section 006, Fall 2016
	Lab #10

	Program Description:

	User inputs 20 integers into Array1, and Array2 is randomly generated
	of integers between 1 and 50, inclusive. Program finds and prints the
	second highest integer in each array. Program then calculates and
	prints the inner product of the two arrays.

*/

#include "defs.h"

int main()
{
	int array1[20];
	int array2[20];

	printf("Enter 20 integers:\n");
	arrayInitWithInput(array1);

	printf("\narray 1:\n");
	printArray(array1);

	printf("\narray 2:\n");
	arrayInitWithRand(array2);
	printArray(array2);

	int secondHigh = findSecondHighestValue(array1); 

	printf("\nSecond highest from array1 is: %d\n", secondHigh);

	printf("Second highest from array2 is: %d\n",
		findSecondHighestValue(array2));

	printf("\ninner product is: %d\n",
		findInnerProduct(array1, array2));

	return(0);
}
