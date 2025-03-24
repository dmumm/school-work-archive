/*
	Dylan Mumm
	CpSc 1010 Lab Section 006, Fall 2016
	Lab #2
 
	Program description:
	This program asks the user to enter two numbers: one for the base of 
	a triangle, one for the height.  It then calculates the area of the 
	triangle and shows the results to the user.

	The scanf() function is used for user input and also comes from stdio.h
	like printf().

	This is adapted from Participation Activity 1.6.2 in zyBooks.
*/

// When my base and height were 3, and 5, my answer was 7.5 becaue (3 * 5) = 15, and (15 / 2) equals 7.5


#include <stdio.h>

double  main (void) {

	double triBase = 0; // made double for cleaner math
	double triHeight = 0; // made double for cleaner math
	double triArea = 0;  // originally had ":" instead of ";" 

	// Get user input
	printf("Enter triangle base (cm): "); // had no semi-colon, print instead of printf
	scanf("%lf", &triBase); // didn't have closed quotes after, asked for double despite variables being integers

	printf("Enter triangle height (cm): "); // didn't close quotes
	scanf("%lf", &triHeight); // didn't have "and" sign

	/* Calculate triangle area */

	triArea = (triBase * triHeight) / 2; // was commented out, had colon instead of semi-colon

	/* Print triangle base, height, area */
	printf("Triangle area = (");
	printf("%lf", triBase); // asked for double despite variable being integer
	printf(" * ");
	printf("%lf", triHeight); // simply printed "triHeight" instead of its value
	printf(") / 2 = ");
	printf("%lf", triArea);
	printf(" cm^2\n");

	return 0;
}

