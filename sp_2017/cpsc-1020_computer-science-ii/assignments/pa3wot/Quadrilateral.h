#ifndef QUADRILATERAL_H
#define QUADRILATERAL_H

#include "Shape.h"
#include "Point.h"

class Quadrilateral : public Shape
{
    private:
            Point point[4];
    public:
           Quadrilateral();
           Quadrilateral(unsigned char, unsigned char, unsigned char);
           
           void setPoint(int, double, double);
           
           void getX(int);
           void getY(int);
};



#endif
