/* Dylan Mumm
 * CPSC 1020 001, Spring 2017
 * dmumm
 */

#ifndef PIXEL_H
#define PIXEL_H

#include "Color.h"
#include "Point.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;


class Pixel
{
  private:

    Color clr;
    Point pnt;

  public:

    void decidePixelColor(bool, bool);
    void setRGB(unsigned char, unsigned char, unsigned char);
    void printRGB(ofstream&);

};
#endif
