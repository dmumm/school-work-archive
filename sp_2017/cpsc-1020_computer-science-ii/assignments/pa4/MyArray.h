#ifndef MYARRAY_H
#define MYARRAY_H
/*There will be two client functions that I will provide the code.
 *These functions will be useful in the implementation of some of
 *the following class functions.*/
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

class MyArray
{
  private:
    int size;
    char* ptr;

  public:
    /*Default constructor*/
    MyArray();
    /*regurlar constructor that accepts as a parameter a char array or
     *string literal example "Hello World"*/
    MyArray(const char*);
    /*Copy constructor*/
    MyArray(const MyArray&);

    /*Destructor*/
    ~MyArray();

    /*Returns the size of the array.  */
    int getSize()const;

    /*Overloaded operators*/
    const MyArray& operator=(const MyArray&);

    /*Returns true if the arrays are the same.  Otherwise it returns false.*/
    bool operator==(const MyArray&) const;

    /*Returns true if the arrays are not equal, false otherwise.*/
    bool operator!=(const MyArray& right)const;
    /*Provides bounds checking for the []*/
    char& operator[](int);

    friend istream& operator>>(istream&, MyArray&);
    friend ostream& operator<<(ostream&, const MyArray&);
    friend MyArray operator+(const MyArray&, const MyArray&);
    friend MyArray operator+(const MyArray&, const char);
    friend MyArray operator+(const char, const MyArray&);

};

#endif
