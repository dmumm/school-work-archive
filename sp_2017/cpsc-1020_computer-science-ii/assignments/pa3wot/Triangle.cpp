#include "Triangle.h"

Triangle::Triangle()
    : Shape(0, 0, 0)
{

}

Triangle::Triangle(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0)
    : Shape(r, g, b)
{

}

void Triangle::setPoint(int i, double x, double y)
{
    point[i].setX(x);
    point[i].setY(y);
}

void Triangle::getX(int i)
{
    point[i].getX();
}

void Triangle::getY(int i)
{
    point[i].getY();
}
