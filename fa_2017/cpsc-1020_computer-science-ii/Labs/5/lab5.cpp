// Dylan Mumm, dmumm
// Lab 5, Section 002
// Nick Glyder, nglyder

#include "lab5.hpp"
using namespace std;


int main (int argc, char* argv[])
{

  // Constructing file pointers

  ifstream input(argv[1]);
  ofstream output(argv[2]);

  if(input.fail())
  {
    cout << argv[1] << " did not open successfully\n";
    return 0;
  }

  if(output.fail())
  {
    cout << argv[2] << " did not open successfully\n";
    return 0;
  }

  // Reading amount of lines

  int c = 0;
  int eol;

  while(input >> eol)
  {
    c++;
  }

  // Resetting input file

  input.clear();
  input.seekg(0, std::ios::beg);

  // Reading input file's ints into array

  int list[c];

  for (int i=0; i<c; i++)
  {
    input >> list[i];
  }

  // Passing to sort function

  bubble_sort(list, c);

  // Printing sorted array to output

  for(int i=0; i<c; i++)
  {
    output << list[i] << endl;
  }

  return 0;

}

void bubble_sort(int array[], int length)
{
  int swaps = 1;
  while(swaps != 0)
  {
    swaps = 0;
    for(int i=0; i<length-1; i++)
    {
      if (array[i] > array[i+1])
      {
        swap(array[i], array[i+1]);
        swaps++;
      }
    }
  }
}
