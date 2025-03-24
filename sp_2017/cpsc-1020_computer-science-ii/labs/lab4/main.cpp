/*
 * Dylan Mumm
 * dmumm
 * Lab 4
 * Lab Section: 004
 * Nick glyder
 */



#include <iostream>
#include "functions.h"

int main(void)
{
  double width;
  double height;
  int i, j;

  point_t points[3];

  std::cout << "Enter width of plane" << std::endl;
  std::cin  >> width;
  std::cout << "Enter height of plane" << std:endl;
  std::cin  >> height;

  point_t *pointsArray = new point_t(width, height);

  std::cout << "Enter three points needed to define a triangle on the plane" 
            << std::endl;

  std::cout << "Enter Point 1 (x then y):";
  std::cin  >> points[0].x;
  std::cin  >> points[0].y;

  std::cout << "Enter Point 2 (x then y):";
  std::cin  >> points[1].x;
  std::cin  >> points[1].y;

  std::cout << "Enter Point 3 (x then y):";
  std::cin  >> points[2].x;
  std::cin  >> points[2].y;

  for(i = 0; i < height ; i++)
  {
    for(j = 0; j < width; j++)
    {
	checkPoint(points[], arrayPoint[i][j];
	std::cout << i << ", " << j << end;




    }
  }








}
