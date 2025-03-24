/* Dylan Mumm
 * CPSC 1020 001, Spring 2017
 * dmumm
 */

#ifndef COLOR_H
#define COLOR_H

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

class Color
{
  private:

    unsigned char red;
    unsigned char green;
    unsigned char blue;

  public:

    void setRGB(unsigned char, unsigned char, unsigned char);

    unsigned char getRed();
    unsigned char getGreen();
    unsigned char getBlue();

};

#endif
