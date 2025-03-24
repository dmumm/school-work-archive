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

/* Class implementation for an overnight package */

#include "OvernightPackage.h"

/*Complete this code*/

/*This is a constructor.
 *Use member initialization to initialize the information for the base
 *class (Package)  Then follow the instruction included to complete
 *the remaining information for the constructor.*/
OvernightPackage::OvernightPackage(Person s, Person r, double w, double c,
       double f, double ff)
       : Package(s, r, w, c), additionalFee(f), flatFee(ff)
{

   /*if the additional fee is negative, intialize it to 10 cents*/

   if(f < 0)
   {
     this->additionalFee = .10;
   }
   else
   {
     this->additionalFee = f;
   }

   /* if the flat fee is negative, initialzie it to $3.00 */

   if(ff < 0)
   {
     this->flatFee = 3.00;
   }
   else
   {
     this->flatFee = ff;
   }


}

/*This function calls packages calculateCost function, adds weight * additionalFee then adds the
 flatfee and returns the value  */
double OvernightPackage::calculateCost()
{

  return (Package::calculateCost() + (weight * additionalFee) + (flatFee));


}
