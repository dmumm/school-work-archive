// Dylan Mumm, dmumm
// Lab 12, Section 002
// Nick Glyder, nglyder

#include <iostream>
#include "MyString.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
  MyString detective("Hello");
   MyString hello = (detective + ",");

  detective = "Sherlock";
  detective = "Mr. " + detective;
  detective = detective + " Holmes";

  cout << hello << " " << detective << endl;
  cout << "String length is: "
       << (hello + " " + detective).len()
       << endl;
  return 0;
}
