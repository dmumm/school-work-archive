#include <cmath>

#include "Circle.h"

Circle::Circle()
    : Shape(0, 0, 0)
{

}

Circle::Circle(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0)
    : Shape(r, g, b)
{

}

void Circle::setCenter(double x, double y)
{
    center.setX(x);
    center.setY(y);
}

void Circle::setRadius(int radius)
{
    this->radius = radius;
}

double Circle::getCenterX()
{
    return center.getX();
}

double Circle::getCenterY()
{
   return center.getY();
}

int Circle::getRadius()
{
    return radius;
}

bool Circle::checkPoint(double x, double y)
{
    if (pow(x - getCenterX(), 2) + pow(y - getCenterY(), 2) <= pow(radius, 2))
    {
        return true;
    }

    else
    {
        return false;
    }
}
