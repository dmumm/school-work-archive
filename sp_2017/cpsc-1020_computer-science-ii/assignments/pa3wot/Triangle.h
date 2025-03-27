#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"
#include "Point.h"

class Triangle : public Shape
{
    private:
            Point point[3]; // instances of Point that represent the 3 points that compose a triangle
    public:
           Triangle();
           Triangle(unsigned char, unsigned char, unsigned char);
           
           void setPoint(int, double, double);
           
           void getX(int);
           void getY(int);
};

#endif
