/*
 * Dylan Mumm
 * CPSC 1020, Section: 001, Spring 2017
 * dmumm
 * Yvon Feaster
 */

#include "functions.h"

void readHeader(header_t *inputHeader, FILE* inputFile)
{
  // scan inputfile's header into a header struct
  fscanf(inputFile, "%s %d %d %d", inputHeader->type, &inputHeader->width,
                                   &inputHeader->height, &inputHeader->maxval);
}

void readImage(header_t *inputHeader, pixel_t **inputImage, FILE* inputFile)
{
  int i, j;

  // loops through the inputFile's pixel data, scanning it into the 2d array of
  // pixel structs
  for(i = 0; i < inputHeader->height; i++)
  {
    for(j = 0; j < inputHeader->width; j++)
    {
      fscanf(inputFile, "%hhu%hhu%hhu", &inputImage[i][j].r,
                   &inputImage[i][j].g, &inputImage[i][j].b);
    }
  }

}

void chooseTransform(header_t *inputHeader, pixel_t **inputImage, FILE* outputFile)
{

  // menu split into strings to increase simplicity
  char division[] = "+++++++++++++++++++++++++++++++"
                    "+++++++++++++++++++++++++++++++";
  char optionOne[]   = "1.   Gray Scale";
  char optionTwo[]   = "2.   Color to Negative";
  char optionThree[] = "3.   Flip the Image";
  char optionFour[]  = "4.   Rotate Right";
  char optionFive[]  = "5.   Rotate Left";
  char optionSix[]   = "6.   Reprint";

  // declaration of char selection
  char selection;

  // menu message
  printf("%s\n", division);
  printf("Thank you for using the Image Transformer!\n");
  printf("There are several transformation you can perform\n");
  printf("on the input image. Choose the number that corresponds to the\n");
  printf("transformation you wish to perform on the image!\n");
  printf("%s\n\n", division);
  printf("%s\n%s\n%s\n%s\n%s\n%s\n", optionOne, optionTwo, optionThree,
                                     optionFour, optionFive, optionSix);

  // while loops that enables user to be re-asked to input selection in case
  // of error
  int start = 1;
  while(start)
  {
    // user inputs selection
    scanf("%c", &selection);

    // switch that calls function user asks, assigns start to 0 to stop loop
    // if user fails to input valid response, loop restarts w/ error message
    switch(selection)
    {
      case '1':
        grayScaleImage(inputHeader, inputImage, outputFile); //void grayScaleImage(header_t *, pixel_t **, FILE*);
        start = 0;
        break;
      case '2':
        color2Negative(inputHeader, inputImage, outputFile);
        start = 0;
        break;
      case '3':
        flipImage(inputHeader, inputImage, outputFile);
        start = 0;
        break;
      case '4':
        rotateLeft(inputHeader, inputImage, outputFile);
        start = 0;
        break;
      case '5':
        rotateRight(inputHeader, inputImage, outputFile);
        start = 0;
        break;
      case '6':
        reprint(inputHeader, inputImage, outputFile);
        start = 0;
        break;
      default:
        printf("\n\n%s\n", division);
        printf("You entered an incorrect number. Please, choose the\n"
                "number that corresponds to the transformation you\n"
                "wish to perform on the image!\n");
        printf("%s\n\n", division);
        printf("%s\n%s\n%s\n%s\n%s\n%s\n", optionOne, optionTwo, optionThree,
                                           optionFour, optionFive, optionSix);
        break;
      }
    }
  }


void printP6Image(header_t *inputHeader, pixel_t **inputImage,
                  FILE* outputFile)
{
  int i, j;

  // prints header to output file
  fprintf(outputFile,"%s %d %d %d\n", inputHeader->type, inputHeader->width,
                                      inputHeader->height, inputHeader->maxval);

  for(i = 0; i < inputHeader->height; i++)
  {
    for(j = 0; j < inputHeader->width; j++)
    {

      // loops through output file, printing pixel data
      fprintf(outputFile, "%hhu%hhu%hhu", inputImage[i][j].r, inputImage[i][j].g,
                                    inputImage[i][j].b);

    }
  }
}

void grayScaleImage(header_t *inputHeader, pixel_t **inputImage,
                  FILE* outputFile)
{

}

void color2Negative(header_t *inputHeader, pixel_t **inputImage,
                  FILE* outputFile)
{

}

void flipImage(header_t *inputHeader, pixel_t **inputImage,
                  FILE* outputFile)
{

}

void rotateLeft(header_t *inputHeader, pixel_t **inputImage,
                  FILE* outputFile)
{

}

void rotateRight(header_t *inputHeader, pixel_t **inputImage,
                  FILE* outputFile)
{

}

void reprint(header_t *inputHeader, pixel_t **inputImage,
                  FILE* outputFile)
{

  // calls printP6Image with no manipulations done
  printP6Image(inputHeader, inputImage, outputFile);
}


/*
void readHeader(header_t*, FILE*);
void readImage(header_t*, pixel_t **, FILE*);
void chooseTransform(header_t *, pixel_t **, FILE*);
void printP6Image(header_t*, pixel_t **, FILE*);
void grayScaleImage(header_t *, pixel_t **, FILE*);
void flipImage(header_t *, pixel_t **, FILE*);
void rotateLeft(header_t * , pixel_t **, FILE*);
void rotateRight(header_t *, pixel_t **, FILE*);
void color2Negative(header_t*, pixel_t **, FILE*);
void reprint(header_t*, pixel_t**, FILE*);
*/
