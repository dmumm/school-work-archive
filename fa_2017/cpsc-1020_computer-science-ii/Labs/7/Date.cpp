#include "Date.hpp"

// Just an array of strings. Access a month using:
// Date::MONTHS[0] ---> "JANUARY"
const string Date::MONTHS[] = {
  "JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY",
  "JUNE", "JULY", "AUGUST", "SEPTEMBER", "OCTOBER",
  "NOVEMBER", "DECEMBER"
};

// Default, just make sure the fields are set to something
Date::Date() {
  this->month = 1;
  this->day = 1;
  this->year = 1000;
}
Date::~Date() {}

// Compare function which is true if lhs is earlier than rhs
bool Date::compare(const Date& lhs, const Date& rhs) {
  if(lhs.get_year() < rhs.get_year())
    return true;
  if(lhs.get_year() == rhs.get_year() && lhs.get_month() < rhs.get_month())
    return true;
  if(lhs.get_year() == rhs.get_year() && lhs.get_month() == rhs.get_month() &&
                                         lhs.get_day() < rhs.get_day())
    return true;
  return false;
}

// getter/setter
int Date::get_month() const {
  return this->month;
}

int Date::get_day() const {
  return this->day;
}

int Date::get_year() const {
  return this->year;
}

void Date::set_month(int month) {
  this->month = month;
}

void Date::set_day(int day) {
  this->day = day;
}

void Date::set_year(int year) {
  this->year = year;
}


// Returns a well formatted string representation of this Date
string Date::print() {
  stringstream  ss;
  ss << left << setw(10) << MONTHS[this->get_month()-1]
                  << setw(3)  << this->get_day()
                  << setw(5)  << this->get_year();
  return ss.str();
}
