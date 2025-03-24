/* Dylan Mumm
 * dmumm
 * Lab 11
 * Nick Glyder, Section 004
 */

#include "functions.h"
using namespace std;

void printVector(vector<int> v)
{
  int n = v.size();

  // Iterates through vector, printing each value

  for(int i = 0; i < n; i++)
  {
    cout << v.at(i) << endl;
  }

}

void selectionSort(vector<int>& v)
{

  int n = v.size();

  // Iterates through vector, and if loop finds a value later on in loop that
  // is greater than the current value being checked, it swaps the values

  for(int i = 0; i < n; i++)
  {


    int min = i;

    for (int j = i+1; j < n; j++)
    {

      if(v.at(j) < v.at(min))
        min = j;

    }

    int temp = v.at(i);
    v.at(i) = v.at(min);
    v.at(min) = temp;

  }
}

bool linearSearch(vector<int>& v, int item)
{

  bool result = false;
  int n = v.size();

  // Iterates through vector, changing the result bool to true if item is found

  for(int i = 0; i < n; i++)
  {
    if(v.at(i) == item)
      result = true;
  }

  return result;

}
