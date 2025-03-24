#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "functions.h"
using namespace std;


int main( int argc, char* argv[] )
{


    int item, query;
    vector<int> list;
    bool result;

    // Using the command line arguments check for a valid input file
    // If there is not one, give the user a message and exit the program

    ifstream input(argv[1]);
    if(input.fail()) {  cout << argv[1] << " did not open successfully\n"; return 0; }


    // Read the other items from the file and store them

    while(input >> query)
    {
      list.push_back(query);
    }


    // Close the file you are reading
    // Then print the array

    input.close();
    printVector(list);

    // Using selection sort, sort the array
    // Then print the array

    selectionSort(list);
    printVector(list);


    // Ask the user for a number

    cout << "Enter search item: ";
    cin  >> item;


    // Using linear search, search the array for the user's number

    result = linearSearch(list, item);

    // Print if the number was or was not found in the array

    if(result)
    {
      cout << "Number was found in list" << endl;
    }
    else
    {
      cout << "Number was not found in list" << endl;
    }

    return 0;
}
