#include <iostream>
#include <fstream>
#include <string>

#include "Header.h"
#include "Point.h"
#include "Color.h"
#include "Shape.h"
#include "Triangle.h"
#include "Circle.h"

using namespace std;

void createShape(ifstream &, ofstream &, string);

int main(int argc, char *argv[])
{
    ifstream inputFile; // file stream for inputFile
    inputFile.open(argv[1]);

    ofstream outputFile; // file stream for outputFile
    outputFile.open(argv[2]);


    // *** VARIABLE DECLARATIONS ***
    int width, height;
    int maxRGB = 255;
    string magicNum = "P6";
    string shapeType;
    // *****************************************************Color defaultColor(0, 0, 0)


    inputFile >> width >> height; // read in width and height from inputFile


    Header header1(magicNum, width, height, maxRGB); // construct instance of header for outputFile


    outputFile << header1.getMagicNum() << endl << header1.getWidth() << " " << 
        header1.getHeight() << endl << header1.getMaxRGB() << endl;


    while (inputFile >> shapeType)
    {
        createShape(inputFile, outputFile, shapeType);
    }


    inputFile.close(); // closes both inputFile and outputFile
    outputFile.close();

    return 0;
}

void createShape(ifstream &inputFile, ofstream &outputFile, string shapeType)
{
    int i  = 0;
    double x, y;
    
    
    if (shapeType == "Triangle")
    {   
        Triangle triangle(255, 0, 0);
        
        for (i = 0; i < 3; i++)
        {
            inputFile >> x >> y;
            triangle.setPoint(i, x, y);
        }
    }
}
