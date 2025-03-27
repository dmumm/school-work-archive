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
