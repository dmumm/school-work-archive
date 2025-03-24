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

/* Class implementation for a 3 day package */

#include "ThreeDay.h"

/*Complete this code*/

/*This is a constructor.
 *Use member initialization to initialize the information for the base
 *class (Package)  Then follow the instruction included to complete
 *the remaining information for the constructor.*/

ThreeDay::ThreeDay(Person s, Person r, double w, double c, double f)
: Package(s, r, w, c), additionalFee(f)
{

  // if additional fee is negative, intialize it to ten cents

  if(f < 0)
  {
    this->additionalFee = .10;
  }
  else
  {
    this->additionalFee = f;
  }

}


/*This function calls the packages calculateCost function,
 *then adds (weight * additionalFee) to it */
double ThreeDay::calculateCost()
{

  return (Package::calculateCost() + (weight * additionalFee));

}
