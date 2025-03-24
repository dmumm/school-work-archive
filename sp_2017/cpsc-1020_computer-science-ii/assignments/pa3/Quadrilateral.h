#ifndef QUADRILATERAL_H
#define QUADRILATERAL_H

#include "Shape.h"
#include "Point.h"

class Quadrilateral : public Shape
{
    private:

  Point v[4];

    public:

   Quadrilateral();
   Quadrilateral(unsigned char, unsigned char, unsigned char);

   void setVector(int, double, double);

   double getX(int);
   double getY(int);

   bool checkPoint(double, double);
};

#endif
