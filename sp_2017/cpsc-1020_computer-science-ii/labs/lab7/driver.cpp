/*
  Dylan Mumm
  dmumm
  Lab 7, 004
  Nick Glyder
*/

#include "color.h"

using namespace std;

void createSquare(ofstream& file1, Color Color1, Color Color2);
void createRectangle(ofstream& file2, Color Color1, Color Color2);


int main(int argc, char const *argv[]) {

  ofstream file1;
  ofstream file2;

  file1.open (argv[1]);
  file2.open (argv[2]);

  if (file1.is_open() && file2.is_open())
  {
    cout << "Files opened, proceed" << endl;
  }
  else
  {
    cout << "Files opened incorrectly, examing command-line arguments" << endl;
  }

  // on board?
  unsigned int red, green, blue;

  Color Color1;
  Color Color2(red, green, blue);

  cout << "Input the RGB values for a color you want on the shape:" << endl;

  cout << "Red:"   << endl;
  cin  >> red;
  cout << "Green:" << endl;
  cin  >> green;
  cout << "Blue:"  << endl;
  cin  >> blue;

  Color2.setRed((unsigned char)red);
  Color2.setGreen((unsigned char)green);
  Color2.setBlue((unsigned char)blue);

  createSquare(file1, Color1, Color2);
  createRectangle(file2, Color1, Color2);



}

void createSquare(ofstream& file1, Color Color1, Color Color2)
{
  int row, column;
  file1 << "P6\n500 500 255\n";
  for(row = 0; row < 250; row++)
  {
    for(column = 0; column < 250; column++)
      file1 << Color1.getRed() << Color1.getGreen() << Color1.getBlue();
    for(column = 250; column < 500; column++)
      file1 << Color2.getRed() << Color2.getGreen() << Color2.getBlue();
  }

  for(row = 250; row < 500; row++)
  {
    for(column = 0; column < 250; column++)
      file1 << Color2.getRed() << Color2.getGreen() << Color2.getBlue();
    for(column = 250; column < 500; column++)
      file1 << Color1.getRed() << Color1.getGreen() << Color1.getBlue();
  }
}

void createRectangle(ofstream& file2, Color Color1, Color Color2)
{
  int row, column;
  file2 << "P6\n800 400 255\n";
  for(row = 0; row < 200; row++)
  {
    for(column = 0; column < 400; column++)
      file2 << Color1.getRed() << Color1.getGreen() << Color1.getBlue();
    for(column = 400; column < 800; column++)
      file2 << Color2.getRed() << Color2.getGreen() << Color2.getBlue();
  }

  for(row = 200; row < 400; row++)
  {
    for(column = 0; column < 400; column++)
      file2 << Color2.getRed() << Color2.getGreen() << Color2.getBlue();
    for(column = 400; column < 800; column++)
      file2 << Color1.getRed() << Color1.getGreen() << Color1.getBlue();
  }
}
