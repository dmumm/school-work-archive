#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>

#include "Pixel.h"
#include "Header.h"
#include "Point.h"
#include "Color.h"
#include "Shape.h"
#include "Triangle.h"
#include "Circle.h"
#include "Quadrilateral.h"

using namespace std;

void printHeader(ofstream &, Header);
void printImage(ifstream &, ofstream &, Header);


int main(int argc, char *argv[])
{

  ofstream output(argv[2]);
  ifstream input(argv[1]);

  int width, height;
  int maxRGB = 255;
  string shapeType, type = "P6";

  input >> width >> height;

  Header h(width, height, maxRGB, type);

  printHeader(output, h);
  printImage(input, output, h);

  input.close();
  output.close();



}

void printHeader(ofstream &output, Header h)
{

  output << h.getType() << endl << h.getWidth() << " " <<
      h.getHeight() << endl << h.getMaxRGB() << endl;

}

void printImage(ifstream &input, ofstream &output, Header hdr)
{

  int i, r;
  double x, y;
  int h = hdr.getHeight();
  int w  = hdr.getWidth();

  static int t = 0, c = 0, q = 0;

  string shapeName;

  vector <Triangle> tris;
  vector <Circle> circs;
  vector <Quadrilateral> quads;

  vector <Pixel> image;
  for(i=0; i < h*w; i++)
  {
    image.push_back(Pixel());
  }

  while (input >> shapeName)
  {

    if(shapeName == "Circle")
    {

      circs.push_back(Circle(150, 150, 150));

      input >> x >> y;
      circs[c].setCenter(x, y);

      input >> r;
      circs[c].setRadius(r);

      for(i=0; i<h*w; i++)
      {
        if(circs[c].checkPoint(image[i].getX(), image[i].getY()) == true)
        {
          image[i].setRGB(circs[c].getRed(), circs[c].getGreen(),
                          circs[c].getBlue());
        }
      }
      c++;
    }

    if(shapeName == "Triangle")
    {
      tris.push_back(Triangle(200,200,000));

      for(i=0; i<3; i++)
      {
        input >> x >> y;
        tris[t].setVector(i, x, y);
      }

      for(i=0; i<h*w; i++)
      {
        if(tris[t].checkPoint(image[i].getX(), image[i].getY()) == true)
        {
          image[i].setRGB(tris[t].getRed(), tris[t].getGreen(),
                          tris[t].getBlue());
        }
      }
      t++;
    }

    if(shapeName == "Quadrilateral")
    {
      quads.push_back(Quadrilateral(100,250,250));

      for(i=0; i<3; i++)
      {
        input >> x >> y;
        quads[q].setVector(i, x, y);
      }

      for(i=0; i<h*w; i++)
      {
        if(quads[q].checkPoint(image[i].getX(), image[i].getY()) == true)
        {
          image[i].setRGB(quads[q].getRed(), quads[q].getGreen(),
                          quads[q].getBlue());
        }
      }
      q++;
    }

    for(i=0; i<h*w; i++)
    {
      image[i].printRGB(output);
    }
  }
}
