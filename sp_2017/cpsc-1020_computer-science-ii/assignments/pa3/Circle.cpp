#include "Circle.h"

Circle::Circle()
    : Shape(0, 0, 0)
{
}

Circle::Circle(unsigned char r, unsigned char g, unsigned char b)
    : Shape(r, g, b)
{
}

void Circle::setCenter(double x, double y)
{
    c.setX(x);
    c.setY(y);
}

void Circle::setRadius(int r)
{
    this->rad = r;
}

double Circle::getX()
{
    return c.getX();
}

double Circle::getY()
{
   return c.getY();
}

int Circle::getRadius()
{
    return rad;
}

bool Circle::checkPoint(double x, double y)
{
    if (   (x - getX() * (x - getX()) + ((y - getY()) * (y - getY())) <=
           (rad * rad))  )
    {
        return true;
    }

    else
    {
        return false;
    }
}
