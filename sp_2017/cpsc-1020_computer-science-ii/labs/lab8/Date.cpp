/* Dylan Mumm
 * dmumm
 * Lab 8
 * Nick Glyder, Section 004
 */

#include "Date.h"
using namespace std;

Date::Date(int m, int d, int y)
{
  month = m;
  day = d;
  year = y;
}

Date::Date()
{
  month = 0;
  day = 0;
  year = 0;
}

void Date::setMonth(int m)
{
  month = m;
}

void Date::setDay(int d)
{
  day = d;
}

void Date::setYear(int y)
{
  year = y;
}

int Date::getMonth()
{
  return month;
}

int Date::getDay()
{
  return day;
}

int Date::getYear()
{
  return year;
}
