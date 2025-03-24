/*
	Dylan Mumm
	CpSc 1010 Lab Section 006, Fall 2016
	Lab #8

	Program Description:

	User inputs 20 integers into Array1, and Array2 is randomly generated of integers between 1 and 50,
	inclusively, Program finds and prints the second highest integer in each array. Program then 
	calculates and prints the inner product of the two arrays.
*/

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void arrayInitWithInput(int[], int);
void arrayInitWithRand(int[], int);
void printArray(int[], int);
int  findSecondHighestValue(int[], int);
int  findInnerProduct(int[], int[], int);

int main()
{
	int array1[20];
	int array2[20];
	int size = 20;

	printf("Enter 20 integers:\n");
	arrayInitWithInput(array1, size);

	printf("\n\narray 1:\n");
	printArray(array1, size);

	printf("array 2:\n\n");
	arrayInitWithRand(array2, size);
	printArray(array2, size);

	printf("Second highest from Array1 is: %d\n", 
		findSecondHighestValue(array1, size));

	printf("Second highest fron Array2 is: %d\n", 
		findSecondHighestValue(array2, size));

	printf("inner product is: %d\n",
		findInnerProduct(array1, array2, size));

	return(0);
	
}

void arrayInitWithInput(int array[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		scanf("%d", &array[i]);
	
}

void arrayInitWithRand(int array[], int size)
{
	int i;
	for(i = 0; i < size; i++)
		array[i] = rand() % 50 + 1;

}

void printArray(int array[], int size)
{
	int i;
	for(i = 0; i < size; i++)
		printf("%d\n", array[i]);

}

int findSecondHighestValue(int array[], int size)
{
	int max = INT_MIN;
	int second = INT_MIN;
	int i;

	for(i = 0; i < size; i++)
	{
		if(array[i] > max)
		{
			second = max;
			max = array[i];
		}
	}
	
	return second;
}

int findInnerProduct(int array1[], int array2[], int size) 
{
	int innerProduct;
	int i;

	for(i = 0; i < size; i++)
		innerProduct = innerProduct + (array1[i] * array2[i]);

	return innerProduct;
}


