#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"
#include "Point.h"

class Circle : public Shape
{
    private:
            Point center;
            int radius;
    public:
           Circle();
           Circle(unsigned char, unsigned char, unsigned char);
           
           void setCenter(double, double);
           void setRadius(int);

           double getCenterX();
           double getCenterY();
           
           int getRadius();

           bool checkPoint(double, double);
};





#endif
