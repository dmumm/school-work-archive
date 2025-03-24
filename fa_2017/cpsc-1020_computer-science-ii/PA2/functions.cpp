// Dylan Mumm, dmumm
// CPSC 1020, Fall 2017
// PA2, October 13th
// Dr. Yvon Feaster

#include "functions.hpp"

void readBirth(Date& birth)
{

  // Prompting user

  cout << "Enter the month of your birth: ";
  cin >> birth.month;

  cout << "Enter the day of your birth: ";
  cin >> birth.day;

  cout << "Enter the year of your birth: ";
  cin >> birth.year;

  cout << endl;



  // When appropriate conditions for a date are met, error is set to 0,
  // if 1, re-calls function

  int error = 1;
  if(birth.year >= 1900)
  {

    if(birth.month == 1 || birth.month == 3 || birth.month == 5 ||
       birth.month == 7 || birth.month == 8 || birth.month == 10 ||
       birth.month == 12)
    {
         if(birth.day <= 31 && birth.day >= 1)
          error = 0;
    }

    else if(birth.month == 4 || birth.month == 6 || birth.month == 9 ||
            birth.month == 11)
    {
         if(birth.day <= 30 && birth.day >= 1)
          error = 0;
    }

    else if(birth.month == 2)
    {
        if(birth.day <= 28 && birth.day >= 1)
          error =  0;

        else if(birth.day == 29)
        {
          if(birth.year % 4 == 0 && !(birth.year % 100 == 0))
            error = 0;

          else if(birth.year % 400 == 0)
            error = 0;
        }
      }
    }

  if(error == 1)
  {
    cout << "You have inputted at least one invalid value!\n" << endl;
    readBirth(birth);
  }
}

void readDate(Date& date, Date birth)
{
  cout << "Enter the desired month: ";
  cin >> date.month;

  cout << "Enter the desired day: ";
  cin >> date.day;

  cout << "Enter the desired year: ";
  cin >> date.year;

  cout << endl;

  int error = 1;
  if(date.year > birth.year ||
  (date.year > birth.year && date.month > birth.month) ||
  (date.year > birth.year && date.month == birth.month  &&
    date.day == birth.day))
  {
    if(date.month == 1 || date.month == 3 || date.month == 5 ||
       date.month == 7 || date.month == 8 || date.month == 10 ||
       date.month == 12)
    {
         if(date.day <= 31 && date.day >= 1)
          error = 0;
    }

    else if(date.month == 4 || date.month == 6 || date.month == 9 ||
            date.month == 11)
    {
         if(date.day <= 30 && date.day >= 1)
          error = 0;
    }

    else if(date.month == 2)
    {
        if(date.day <= 28 && date.day >= 1)
          error =  0;

        else if(date.day == 29)
        {
          if(date.year % 4 == 0 && !(date.year % 100 == 0))
            error = 0;

          else if(date.year % 400 == 0)
            error = 0;
        }
      }
    }

  if(error == 1)
  {
    cout << "You have inputted at least one invalid value!\n" << endl;
    readDate(date, birth);
  }
}

void calculateAge(Date& difference, Date date, Date birth)
{
  // if need be, "borrows" from larger unit
  // calculating days

  if (date.day < birth.day)
  {
    if(date.month == 1 || date.month == 3 || date.month == 5 ||
       date.month == 7 || date.month == 8 || date.month == 10 ||
       date.month == 12) {
         date.day = date.day + 31;
    }
    else if(date.month == 4 || date.month == 6 || date.month == 9 ||
               date.month == 11) {
         date.day = date.day + 30;
    }
    else if((date.month == 2 && date.year % 4 == 0 && !(date.year % 100 == 0))
              || (date.month == 2 && date.year % 400 == 0)) {
         date.day = date.day + 29;
   }
   else {
     date.day = date.day + 28;
   }
   date.month = date.month - 1;
 }
 difference.day = date.day - birth.day;



 // calculating months

 if(date.month < birth.month) {
   date.year = date.year - 1;
   date.month = date.month + 12;
 }
 difference.month = date.month - birth.month;

 // calculating years

 difference.year = date.year - birth.year;

}

void printAge(Date difference, Date date)
{

  // String array to print month name
  string months[12] = {"January", "February", "March", "April",
                    "May", "June", "July", "August", "September",
                    "October", "November", "December"};

  cout << "\nOn " << months[date.month-1] << " " << date.day << ", "
       << date.year << " you are " << difference.year << " years, "
       << difference.month << " months, and " << difference.day
       << " days old." << endl;




}
