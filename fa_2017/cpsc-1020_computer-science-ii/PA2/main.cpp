// Dylan Mumm, dmumm
// CPSC 1020, Fall 2017
// PA2, October 13th
// Dr. Yvon Feaster

#include "functions.hpp"


int main(int argc, char *argv[])
{

    Date birth;
    Date date;
    Date difference;

    readBirth(birth);
    readDate(date, birth);
    calculateAge(difference, date, birth);
    printAge(difference, date);


    return 0;
}
 
