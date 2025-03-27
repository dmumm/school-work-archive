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

double Triangle::getX(int i)
{
    return point[i].getX();
}

double Triangle::getY(int i)
{
   return point[i].getY();
}

bool Triangle::checkPoint(double x, double y)
{
    double a = ((point[1].getY() - point[2].getY()) * (x - point[2].getX()) + 
    	(point[2].getX() - point[1].getX()) * (y - point[2].getY())) / 
    	((point[1].getY() - point[2].getY()) * (point[0].getX() - 
    	point[2].getX()) + (point[2].getX() - point[1].getX()) * 
    	(point[0].getY() - point[2].getY()));
    
    double b = ((point[2].getY() - point[0].getY()) * (x -
  	point[2].getX()) + (point[0].getX() - point[2].getX()) *
        (y - point[2].getY())) / ((point[1].getY() - point[2].getY()) *
        (point[0].getX() - point[2].getX()) +
        (point[2].getX() - point[1].getX()) * (point[0].getY() -
        point[2].getY()));
  	
    double c = 1 - a - b;
    
    if (a >= 0 && a <= 1 && b >= 0 && b <= 1 && c >= 0 && c <= 1) // if within boundaries of triangle return true .. otherwise return false
    {
        return true;
    }
    
    else
    {
        return false;
    }
}
