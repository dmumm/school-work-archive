#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"
#include "Point.h"

class Triangle : public Shape
{
    private:

  Point v[3];

    public:

   Triangle();
   Triangle(unsigned char, unsigned char, unsigned char);

   void setVector(int, double, double);

   double getX(int);
   double getY(int);

   bool checkPoint(double, double);
};

#endif
