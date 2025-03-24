#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <fstream>


using namespace std;

class Header
{
    private:

  string type;
  int width;
  int height;
  int maxRGB;

    public:

  Header();
  Header(int, int, int, string);

  string getType();
  int getWidth();
  int getHeight();
  int getMaxRGB();

};
#endif
