// Dylan Mumm
// PA4
// Dr Yvon Feaster, CPSC 1020
// December 8th

#ifndef PERSON_H
#define PERSON_H

#include "Address.hpp"
#include "Date.hpp"
#include <string>
#include <vector>

class Person
{
  private:
    string last;
    string first;
    string email;
    Address address;
    Date bday;

  public:

    Person();
    Person(string, string, string, int, string, string, string,
           int, int, int, int);

    void setLast(string);
    void setFirst(string);

    string getLast();
    string getFirst();
    string getEmail();

    void printEmail(vector<Person>&, ostream&);

};

#endif
