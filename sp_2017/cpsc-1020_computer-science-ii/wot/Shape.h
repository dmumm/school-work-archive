#ifndef SHAPE_H
#define SHAPE_H

#include "Color.h"
#include <fstream>

using namespace std;

class Shape
{
    private:
            Color color;
    public:
            Shape();
            Shape(unsigned char red, unsigned char green, unsigned char blue);
            
            void setRGB(unsigned char, unsigned char, unsigned char); // setters
            
            unsigned char getRed();
            unsigned char getGreen();
            unsigned char getBlue();
};

#endif
