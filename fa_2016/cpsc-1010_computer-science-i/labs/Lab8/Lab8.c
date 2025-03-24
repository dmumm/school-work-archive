/*

	Dylan Mumm
	CpSc 1010 Lab Section 006, Fall 2016
	Lab #2

	Program Description:
	
	User inputs 20 integers into Array1, and Array2 is randomly generated of integers between 1 and 50,
	inclusive. Program finds and prints the second highest integer in each array. Program than calculates
	and prints the inner product of the two arrays.

*/

#include <stdio.h>
#include <limits.h>

int main(void){

	int array1[20];
	int array2[20];

	int i;
	int pairProduct;
	int innerProduct;

	int max1 = INT_MIN;
	int max2 = INT_MIN;
	int second1 = INT_MIN;
	int second2 = INT_MIN;
	

	printf("Enter 20 integers:\n");

	for(i = 0; i < 20; i++)
		scanf("%d", &array1[i]);

	printf("\n\narray 1:\n");

	for(i = 0; i < 20; i++)
		printf("%d\n", array1[i]);

	for(i = 0; i < 20; i++)
		array2[i] = rand() % 50 + 1;

	printf("\n\n");

	printf("array 2:\n");

	for(i = 0; i < 20; i++)
		printf("%d\n", array2[i]);

	printf("\n");

	for(i = 0; i < 20; i++)
	{

		if(array1[i] > max1)
		{
			second1 = max1;
			max1 = array1[i];
		}
		
		if(array2[i] > max2)
		{
			second2 = max2;
			max2 = array2[i];
		}

	}

	printf("Second highest from Array1 is: %d\n", second1);
	printf("Second highest from Array2 is: %d\n\n", second2);

	for(i = 0; i < 20; i++)
		innerProduct = innerProduct + (array1[i] * array2[i]);

	printf("inner product is: %d\n", innerProduct);

	return(0);

}
