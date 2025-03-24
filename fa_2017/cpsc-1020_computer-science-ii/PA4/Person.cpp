// Dylan Mumm
// PA4
// Dr Yvon Feaster, CPSC 1020
// December 8th

#include "Person.hpp"

// Constructors

Person::Person() : last("last"), first("first"), email("email"),
                   address(0,"str","c","sta",01234), bday(1,1,1999) {}

Person::Person(string l, string f, string e, int h, string str, string c,
               string sta, int z, int m, int d, int y )
               : last(l), first(f), email(e), address(h, str, c, sta, z),
                  bday(m, d, y) {}

// Setters

void Person::setLast(string l) {
  this->last = l;
}

void Person::setFirst(string first) {
  this->first = first;
}

// Getters

string Person::getLast() {
  return last;
}

string Person::getFirst() {
  return first;
}

string Person::getEmail() {
  return email;
}

// Prints emails

void Person::printEmail(vector<Person>& list, ostream& out) {

  for(size_t i = 0; i < list.size(); i++)
  {
    Person person;
    person = list[i];

    out << person.getLast()<< ", " << person.getFirst() << endl;
    person.address.printAddress(out);

    out << person.getEmail() << endl;
    person.bday.printDate(out);
  }
}
