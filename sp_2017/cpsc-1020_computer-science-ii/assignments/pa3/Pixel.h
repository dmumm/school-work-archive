#ifndef PIXEL_H
#define PIXEL_H

#include "Color.h"
#include "Point.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

class Pixel
{

    private:

  Color clr;
  Point pnt;

    public:

  Pixel(unsigned char, unsigned char, unsigned char);
  Pixel();

  void setRGB(unsigned char, unsigned char, unsigned char);
  void printRGB(ofstream&);
  double getX();
  double getY();

};
#endif
