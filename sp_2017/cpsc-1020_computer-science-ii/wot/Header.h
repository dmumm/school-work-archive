#ifndef HEADER_H
#define HEADER_H

#include <string>

using namespace std;

class Header
{
  private:
          string magicNum;
          int width;
          int height;
          int maxRGB;
  public:
          Header();
          Header(string, int, int, int);
          string getMagicNum();
          int getWidth();
          int getHeight();
          int getMaxRGB();
};
#endif
