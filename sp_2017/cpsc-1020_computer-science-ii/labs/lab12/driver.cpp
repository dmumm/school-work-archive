#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "functions.h"

using namespace std;



int main( int argc, char* argv[] )
{
    //create a file pointer
    // Using the command line arguments check for a valid input file
    // If there is not one, give the user a message and exit the program

    ifstream input(argv[1]);
    if(input.fail()) {
      cout << argv[1] << " did not open successfully\n";
      return -1;
    }



    // Assuming there is a valid input file, read the first item
    // The first item represents the number of items in the file

    int query, item;
    int n = input.get();
    cout << n;



    /*Dynamically allocate the memory for the array that is going to
     *hold the numbers be read in*/

     int* list = NULL;
     list = new int[n];

    /*Read in the numbers from the file storing them in array*/

    for(int i = 0; i < n; i++)
    {
      input >> query;
      list[i] = query;
    }


    /* Close the file you are reading.*/

//    input.close();


    /*Print the array to make sure you read in all the values correctly*/

    printArray(list, n);


    /*Using the quicksort function sort the array.*/

    quickSort(list, 0, n);

    /*Now Print the sorted array to make sure it is sorted*/

    printArray(list, n);

    /*To test the binary search algorithm ask the user for a number.
     *Call the binary search function.  If the number was found tell the
     *user you found the number and at what index it was found.*/

     cout << "Search for a number in the input: ";
     cin >> item;

     cout << "\nYour number was in position #" << binarySearch(list, 0, n, item);


     //delete dynamically allocated array

     delete [] list;
     list = NULL;

    return 0;
}
