#ifndef SHAPE_H
#define SHAPE_H

#include "Color.h"
#include <fstream>

using namespace std;

class Shape
{
    private:

  Color clr;

    public:

  Shape();
  Shape(unsigned char, unsigned char, unsigned char);

  void setRGB(unsigned char, unsigned char, unsigned char);

  unsigned char getRed();
  unsigned char getGreen();
  unsigned char getBlue();

};

#endif
