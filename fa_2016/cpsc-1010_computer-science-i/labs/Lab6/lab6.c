/*

	Dylan Mumm
	CpSc Lab Section 006, Fall 2016
	Lab 6
	
	Program will take in a 3 digit number, check if each digit is even or odd. After doing so,
	prompts user if they want to go again. Will give warning in case of invalid input.

*/

#include <stdio.h>
#include <math.h>

int main (void) {

	int input;
	int digit1;
	int digit10;
	int digit100;
	int response;
	int responseInit;

	int start = 1;

	while(start == 1){

		printf("Enter a three-digit integer: ");
		scanf("%d", &input);

		printf("The square root of %d is %.2lf.\n", input, sqrt(input));

		digit1 = input % 10;
		digit10 = (input / 10) % 10;
		digit100 = input / 100;

		if(((digit1 % 2) == 0) && ((digit10 % 2) == 0) && ((digit100 % 2) == 0))
			printf("This number contains all even digits\n");

		else if(((digit1 % 2) > 0) && ((digit10 % 2) > 0) && ((digit100 % 2) > 0))
			printf("This number contains all odd digits\n");

		else
			printf("This number contains a mix of even and odd digits\n");

		printf("Do you want to go again? (1 for yes, 0 for no): ");

		responseInit = 1;

		while(responseInit == 1){

			scanf("%d", &response);

			if(response == 0){
				start = 0;
				responseInit = 0;
			}
				
			else if(response != 0 && response != 1)
				printf("Invalid input. Enter a 1 for yes, 0 for no: ");

			else
				responseInit = 0;
				

		}
	}

	return(0);
}






















































































































































