// Dylan Mumm
// PA3
// Dr Yvon Feaster, CPSC 1020
// November 17th

#ifndef PERSON_HPP
#define PERSON_HPP
#include <iostream>
#include <string>
#include "Address.hpp"
using namespace std;

class Person
{
  private:
    string first;
    string last;
    Address address;

  public:
    /*Constructors*/

    Person(string, string, int, string, string, string, int, string);
    Person();

    /*Getters and Setters*/

    void setFirst(string);
    void setLast(string);
    void setAddress(Address);

    string getFirst();
    string getLast();
    Address getAddress();

    /*Other functions*/
    void printPerson() const;

};

#endif
