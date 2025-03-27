//@ Dylan Mumm, 2120
//@ Assignment 1
//@ February 11th

#include <iostream>
#include <iomanip>
using namespace std;
#include "MySentence.h"

int main() {

   string filename;
   string sentence;

   // Constructs corpus based on user inputted file
   cout << "Enter file name for corpus:  ";
   getline(cin, filename);
   Corpus c(filename);

   // Constructs sentence based on user inputted string
   cout << "Enter sentence terminated by <ENTER> ";
   getline(cin, sentence);
   MySentence s(sentence);

   // Passes sentence to decode function
   s.decode(c);
   cout << "Decoded sentence is: " << s << endl;

   return 0;
}
