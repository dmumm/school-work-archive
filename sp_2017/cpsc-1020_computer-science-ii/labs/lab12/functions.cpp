#include <iostream>
//#include <fstream>
#include <cstdlib>
#include <algorithm>
#include "functions.h"
using namespace std;


/*********************************************
 *This function should print each element in *
 *the array.                                 *
 *********************************************/
void printArray(int array[], int array_size )
{
  for(int i = 0; i < array_size; i++)
  {
    cout << array[i];
  }
}

//************************************************
// quickSort uses the quickSort algorithm to     *
// sort arr from arr[start] through arr[end].    *
// This is a recursive algorithm                 *
//************************************************
void quickSort(int array[], int start, int end)
{

  int i = partition(array, start, end);

  if (start < i - 1)
        quickSort(array, start, i - 1);
  if (i < end)
        quickSort(array, i, end);


}


//***********************************************************
// partition rearranges the entries in the array arr from   *
// start to end so all values greater than or equal to the  *
// pivot are on the right of the pivot and all values less  *
// than are on the left of the pivot.                       *
//***********************************************************
int partition(int arr[], int start, int end)
{


    /*Create two variables --
     *1 that is equal to the element of arr at [start]     *
     *2 that is the position of the pivot                  */

   int s = start, e = end;
   int temp;
   int pivot = arr[(start + end) / 2];

    // Rearrange the rest of the array elements to
    // partition the subrange from start to end

    while(s <= e)
    {

            // arr[scan] is the "current" item.
            // Swap the current item with the item to the
            // right of the pivot element

            while (arr[s] < pivot)
                   s++;
            while (arr[e] > pivot)
                   e--;

            // Swap the current item with the pivot element

            if (e <= s) {
                  temp = arr[s];
                  arr[e] = arr[e];
                  arr[s] = temp;
                  s++;
                  e--;
        }
    }
    //return the position of the pivot

    return s;


}

//**********************************************************
// The binarySearch function performs a recursive binary   *
// search on a range of elements of an integer array. The  *
// parameter first holds the subscript of the range's      *
// starting element, and last holds the subscript of the   *
// ranges's last element. The parameter value holds the    *
// the search value. If the search value is found, its     *
// array subscript is returned. Otherwise, -1 is returned  *
// indicating the value was not in the array.              *
//**********************************************************
int binarySearch(const int array[], int first, int last, int value)
{

  while (first <= last) {
        int middle = (first + last) / 2;
        if (array[middle] == value)
              return middle;
        else if (array[middle] > value)
              last = middle - 1;
        else
              first = middle + 1;
  }
  return -1;

}
