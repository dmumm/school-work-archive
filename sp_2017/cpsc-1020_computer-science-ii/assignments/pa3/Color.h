#ifndef COLOR_H
#define COLOR_H

class Color
{
    private:

  unsigned char red;
  unsigned char green;
  unsigned char blue;

    public:

  void setRGB(unsigned char, unsigned char, unsigned char);

  unsigned char getRed();
  unsigned char getGreen();
  unsigned char getBlue();

};

#endif
