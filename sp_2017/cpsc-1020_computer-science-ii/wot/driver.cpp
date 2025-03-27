#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Header.h"
#include "Point.h"
#include "Color.h"
#include "Shape.h"
#include "Triangle.h"
#include "Circle.h"
#include "Quadrilateral.h"

using namespace std;

void createShape(ifstream &, ofstream &, Header &);

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


    inputFile >> width >> height; // read in width and height from inputFile


    Header header(magicNum, width, height, maxRGB); // construct instance of header for outputFile


    outputFile << header.getMagicNum() << endl << header.getWidth() << " " << 
        header.getHeight() << endl << header.getMaxRGB() << endl;


    createShape(inputFile, outputFile, header);


    inputFile.close(); // closes both inputFile and outputFile
    outputFile.close();

    return 0;
}

void createShape(ifstream &inputFile, ofstream &outputFile, Header &header)
{
    // *** VARIABLE DECLARATIONS ***
    int i, j = 0;
    int r;
    int row, column;
    double x, y;
    string shapeType;
    Color black;
    black.setRGB(0, 0, 0);
    struct RGB
    {
        unsigned char red;
        unsigned char green;
        unsigned char blue;
    };
    struct RGB Image[header.getHeight()][header.getWidth()];
    vector <Triangle> triangles;
    vector <Circle> circles;
    vector <Quadrilateral> quadrilaterals;
    static int t, c, q = 0; // iterators for triangle/circle/quadrilateral
    
    
    for (i = 0; i < header.getHeight(); i++)
    {
        for (j = 0; j < header.getWidth(); j++)
        {
            Image[i][j].red = 0; 
            Image[i][j].green = 0; 
            Image[i][j].blue = 0;
        }
    }
    
    
    while (inputFile >> shapeType)
    {
        if (shapeType == "Triangle")
        {   
            triangles.emplace_back(255, 0, 0);
        
            for (i = 0; i < 3; i++)
            {
                inputFile >> x >> y;
                triangles.at(t).setPoint(i, x, y);
            }
        
            for (row = 0; row < header.getHeight(); row++)
            {
                for (column = 0; column < header.getWidth(); column++)
                {
                    if (triangles.at(t).checkPoint(row, column) == true)
                    {
                       Image[row][column].red = triangles.at(t).getRed();
                       Image[row][column].green = triangles.at(t).getGreen();
                       Image[row][column].blue = triangles.at(t).getBlue();
                    }
                }
            }
            t++;
        }
    
        else if (shapeType == "Circle")
        {
            circles.emplace_back(0, 0, 255);
        
            inputFile >> x >> y;
            inputFile >> r;
            circles.at(c).setCenter(x, y);
            circles.at(c).setRadius(r);
        
            for (row = 0; row < header.getHeight(); row++)
            {
                for (column = 0; column < header.getWidth(); column++)
                {    
                    if (circles.at(c).checkPoint(row, column) == true)
                    {
                        Image[row][column].red = circles.at(c).getRed();
                        Image[row][column].green = circles.at(c).getGreen();
                        Image[row][column].blue = circles.at(c).getBlue();
                    }
                }
            }
            
            c++;
         }
     
         else if (shapeType == "Quadrilateral")
         {
             quadrilaterals.emplace_back(0, 255, 0);
         
             for (i = 0; i < 4; i++)
             {
                 inputFile >> x >> y;
                 quadrilaterals.at(q).setPoint(i, x, y);
             }
             
             for (row = 0; row < header.getHeight(); row++)
             {
                 for (column = 0; column < header.getWidth(); column++)
                 {
                     if (quadrilaterals.at(q).checkPoint(row, column) == true)
                     {
                         Image[row][column].red = quadrilaterals.at(q).getRed();
                         Image[row][column].green = quadrilaterals.at(q).getGreen();
                         Image[row][column].blue = quadrilaterals.at(q).getBlue();
                     }
                 }
             }
         
             q++;
         }
     
    }
    for (i = 0; i < header.getHeight(); i++)
    {
        for (j = 0; j < header.getWidth(); j++)
        {
            outputFile << Image[i][j].red << Image[i][j].green << Image[i][j].blue;
        }
    }
}



