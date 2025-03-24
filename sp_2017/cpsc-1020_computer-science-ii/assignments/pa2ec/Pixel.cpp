/* Dylan Mumm
 * CPSC 1020 001, Spring 2017
 * dmumm
 */

#include "Pixel.h"

// If passed in bool is true, passes in variables to Color's setRGB function
// that make pixel yellow, if false, passes in variables that make pixel black
void Pixel::decidePixelColor(bool decision1, bool decision2)
{
  if(decision1 == true && decision2 == false)
  {
    clr.setRGB((unsigned char)205, (unsigned char)20, (unsigned char)40);
  }
  else if((decision1 == true && decision2 == true))
  {
    clr.setRGB((unsigned char)0, (unsigned char)120, (unsigned char)60);
  }
  else
  {
    clr.setRGB((unsigned char)0, (unsigned char)0, (unsigned char)0);
  }
}

// Passes variables into Color's setRGB function
void Pixel::setRGB(unsigned char r, unsigned char b, unsigned char g)
{

  clr.setRGB(r, g, b);

}

// Access Color's getters to print Pixel's RGB values
void Pixel::printRGB(ofstream& outPut)
{

  outPut << clr.getRed() << clr.getGreen() << clr.getBlue();

}
