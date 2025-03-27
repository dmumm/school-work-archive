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

void Circle::getCenterX()
{
    center.getX();
}

void Circle::getCenterY()
{
    center.getY();
}

int Circle::getRadius()
{
    return radius;
}
