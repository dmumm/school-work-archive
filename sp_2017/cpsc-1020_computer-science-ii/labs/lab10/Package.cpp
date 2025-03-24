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

// Class implementation for Package. Threeday and Overnight Package
//   are derived classes

#include "Package.h"

// Use intialization list to initialize packages sender and recipient variables.
// The remaining variables will be initialized in the constructor

Package::Package(Person s, Person r, double w, double c)
  : sender(s), recipient(r), weight(w), cost(c)
{

   /* Complete the following code */

   // if weight is zero, intialize it to 5 ounces

   if(w == 0)
   {
     this->weight = 5;
   }



   // if cost is zero, intialize it to 25 cents

   if(c == 0)
   {
     this->cost = .25;
   }


}

// I will provide the implementation for this function.  However ThreeDay and
// OvernightPackage will need to override this function to meet add the additional
// cost.

double Package::calculateCost()
{
   return (weight*cost);
}


Person& Package::getSender()
{
  return sender;
}
Person& Package::getRecipient()
{
  return recipient;
}
