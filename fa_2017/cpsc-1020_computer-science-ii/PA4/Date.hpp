// Dylan Mumm
// PA4
// Dr Yvon Feaster, CPSC 1020
// December 8th

#ifndef DATE_H
#define DATE_H
#include <iostream>
using namespace std;

class Date
{

  private:
    int month;
    int day;
    int year;

  public:

    Date();
    Date(int, int, int);
    ~Date();

    void setMonth(int);
    void setDay(int);
    void setYear(int);

    int getMonth();
    int getDay();
    int getYear();

    void printDate(ostream& out);

};
#endif
