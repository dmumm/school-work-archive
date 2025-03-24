// Dylan Mumm, dmumm
// CPSC 1020, Fall 2017
// PA1, September 29th
// Dr. Yvon Feaster

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <time.h>


/*Use this file to implement the functions you have listed in your header file*/


void readData(FILE* input, int** arr, int row, int col)
{

  // Reads in the data from the file and stores it in the 2D array
  // (double pointer) passed to the function.

 int i, j;
 for(i=0; i < row; i++)
  {
    for(j=0; j < col; j++)
    {
      fscanf(input, " %d", &arr[i][j]);
    }
  }
}


void checkNeighbors(int**  board, int height, int width)
{
  int i, j;
  for(i = 0; i < height; i++)  {
    for(j = 0; j < width; j++)  {

      // Only will detect neighbors if a bomb

      if(board[i][j] == -1)    {

        // Positively increments neighboring spaces, ensuring it doesn't
        // increment non-allocated spaces, or bombs

        if(i > 0 && j > 0)
          if(board[i-1][j-1] != -1)
            board[i-1][j-1]++;
        if(i > 0)
          if(board[i-1][j] != -1)
            board[i-1][j]++;
        if(i > 0 && j < width)
          if(board[i-1][j+1] != -1)
            board[i-1][j+1]++;
        if(j > 0)
          if(board[i][j-1] != -1)
            board[i][j-1]++;
        if(j < width)
          if(board[i][j+1] != -1)
            board[i][j+1]++;
        if(i < height-1 && j > 0)
          if(board[i+1][j-1] != -1)
            board[i+1][j-1]++;
        if(i < height-1)
          if(board[i+1][j] != -1)
            board[i+1][j]++;
        if(i < height-1 && j < width)
          if(board[i+1][j+1] != -1)
            board[i+1][j+1]++;
      }
    }
  }
}


void printOutput(FILE* output, int** board, int height, int width) {

  // Prints 2d array

  int i, j;
  for(i=0;i<height;i++) {
    for(j=0;j<width;j++) {

      // Converts -1s to X for readability, otherwise prints

      if(board[i][j] == -1)
        fprintf(output, "X ");
      else
        fprintf(output, "%d ", board[i][j]);
    }
    fprintf(output, "\n");
  }
}


void printOut(int** board, int height, int width){

  int i, j;

  // prints top row of guide numbers

  printf("\n    ");
  for(j=0; j<width;j++)
    printf("%2d ", j);
  printf("\n\n");

  for(i=0;i<height;i++) {

    // prints left column of guide numbers

    printf("%2d   ", i);

    for(j=0;j<width;j++) {

      // Converts -1s to Xs

      if(board[i][j] == -1)
        printf("X  ");

      // Converts -2s to .s

      else if(board[i][j] == -2)
          printf(".  ");
      else
        printf("%d  ", board[i][j]);
    }

    //Prints right column of guide numbers

    printf("   %d\n", i);
  }

  // prints bottom row of guide numbers
  printf("\n    ");
  for(j=0; j<width;j++)
    printf("%2d ", j);
  printf("\n");

}


int** allocateMemory(int height, int width)
{
  int i;

  // Allocating and initializing 2d arrays

  int** arr;
  arr = (int **)calloc(height , sizeof(int *));
  for (i=0; i<height; i++)
  {
    arr[i] = (int *)calloc(width , sizeof(int));
  }

  return arr;
}

void freeMemory(int** arr, int height, int width)
{

  // Freeing allocated memory

  int i;;
  for(i=height-1; i>=0; i--)
  {
    free(arr[i]);
  }
  free(arr);

}



int printMenu()
{

  int input = 5;

  printf("**************************************************\n");
  printf("\n       Welcome to Avoid The Mines\n");
  printf("\n   Please choose one of the options below.\n");
  printf("\n   1: Read the board information from a file\n");
  printf("\n   2: Randomly generate the board information\n");
  printf("\n   3: Randomly generate the board and play basic\n");
  printf("\n   4: Randomly generate the board and play advanced\n");
  printf("\n   Type 1, 2, 3, or 4 -- and then press return\n");
  printf("\n**************************************************\n");\

  // Storing user response
  scanf("%d", &input);

  // Verifying response
  while(input != 1 && input != 2 && input != 3 && input != 4)
  {
    printf("You have entered an invalid response, please try again");
    scanf("%d", &input);
  }

  return input;

}


