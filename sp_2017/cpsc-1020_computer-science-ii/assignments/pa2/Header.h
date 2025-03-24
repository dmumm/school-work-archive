/* Dylan Mumm
 * CPSC 1020 001, Spring 2017
 * dmumm
 */

#ifndef HEADER_H
#define HEADER_H

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;


class Header
{
  private:

    string type;
    int width;
    int height;
    int maximumRGB;

  public:

    void setType(string);
    void setWidth(int);
    void setHeight(int);
    void setMaxRGB(int);
    
    void printHeader(ofstream&);

};

#endif
