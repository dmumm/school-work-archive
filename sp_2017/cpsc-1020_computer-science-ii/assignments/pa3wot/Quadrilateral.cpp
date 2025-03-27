#include "Quadrilateral.h"

Quadrilateral::Quadrilateral()
    : Shape(0, 0, 0)
{
    
}

Quadrilateral::Quadrilateral(unsigned char r = 0, unsigned char g = 0, 
    unsigned char b = 0) : Shape(r, g, b)
{

}

void Quadrilateral::setPoint(int i, double x, double y)
{
    point[i].setX(x);
    point[i].setY(y);
}

void Quadrilateral::getX(int i)
{
    point[i].getX();
}

void Quadrilateral::getY(int i)
{
    point[i].getY();
}
