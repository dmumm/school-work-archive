/* Dylan Mumm
 * CPSC 1020 001, Spring 2017
 * dmumm
 */

#include "Image.h"

// Passes all variables into Header's setters
void Image::setHeader(string type, int w, int h, int max)
{

  hdr.setType(type);
  hdr.setWidth(w);
  hdr.setHeight(h);
  hdr.setMaxRGB(max);

}

// Passes ofstream into Header's printHeader function
void Image::printHeader(ofstream& outPut)
{

  hdr.printHeader(outPut);

}

// Passes ofstream into Pixel's printRGB function
void Image::printPixelColor(ofstream& outPut)
{

  pxl.printRGB(outPut);

}

// Passes variables into Pixel's setRGB function
void Image::setPixelColor(unsigned char r, unsigned char g, unsigned char b)
{

  pxl.setRGB(r, g, b);

}


// Passes bool into Pixel's decidePixelColor function
void Image::decidePixelColor(bool decision1, bool decision2)
{

  pxl.decidePixelColor(decision1, decision2);

}
