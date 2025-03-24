/* Dylan Mumm
 * CPSC 1020 001, Spring 2017
 * dmumm
 */

#include "Header.h"

// Setters

void Header::setType(string t)
{
   type = t;
}

void Header::setWidth(int w)
{
  width = w;
}

void Header::setHeight(int h)
{
  height = h;
}

void Header::setMaxRGB(int rgb)
{
  maximumRGB = rgb;
}

// Prints header to passed in ofstream

void Header::printHeader(ofstream& outPut)
{

  outPut << type << "\n" << width
         << " " << height << " "
         << maximumRGB << "\n";

}
