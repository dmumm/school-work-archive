// Dylan Mumm, dmumm
// CPSC 1020, Fall 2017
// PA1, September 29th
// Dr. Yvon Feaster

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"


int main(int argc, char *argv[])
{
  /*Create any variables need*/

  int height, width;
  int** oldBoard = NULL;
  int** newBoard = NULL;


  /*1.  Create a file pointer for the file that you will read from
   *2.  Check to make sure the file pointer is opened sucessfully */

   FILE* input;
   FILE* output;

   input  = fopen(argv[1], "r");
   output = fopen(argv[2], "w");

   if(input == NULL) {
    printf("Error regarding input file command argument.");
    return 0;
   }

  if(output == NULL) {
   printf("Error regarding input file command argument.");
   return 0;
  }

  fscanf(input, "%d %d", &height, &width);

  /*Call printMenu() This starts the program.  The Selection returned will
   *determine the steps needed next.
   */

 switch(printMenu())
 {
   case 1:
    option1(input, output, height, width, oldBoard, newBoard);
    break;
  case 2:
    getHW(&height, &width);
    option2(output, height, width, oldBoard);
    break;
  case 3:
    getHW(&height, &width);
    option3(output, height, width, oldBoard, newBoard);
    break;
  case 4:
    getHW(&height, &width);
    option4(output, height, width, oldBoard, newBoard);
 }




  /*After everything is complete you should free any remaining allocated memory
   *and close and open file pointers.*/


   fclose(input);
   fclose(output);


  return 0;

}
