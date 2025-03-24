#include "Header.h"

Header::Header() : type(""), width(0), height(0), maxRGB(0)
{
}

Header::Header(int w, int h, int m, string t)
    : width(w), height(h), maxRGB(m), type(t)
{
}

string Header::getType()
{
    return type;
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