void generateBoard(int height, int width, int** oldBoard)
{
  int i, r, c, mines;

  mines = height * width * 0.15;
  printf("\nWatch out for the %d mines scattered around your %d x %d board!\n",
                                                mines, height, width);

  // Acquiring seed
  srand(time(NULL));

  for(i = 0; i < mines; i++) {

    // Acquiring random row and column
    r = rand() % (height);
    c = rand() % (width);

    // Making random row and column a bomb -- unless it already is one
    if(oldBoard[r][c] != -1) {
      oldBoard[r][c] = -1;
    }
    else // If alredy a bomb, increments mine variable to ensure proper amount
      mines++;
  }
}

void propogateGuess(int height, int width, int row, int col, int* count,
                            int** oldBoard, int** newBoard)
{


  // Returns if space is off the dimensions or not  a blank space
  if (row < 0 || row >= height)
    return;
  if (col < 0 || col >= width)
    return;
  if (newBoard[row][col] != -2)
    return;

  else
  {
    // If gamespace is't updated, updates it and decrements count
    if(newBoard[row][col] != oldBoard[row][col])
    {
      newBoard[row][col] = oldBoard[row][col];
      *count = *count - 1;
    }
    if (oldBoard[row][col] == 0) { // If a 0, checks neighboring spaces
        propogateGuess(height, width, row - 1, col, count, oldBoard, newBoard);
        propogateGuess(height, width, row, col - 1, count, oldBoard, newBoard);
        propogateGuess(height, width, row, col + 1, count, oldBoard, newBoard);
        propogateGuess(height, width, row + 1, col, count, oldBoard, newBoard);
    }
  }
}


void getHW(int* height, int* width)
{
  printf("Enter the Height and Width you wish the board to be!\n");
  printf("The Height and Width should be between 5 - 20\n");
  printf("You must place a space between the height and width.\n");

  scanf("%d %d", height, width);

  while(*height < 5 || *height > 20 || *width < 5 || *width > 20)
  {
    printf("You have entered an invalid response, please try again\n");
    scanf("%d %d", height, width);
  }

}


void option1(FILE* input, FILE* output, int height, int width,
   int** oldBoard, int** newBoard)
{

  int i, j;

  // Allocating memory, reading data

  oldBoard = allocateMemory(height, width);
  newBoard = allocateMemory(height, width);
  readData(input, oldBoard, height, width);

  // Converting 1s to -1s

 for(i = 0; i < height; i++) {
   for(j = 0; j < width; j++) {
     if(oldBoard[i][j] == 1) {
       newBoard[i][j] = -1;
     }
   }
 }

 // Find and printing solved puzzle

 checkNeighbors(newBoard, height, width);
 printOutput(output, newBoard, height, width);

 // Freeing memory

 freeMemory(oldBoard, height, width);
 freeMemory(newBoard, height, width);

}


void option2(FILE* output, int height, int width, int** oldBoard){

  // Allocating memory
  oldBoard = allocateMemory(height, width);

  // Generating board, solving it, printing it, freeing allocated memory
  generateBoard(height, width, oldBoard);
  checkNeighbors(oldBoard, height, width);
  printOutput(output, oldBoard, height, width);
  freeMemory(oldBoard, height, width);

}
void option3(FILE* output, int height, int width,
  int** oldBoard, int** newBoard)
{

  // Allocating memory, generating board, solving it, printing it,
  oldBoard = allocateMemory(height, width);
  newBoard = allocateMemory(height, width);
  generateBoard(height, width, oldBoard);
  checkNeighbors(oldBoard, height, width);

  // Printing solved board to output
  printOutput(output, oldBoard, height, width);

  // Starting game
  playBasicGame(height, width, oldBoard, newBoard);

  // freeing allocated memory
  freeMemory(oldBoard, height, width);
  freeMemory(newBoard, height, width);


}


void option4(FILE* output, int height, int width,
  int** oldBoard, int** newBoard)
{

  // Allocating memory, generating board, solving it, printing it,
  oldBoard = allocateMemory(height, width);
  newBoard = allocateMemory(height, width);
  generateBoard(height, width, oldBoard);
  checkNeighbors(oldBoard, height, width);

  // Printing solved board to output
  printOutput(output, oldBoard, height, width);

  // Starting game
  playAdvancedGame(height, width, oldBoard, newBoard);

  // freeing allocated memory
  freeMemory(oldBoard, height, width);
  freeMemory(newBoard, height, width);
}


