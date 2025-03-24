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

/* Class definitions for overnight package */

#ifndef OVERNIGHTPACKAGE_H
#define OVERNIGHTPACKAGE_H

#include "Package.h"
#include <string>
using namespace std;

class OvernightPackage:public Package
{
    public:
        OvernightPackage(Person, Person, double, double, double, double);
        double calculateCost();

    private:
        double additionalFee;
        double flatFee;
};
#endif
