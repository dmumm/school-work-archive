// Dylan Mumm
// PA3
// Dr Yvon Feaster, CPSC 1020
// November 17th

#include "Person.hpp"

Person::Person(string first, string last, int streetNum, string streetName,
               string city, string state, int zip, string site) :
               first(first), last(last),
               address(streetNum, streetName, city, state, zip, site)
{
}

Person::Person() : first("first"), last("last"), address()
{
}

void Person::setFirst(string first)
{
  this->first = first;
}

void Person::setLast(string last)
{
  this->last = last;
}

void Person::setAddress(Address address)
{
  this->address = address;
}

string Person::getFirst()
{
  return first;
}

string Person::getLast()
{
  return last;
}

Address Person::getAddress()
{
  return address;
}

void Person::printPerson() const {

  cout << "Author Info:" << endl
       << this->last << ", "
       << this->first << endl;

  this->address.printAddress();


}
