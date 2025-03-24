#include "Triangle.h"

Triangle::Triangle()
    : Shape(0, 0, 0)
{
}

Triangle::Triangle(unsigned char r, unsigned char g, unsigned char b)
    : Shape(r, g, b)
{
}

void Triangle::setVector(int i, double x, double y)
{
    v[i].setX(x);
    v[i].setY(y);
}

double Triangle::getX(int i)
{
    return v[i].getX();
}

double Triangle::getY(int i)
{
   return v[i].getY();
}

bool Triangle::checkPoint(double x, double y)
{
   double a, b, c;

   a = ((v[1].getY() - v[2].getY()) * (x - v[2].getX()) +
    	  (v[2].getX() - v[1].getX()) * (y - v[2].getY())) /
    	 ((v[1].getY() - v[2].getY()) * (v[0].getX() - v[2].getX()) +
        (v[2].getX() - v[1].getX()) * (v[0].getY() - v[2].getY()));

   b = ((v[2].getY() - v[0].getY()) * (x -v[2].getX()) +
        (v[0].getX() - v[2].getX()) * (y - v[2].getY())) /
       ((v[1].getY() - v[2].getY()) * (v[0].getX() - v[2].getX()) +
        (v[2].getX() - v[1].getX()) * (v[0].getY() - v[2].getY()));

   c = 1 - a - b;

   if (a >= 0 && a <= 1 &&
        b >= 0 && b <= 1 &&
        c >= 0 && c <= 1) {

        return true;
   }

   else
   {
       return false;
   }
}
