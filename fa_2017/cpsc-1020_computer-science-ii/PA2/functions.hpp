// Dylan Mumm, dmumm
// CPSC 1020, Fall 2017
// PA2, October 13th
// Dr. Yvon Feaster

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct Date {

int day;
int month;
int year;

};

void readBirth(Date&);
void readDate(Date&, Date);
void calculateAge(Date&, Date, Date);
void printAge(Date, Date);


#endif
