//@ Dylan Mumm, 2121
//@ Assignment 1
//@ February 11th

#ifndef MYSENTENCE_H
#define MYSENTENCE_H
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Corpus.h"

using namespace std;

class MySentence {

  public:

    // constructor
    MySentence(string);

    // functions
    void reverse();
    static char rotationOf(char);
    void rotate();
    void rotate(const int);

    double scoreWith(const Corpus&) const;
    void decode(const Corpus&);

    bool operator==(const MySentence&) const;
    friend ostream& operator<<(ostream&, const MySentence&);

  private:

    // Member variable
    string str;
    int size;

};
#endif
