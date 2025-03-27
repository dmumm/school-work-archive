//@ Dylan Mumm, 2121
//@ Lab 3
//@ February 5th

#include <iostream>
#include <fstream>
using namespace std;

class Recursion {

  public:

    // Regular constructor
    Recursion(ifstream&);

    // Member functions
    void print();
    void printGroupWith(int, int);

  private:

    // Member variable
    int** grid;


};

Recursion::Recursion(ifstream& input) {

  // creates 10x10 2d array
  grid = new int*[10];
  for(int i = 0; i < 10; i++)
    grid[i] = new int[10];

  // Loops through ifstream, saving "."s as 0s, and other
  // chars as 1s
  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      char cell;
      input >> cell;
      if(cell == '.')
      {
        grid[i][j] = 0;
      }
      else
      {
        grid[i][j] = 1;
      }
    }
  }
}


void Recursion::print() {


  // Creates 2d array of 10x10 for copying
  int** gridCopy = new int* [10];
  for(int i = 0; i < 10; i++) {
    gridCopy[i] = new int [10];
  }

  // Copies old 2d array onto new one
  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      gridCopy[i][j] = grid[i][j];
    }
  }

  // Loops through 2d array, if it finds a "1", prints out new group and starts
  // recursive function
  int count = 0;
  for(int r = 0; r < 10; r++)
  {
    for(int c = 0; c < 10; c++) {
      if(grid[r][c] == 1) {
        cout << "Group" << " " << ++count << ": ";
        printGroupWith(r, c);
        cout << endl;
      }
    }
  }

  // Deletes 2d arrays
  for(int i = 0; i < 10; ++i) {
    delete [] grid[i];
    delete [] gridCopy[i];
  }

  delete [] grid;
  delete [] gridCopy;

}

void Recursion::printGroupWith(int r, int c) {

  // Prints coordinate inputted as parameter
  cout << "(" << r << "," << c << ") ";

  // Resets that coordinate to 0 to prevent it being called again
  grid[r][c] = 0;

 /*
  * To prevent segmentation fault, ensures that it does not check the value of
  * coordinates outside of the 2d array, checks (valid) coordinates above,
  * to the left, below, or right of the inputted coordinate, and if 1, calls
  * the recursive function with that coordiante
  */

  if(r == 0 && c == 0) {
    if(grid[r+1][c] == 1)
      printGroupWith(r+1, c);

    if(grid[r][c+1] == 1)
      printGroupWith(r, c+1);
  }

  else if(r == 0) {
    if(grid[r+1][c] == 1)
      printGroupWith(r+1, c);

    if(grid[r][c+1] == 1)
      printGroupWith(r, c+1);

    if(grid[r][c-1] == 1)
      printGroupWith(r, c-1);
  }

  else if(c == 0) {
    if(grid[r+1][c] == 1)
      printGroupWith(r+1, c);

    if(grid[r][c+1] == 1)
      printGroupWith(r, c+1);

    if(grid[r-1][c] == 1)
      printGroupWith(r-1, c);
  }

  else if(r == 9 && c == 9) {
    if(grid[r-1][c] == 1)
      printGroupWith(r-1, c);

    if(grid[r][c-1] == 1)
      printGroupWith(r, c-1);
  }

  else if(r == 9) {
    if(grid[r-1][c] == 1)
      printGroupWith(r-1, c);

    if(grid[r][c-1] == 1)
      printGroupWith(r, c-1);

    if(grid[r][c+1] == 1)
      printGroupWith(r, c+1);
  }

  else if(c == 9) {
    if(grid[r-1][c] == 1)
      printGroupWith(r-1, c);

    if(grid[r][c-1] == 1)
      printGroupWith(r, c-1);

    if(grid[r+1][c] == 1)
      printGroupWith(r+1, c);
  }

  else {
    if(grid[r-1][c] == 1)
      printGroupWith(r-1, c);

    if(grid[r][c-1] == 1)
      printGroupWith(r, c-1);

    if(grid[r+1][c] == 1)
      printGroupWith(r+1, c);

    if(grid[r][c+1] == 1)
      printGroupWith(r, c+1);
  }
}


int main(int argc, char *argv[]) {

  // takes a filename from the command line
  ifstream input(argv[1]);

  // creates a suitable recursion object
  Recursion grid(input);

  // calls print on said object
  grid.print();


}
