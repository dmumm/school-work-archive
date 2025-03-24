/*
 * Dylan Mumm
 * dmumm
 * Lab #1, Section: 004
 * Nick Glyder
 *
 * A simple program that prints a hello world
 * ascii art. 
 *
 */

#include "stdio.h"

int main(int argc, char const *argv[])
{
	const char* s = ""

	"H   H   EEEEE   L       L        OOO\n"
	"H   H   E       L       L       O   O\n"
        "HHHHH   EEEE    L       L       O   O\n" 
        "H   H   E       L       L       O   O\n"
        "H   H   EEEEE   LLLLL   LLLLL    OOO\n"


        "W     W    OOO    RRRRR   L       DDDD     !!\n"
        "W     W   O   O   R   R   L       D   D    !!\n"
        "W  W  W   O   O   RRRR    L       D   D    !!\n"
        " W W W    O   O   R R     L       D   D    !!\n"
        "  W W      OOO    R   R   LLLLL   DDDD     oo\n";

	printf("%s", s);

	return(0);
}


