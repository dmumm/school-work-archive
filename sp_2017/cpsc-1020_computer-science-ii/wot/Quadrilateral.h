#ifndef QUADRILATERAL_H
#define QUADRILATERAL_H

#include "Shape.h"
#include "Point.h"

class Quadrilateral : public Shape
{
    private:
            Point point[4];
            Point center;
    public:
           Quadrilateral();
           Quadrilateral(unsigned char, unsigned char, unsigned char);
           
           void setPoint(int, double, double);
           
           double getX(int);
           double getY(int);
           
           bool checkPoint(double, double);
};



#endif
