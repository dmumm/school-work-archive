/*
	Dylan Mumm
	CpSc 1010 Lab Section 006, Fall 2016
	Lab #7

	A variant of a standard Linux command, echo. In the echo
	command, arguments passed from the command line are all printed
	out, seperated by spaces, with a newline characer at the end.

	reverse_echo does the same, except the arguments entered at the
	command line are printed out in reverse order. For example, if
	the executableis renamed as reverse_echo and you type the 
	following to run it...

	./reverse_echo testing 1 2 3

	the program will print the following....

	3 2 1 testing

	---

	Compile Instructions:	gcc -Wall -o reverse_echo reverse_echo.c

	Run Instructions:	./reverse_echo <arg1> <arg2> ... <argn>
*/

#include <stdio.h>

int main(int argc, char *argv[]) {
	int i;

	printf("argc is:  %d\n", argc);	

	// finish the rest of the for loop 
	for (i = argc - 1; i >= 0; i--)
	{
		printf("%s ", argv[i]);
	


		
			
	}

	printf("\n\n");

	return 0;
}
