#ifndef IMAGE_H
#define IMAGE_H

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "Pixel.h"
#include "Header.h"

class Image
{
  private:

    Pixel pxl;
    Header hdr;

  public:

    void setHeader(string, int, int, int);
    void printHeader(ofstream&);
    void printPixelColor(ofstream&);
    void setPixelColor(unsigned char, unsigned char, unsigned char);
    void decidePixelColor(bool);

};
#endif
