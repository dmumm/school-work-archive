#include "Quadrilateral.h"

#include <iostream>

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

double Quadrilateral::getX(int i)
{
    return point[i].getX();
}

double Quadrilateral::getY(int i)
{
   return point[i].getY();
}

bool Quadrilateral::checkPoint(double x, double y)
{
    //center.setX(((point[0].getX() + point[1].getX() + point[2].getX() + point[3].getX()) / 4.00));
    //center.setY(((point[0].getY() + point[1].getY() + point[2].getY() + point[3].getY()) / 4.00));

    
    //Triangle 1
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
    
    if (a >= 0 && a <= 1 && b >= 0 && b <= 1 && c >= 0 && c <= 1)
    {
        return true;
    }
    

    // Triangle 2
    double d = ((point[3].getY() - point[0].getY()) * (x - point[0].getX()) + 
    	(point[0].getX() - point[3].getX()) * (y - point[0].getY())) / 
    	((point[3].getY() - point[0].getY()) * (point[2].getX() - 
    	point[0].getX()) + (point[0].getX() - point[3].getX()) * 
    	(point[2].getY() - point[0].getY()));
    	
    double e = ((point[0].getY() - point[2].getY()) * (x -
  	point[0].getX()) + (point[2].getX() - point[0].getX()) *
        (y - point[0].getY())) / ((point[3].getY() - point[0].getY()) *
        (point[2].getX() - point[0].getX()) +
        (point[0].getX() - point[3].getX()) * (point[2].getY() -
        point[0].getY()));
        
    double f = 1 - d - e;
    
    if (d >= 0 && d <= 1 && e >= 0 && e <= 1 && f >= 0 && f <= 1)
    {
        return true;
    }
    
    
    // Triangle 3
    double g = ((point[2].getY() - point[1].getY()) * (x - point[1].getX()) + 
    	(point[1].getX() - point[2].getX()) * (y - point[1].getY())) / 
    	((point[2].getY() - point[1].getY()) * (point[3].getX() - 
    	point[1].getX()) + (point[1].getX() - point[2].getX()) * 
    	(point[3].getY() - point[1].getY()));
    	
    double h = ((point[1].getY() - point[3].getY()) * (x -
  	point[1].getX()) + (point[3].getX() - point[1].getX()) *
        (y - point[1].getY())) / ((point[2].getY() - point[1].getY()) *
        (point[3].getX() - point[1].getX()) +
        (point[1].getX() - point[2].getX()) * (point[3].getY() -
        point[1].getY()));
    
    double i = 1 - g - h;
    
    if (g >= 0 && g <= 1 && h >= 0 && h <= 1 && i >= 0 && i <= 1)
    {
        return true;
    }
}
