// Dylan Mumm
#include <iostream>
using namespace std;

class NumberCount {
  public:
    // Regular constructor
    NumberCount(int mi, int ma) : min(mi), max(ma)
    {
      // Declares array of 0s with size requested in arguments
      data = new int[max - min + 1];
      for(int i = 0; i < max-min; i++)
        data[i] = 0;
    }

    // Default constructor
    NumberCount() : min(0), max(0)
    {
      data = new int[9];
      for(int i = 0; i < max-min; i++)
        data[i] = 0;
    }

    // Mutators
    void addElement(int number)
    {
      // If within range of array, increments by 1
      if(number >= min && number <= max) {
        data[number-min]++;
      }
      // If not in range, prints error message
      else {
        cout << number << " out of range;" << endl;
      }
    }

    bool removeElement(int number)
    {
      // If element has value greater than 0 and within range, decrements by 1
      if(data[number-min] > 0 && number >= min && number <= max) {
        data[number-min]--;
        return true;
      }

      // If element not in range, prints erorr message
      else if(number < min && number > max) {
        cout << number << " out of range;" << endl;
        return false;
      }

      // If element in range but with a value of 0, prints error message
      else {
        cout << number << " not present;" << endl;
        return false;
      }

    }

    void display()
    {
      // Prints every element, followed by its value represented by astericks
      cout << endl;
      for(int i = 0; i <= max-min; i++) {
        cout << i+min << ":";
        for(int j = 0; j < data[i]; j++) {
          cout << "*";
        }
        cout << endl;
      }
      cout << endl;
    }

  private:
    int min;
    int max;
    int* data;
};

int main(){

  NumberCount N(11,16);
  N.addElement(12);
  N.addElement(12);
  N.addElement(12);
  N.addElement(14);
  N.addElement(17);
  N.addElement(13);
  N.removeElement(11);
  N.removeElement(13);
  N.display();


  return 0;
}
