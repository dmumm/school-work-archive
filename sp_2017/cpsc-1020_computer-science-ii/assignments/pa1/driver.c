/*
 * Dylan Mumm
 * CPSC 1020, Section: 001, Spring 2017
 * dmumm
 * Yvon Feaster
 */

//access header file
#include "functions.h"

int main(int argc, char const *argv[])
{

  // use command line arguments to dictate what image will be inputed, and to
  // input the path for the outputted .ppm
  FILE* inputFile = fopen(argv[1], "r");
  FILE* outputFile = fopen(argv[2], "w");

  int i = 0;

  // making sure files were proper
  if(inputFile == NULL)
  {
    printf("File %s did not open\n", argv[1]);
  }

  if(outputFile == NULL)
  {
    printf("File %s did not open\n", argv[2]);
  }

  // declaring the header struct
  header_t inputHeader;

  // call to readHeader to take the header from input file into a struct
  readHeader(&inputHeader, inputFile);

  // dynamically allocating 2d array for ppm
  pixel_t **inputImage = (pixel_t **)malloc(inputHeader.height * sizeof(pixel_t *));
  for (i = 0; i < inputHeader.height; i++)
    inputImage[i] = (pixel_t*)malloc(inputHeader.width * sizeof(pixel_t));

  // call to readImage to take the pixel data from input file and write it
  // into the 2d aray
  readImage(&inputHeader, inputImage, inputFile);

  // call to chooseTransform to give user a menu to ask them what they would
  // like to do with the image
  chooseTransform(&inputHeader, inputImage, outputFile);

  // freeing the dynamically allocated memory
  for (i = 0; i < inputHeader.height; i++)
    free(inputImage[i]);
  free(inputImage);

  // closeing the file pointers
  fclose(inputFile);
  fclose(outputFile);

  return(0);

}
