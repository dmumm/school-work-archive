#include "Header.h"

Header::Header()
{
    magicNum = "";
    width = 0;
    height = 0;
    maxRGB = 0;
}

Header::Header(string magicNum, int width, int height, int maxRGB) :
	magicNum(magicNum), width(width), height(height), maxRGB(maxRGB)
{ 
    if (width < 0)
    {
        width = 200;
    }
  
    if (height < 0)
    {
        height = 200;
    }
}

string Header::getMagicNum()
{
    return magicNum;
}

int Header::getWidth()
{
    return width;
}

int Header::getHeight()
{
    return height;
}

int Header::getMaxRGB()
{
    return maxRGB;
}
