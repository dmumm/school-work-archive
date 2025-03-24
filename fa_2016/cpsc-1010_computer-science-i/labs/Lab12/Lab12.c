/*

	Dylan Mumm
	CpSc 1010 Lab Section 006, Fall 2016
	Lab #11

	Prints a histogram for a series of numbers beginning with 2, up to a value
	entered by the user at the command line. Each line of the histogram will
	consist of at least q character, also specified at the command line. The
	number of characters per line will correpond to the sum of the divisors
	(not including the number itself) of the value for that line.



*/

#include <stdio.h>
#include <math.h>


int sumOfDivisors(int aNum);

int main(int argc, char *argv[])
{
	int num, i, j;
	char input;

	sscanf(argv[1], "%d", &num);
	sscanf(argv[2], "%c", &input);

	for(i = 2; i <= num; i++){
		
		printf("\n%3d", i);
		printf("  ");

		for(j = 0; j < sumOfDivisors(i); j++)
		{
		
		printf("%c", input);

		}

	}

	return 0;

}

int sumOfDivisors(int aNum){

	int sum = 1;
	int i, remainder, high;

	for (i = 2; i <= sqrt(aNum); i++)
	{
		remainder = aNum % i;
		if(remainder == 0)
		{
			high = aNum / i;
			sum = sum + i;
			if (high != i)
			{
				sum = sum + high;
			}
		}
	}

	return sum;


}
