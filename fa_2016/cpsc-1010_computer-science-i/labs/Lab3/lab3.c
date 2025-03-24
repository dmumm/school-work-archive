/* 
	Dylan Mumm
	CpSc 1010 Lab Section 006, Fall 2016
	Lab #2

	Program declared several variables, assings some values, then plugs those into expressions and solves 
	and prints

	No, it gave "floating point exception", because as the variables were integers, it rounded 
	(intVar4 / intVar3) into 0, causing a division of 0.

*/

#include <stdio.h>

int main (void) {

	int intVar1;
	int intVar2;
	int intVar3;
	int intVar4;

	int exp1;
	int exp2;
	int exp3;
	int exp4;

	intVar1 = 4;
	intVar2 = 3;

	exp1 = intVar1 + (5 * intVar2 / 3) * intVar1;
	exp2 = ((intVar1 + 5) * intVar2) / (3 * intVar1);

	fprintf(stdout,"intVar1  = %d and intVar2 = %d\n\n", intVar1, intVar2);
	fprintf(stdout,"Expression values are:\nexp1 = %d\nexp2 = %d\n\n\n", exp1, exp2);

	intVar3 = 3;
	intVar4 = 5;

	exp3 = intVar3 + ((4 * intVar4) / (3 * intVar3));
	exp4 = (intVar4 % 2) / (intVar4 / intVar3);

	fprintf(stdout,"intVar3  = %d and intVar4 = %d\n\n", intVar3, intVar4);
        fprintf(stdout,"Expression values are:\nexp3 = %d\nexp4 = %d\n", exp3, exp4);

	return 0;

}
