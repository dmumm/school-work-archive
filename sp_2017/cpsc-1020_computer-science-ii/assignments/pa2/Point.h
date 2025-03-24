/* Dylan Mumm
 * CPSC 1020 001, Spring 2017
 * dmumm
 */

#ifndef POINT_H
#define POINT_H

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

class Point
{
    private:

      double xValue;
      double yValue;

    public:

      void setPoints(double, double);
      double getX();
      double getY();

};
#endif
