//@ Dylan Mumm, 2120
//@ Assignment 1
//@ February 11th

#ifndef CORPUS_H
#define CORPUS_H
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class Corpus {

  public:

    // constructors
    Corpus();
    Corpus(const string);

    // function
    double proportion(const char) const;

  private:

    // Member variable
    double prop[26];

};
#endif
