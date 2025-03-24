/* Dylan Mumm
 * CPSC 1020 001, Spring 2017
 * dmumm
 */

#include "Image.h"
using namespace std;

// The prototype for the client function that determines if the given
// point is within the parameter of the trianle

bool checkPoint(Point p[], Point t);

int main(int argc, char *argv[])
{

  // File pointers for input.txt and output.ppm

  ofstream outPut(argv[2]);
  ifstream inPut(argv[1]);

  // Create an instance of the Image class and Point to represent
  // the three points that defines the triangle.  Also put other
  // variables needed here.

  Image Image1;
  Point *Points;
  Points = new Point [3];
  Point Test;

  string type = "P6";
  int maximumRGB = 255;
  int height, width, i, j, r, g, b;
  double x, y;


  // Test if files loaded loaded properly

  if(argc != 3)
  {
    cout << "USAGE ERROR:  ./executable outPutFileName";
    return -1;
  }
  if(inPut.fail())
  {
    cout << argv[1] << " did not open successfully\n";
  }

  if(outPut.fail())
  {
    cout << argv[2] << " did not open successfully\n";
  }

  // read the data from the input file here

  inPut >> width >> height;

  for(i = 0; i < 3; i++)
  {
    inPut >> x >> y;
    Points[i].setPoints(x, y);
  }

  // Using the instance of image created above call the function
  // to set the width and height for the header.  Using the
  // instance of image call the funtion used to print the header

  Image1.setHeader(type, width, height, maximumRGB);
  Image1.printHeader(outPut);

  // Using nested for loops call the client function to test if
  // the given point is within the parameters of the triangle.
  //
  // Using the instance of image set the color of the pixels RGB
  // channels and then call the function to print the Pixel to
  // the output file.

  for(i = 0; i < height; i++)
  {
    for(j = 0; j < width; j++)
    {

      // Creates point that is rewritten for each iteration of the loop,
      // Passing it into the function that interprets what color the pixel
      // should be, And then printing said pixel.

      Test.setPoints(i, j);

      Image1.decidePixelColor(checkPoint(Points, Test));
      Image1.printPixelColor(outPut);

     }
  }

  inPut.close();
  outPut.close();

  return 0;
}

// Implement the function that determines if a given point is
// within the parameter of the triangle

bool checkPoint(Point p[], Point t)
{
  double a, b, c;

  a = ((p[1].getY() - p[2].getY()) * (t.getX() - p[2].getX()) +
       (p[2].getX() - p[1].getX()) * (t.getY() - p[2].getY())) /
      ((p[1].getY() - p[2].getY()) * (p[0].getX() - p[2].getX()) +
       (p[2].getX() - p[1].getX()) * (p[0].getY() - p[2].getY()));

  b = ((p[2].getY() - p[0].getY()) * (t.getX() - p[2].getX()) +
       (p[0].getX() - p[2].getX()) * (t.getY() - p[2].getY())) /
      ((p[1].getY() - p[2].getY()) * (p[0].getX() - p[2].getX()) +
       (p[2].getX() - p[1].getX()) * (p[0].getY() - p[2].getY()));

  c = 1 - a - b;

  if (0 <= a && a <= 1 &&
      0 <= b && b <= 1 &&
      0 <= c && c <= 1)
  {
    return true;
  }

  else
  {
    return false;
  }

}
