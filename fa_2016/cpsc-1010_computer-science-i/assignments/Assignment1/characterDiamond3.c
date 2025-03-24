/* 

	Dylan Mumm
	CpSc 1010, Lab Section 006
	Fall 2016
	Assignment #1 // Phase #1

	Prints a character diamond, beginning with a character entered by the user,
	and the rows are determined by an odd number inputed by the user.

*/

#include <stdio.h>

int main (void) {

	// variables

	char inputChar;
	int  inputSize;
	int  maximumInput;
	int  start;
	int  i;
	int  j;

	// Initial instructions and user inputs

	printf("\n\nThis program will print a character diamond.\n\n");

	printf("Enter a character: ");
	scanf("%c", &inputChar);

	maximumInput = 128 - inputChar;
	maximumInput = (maximumInput > 40) ? 40 : maximumInput;

	start = 0;
	while(start == 0)
	{
		printf("\nEnter an odd number at least 1 but less than %d: ", maximumInput);
		scanf("%d", &inputSize);
		printf("\n");
		
		if((inputSize % 2 > 0) && (inputSize > 1) && (inputSize < maximumInput))
			start = 1;
		 
	}

	// For loop to create rest of triangle

	for(i = 0; i < (inputSize / 2) + 1; i++)
	{

		// Initial spacing that scales with rows. 
		// Spaces = Size - (Row * 2)

		for(j = 0; j < 40 - (i * 2); j++)
		{
			printf(" ");
		}

		// First group of characters:
		// Starting with user's character, ASCII
		// value goes up by one after each interation
		// of loop. Ends after printing middle column.

		for(j = 0; j < (i * 2) + 1; j++)
		{
			printf("%c", inputChar+j);
		}

		// Second group of characters:
		// Starting with one value before middle
		// character, ASCII value goes down by one
		// after each iteration. Ends after printing
		// user's inputted character

		for(j = i * 2; j > 0; j--)
		{
			printf("%c", inputChar+j-1);
		}

		// Line break

		printf("\n");
	}

	// Same thing as above for loop, but this time it
	// generates the rows in reverse order

	for(i = (inputSize / 2) - 1; i >= 0; i--)
	{
		for(j = 0; j < 39 - (i * 2) + 1; j++)
		{
			printf(" ");
		}
		for(j = 0; j < (i * 2) + 1; j++)
		{
			printf("%c", inputChar+j);
		}
		for(j = i * 2; j > 0; j--)
		{
			printf("%c", inputChar+j - 1);
		}
	
		printf("\n");
	}



	return(0);

}
