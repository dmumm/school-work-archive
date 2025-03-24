/* Dylan Mumm
 * CPSC 1020 001, Spring 2017
 * dmumm
 */

#include "Point.h"

// Setter
void Point::setPoints(double x, double y)
{

  xValue = x;
  yValue = y;

}

// Getters

double Point::getX()
{
  return xValue;
}

double Point::getY()
{
  return yValue;
}
