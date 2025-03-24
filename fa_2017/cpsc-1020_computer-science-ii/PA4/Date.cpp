// Dylan Mumm
// PA4
// Dr Yvon Feaster, CPSC 1020
// December 8th

#include "Date.hpp"

// Constructors

Date::Date() : month(0), day(0), year(0) {}

Date::Date(int m, int d, int y) : month(m), day(d), year(y) {}

// Deconstructor

Date::~Date() {}

// Setters

void Date::setMonth(int m) {
  month = m;
}

void Date::setDay(int d) {
  day = d;
}

void Date::setYear(int y) {
  year = y;
}

// Getters

int Date::getMonth() {
  return month;
}

int Date::getDay() {
  return day;
}

int Date::getYear() {
  return year;
}

// Prints date
void Date::printDate(ostream& out) {
  out << month << "/" << day <<"/" << year << endl << endl;
}
