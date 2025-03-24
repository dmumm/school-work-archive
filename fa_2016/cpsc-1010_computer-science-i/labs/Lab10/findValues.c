/*

	findSecondHighestValue() figures out what value in
	 an array has the second highest value

	findInnerProduct figures out the inner product of
	two arrays

*/

#include "defs.h"

int findSecondHighestValue(int array[])
{
	int max = INT_MIN;
	int second = INT_MIN;
	int i;

	for (i = 0; i < SIZE; i++)
	{
		if (array[i] > max)
		{
			second = max;
			max = array[i];
		}
	}

	return second;
}

int findInnerProduct(int array1[], int array2[])
{
	int innerProduct = 0;
	int i;

	for(i = 0; i < SIZE; i++)
		innerProduct = innerProduct + (array1[i] * array2[i]);

	return innerProduct;
}


