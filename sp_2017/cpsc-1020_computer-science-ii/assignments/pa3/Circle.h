#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"
#include "Point.h"

class Circle : public Shape
{
    private:

  Point c;
  int rad;

    public:

  Circle();
  Circle(unsigned char, unsigned char, unsigned char);

  void setCenter(double, double);
  void setRadius(int);

  double getX();
  double getY();

  int getRadius();

  bool checkPoint(double, double);

};





#endif