/*Extra Credit functions*/
void playBasicGame(int height, int width, int** oldBoard, int** newBoard) {

  int start = 1;
  int row, col, count, i, j;
  int mines = height * width * 0.15;

  // Filling gameboard with -2s
  for(i = 0; i < height; i++) {
    for(j = 0; j < width; j++) {
        newBoard[i][j] = -2;
    }
  }

  // Calculating count to calculate win-state
  count = (height*width) - mines;

  while(start)
  {
    printf("\nWhat space do you want to uncover?\n");
    printf("Enter the row (0 - %d), a space, then the column (0 - %d): ",
                                                        height-1, width-1);
    scanf("%d %d", &row, &col);

    // Ensuring selection is in-bounds
    while(row < 0 || row > height || col < 0 || col > width)
    {
      printf("You have entered an invalid response, please try again\n\n");
      scanf("%d %d", &row, &col);
    }

    // Seeing if they guessed a bomb
    if(oldBoard[row][col] == -1)
    {
      newBoard[row][col] = -1;
      printOut(newBoard, height, width);
      printf("\nSorry, (%d, %d) is a bomb. You die!\n", row, col);
      start = 0;
    }

    // Seeing if they've already selected that spot
    else if(newBoard[row][col] != -2)
    {
      printf("You've already selected that spot! Try again.");
    }

    // Otherwise, figures what number said space should be
    else
    {

      // Decrements count
      count--;

      // Win state when count is 0
      if(count == 0)
      {
        printf("\n\nCongratulations, you live!\n");
        start = 0;
        newBoard[row][col] = oldBoard[row][col];
        for(i = 0; i < height; i++) {
          for(j = 0; j < width; j++) {
            if(newBoard[i][j] == -2)
              newBoard[i][j] = -1;
          }
        }
        printOut(newBoard, height, width);
        printf("\n");
      }

      // Converts space to that of solved board, prints
      else
      {
        newBoard[row][col] = oldBoard[row][col];
        printOut(newBoard, height, width);
      }
    }
  }

}
void playAdvancedGame(int height, int width, int** oldBoard, int** newBoard){

  int start = 1;
  int row, col, count, i, j;
  int mines = height * width * 0.15;

  // Filling gameboard with -2s
  for(i = 0; i < height; i++) {
    for(j = 0; j < width; j++) {
        newBoard[i][j] = -2;
    }
  }

  // Calculating count to calculate win-state
  count = (height*width) - mines;

  while(start == 1)
  {
    printf("\nWhat space do you want to uncover?\n");
    printf("Enter the row (0 - %d), a space, then the column (0 - %d): ",
                                                        height-1, width-1);
    scanf("%d %d", &row, &col);

    // Ensuring selection is in-bounds
    while(row < 0 || row > height || col < 0 || col > width)
    {
      printf("You have entered an invalid response, please try again\n\n");
      scanf("%d %d", &row, &col);
    }

    // Seeing if they guessed a bomb
    if(oldBoard[row][col] == -1)
    {
      newBoard[row][col] = -1;
      printOut(newBoard, height, width);
      printf("\nSorry, (%d, %d) is a bomb. You die!\n", row, col);
      start = 0;
    }

    // Seeing if they've already selected that spot
    else if(newBoard[row][col] != -2)
    {
      printf("You've already selected that spot! Try again.");
    }

    // Otherwise, figures what number said space should be
    else
    {
      // Converts space to that of solved board
      // Converts all connected spaces that do not neighbor bombs
      // Prints
      if(count > 0)
      {
        propogateGuess(height, width, row, col, &count, oldBoard, newBoard);
        printOut(newBoard, height, width);
      }

      // Win state
      if(count == 0)
      {
        printf("\n\nCongratulations, you live!\n");
        start = 0;
        newBoard[row][col] = oldBoard[row][col];
        for(i = 0; i < height; i++) {
          for(j = 0; j < width; j++) {
            if(newBoard[i][j] == -2)
              newBoard[i][j] = -1;
          }
        }
        printOut(newBoard, height, width);
        printf("\n");
      }
    }
  }

}
