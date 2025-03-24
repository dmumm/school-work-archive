/* Dylan Mumm
 * dmumm
 * Lab 10
 * Nick Glyder, Section 004
 *
 * Victor Gamble
 * mlgambl
 * Lab 10
 * Nick Glyder, Section 005
 */

/* Class definitions for a three day package */

#ifndef THREEDAY_H
#define THREEDAY_H

#include "Package.h"
#include <string>
using namespace std;

class ThreeDay:public Package
{
   public:
	ThreeDay(Person, Person, double, double, double);
	double calculateCost();

   private:
	double additionalFee;
};
#endif
