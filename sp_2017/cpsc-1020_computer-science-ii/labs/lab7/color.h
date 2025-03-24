/*
  Dylan Mumm
  dmumm
  Lab 7, 004
  Nick Glyder
*/

#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <fstream>


using namespace std;


class Color
{
  private:

    unsigned char red;
    unsigned char green;
    unsigned char blue;

  public:

    Color(unsigned char, unsigned char, unsigned char);
    Color();

    void setRed(unsigned char );
    void setGreen(unsigned char);
    void setBlue(unsigned char);

    unsigned char getRed();
    unsigned char getGreen();
    unsigned char getBlue();

};


#endif
