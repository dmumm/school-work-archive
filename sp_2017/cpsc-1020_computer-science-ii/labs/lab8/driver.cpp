/* Dylan Mumm
 * dmumm
 * Lab 8
 * Nick Glyder, Section 004
 */

#include "Date.h"
using namespace std;

void oldestDate(ofstream& file2, vector<Date> Dates);

int main(int argc, char const *argv[])
{
  // Declarations

  ifstream file1;
  ofstream file2;

  vector<Date> Dates;

  int numDates;

  // Opening files

  file1.open(argv[1]);
  file2.open(argv[2]);

  if (file1.is_open() && file2.is_open())
  {
    cout << "Files loaded successfully" << endl;
  }
  else
  {
    cout << "Files loaded unsuccessfully" << endl;
  }

  // Reading first line of input as
  // total number of dates
  file1 >> numDates;

  // Initializing vector of Date objects
  // the size of numDates with default constructor

  for(int i = 0; i < numDates; i++)
  {
    Dates.push_back(Date());
  }

  // Storing dates in input file in
  // vector of Date objects
  for(int i = 0; i < numDates; i++)
  {

    int m, d, y;
    file1 >> m >> d >> y;

    Dates.at(i).setMonth(m);
    Dates.at(i).setDay(d);
    Dates.at(i).setYear(y);
  }

  // Calling function to find print
  // Oldest Date to output file
  oldestDate(file2, Dates);

  file1.close();
  file2.close();

 }


void oldestDate(ofstream& file2, vector<Date> Dates)
{

  // Declaring variables
  int numDates = Dates.size();
  int i;

  // Declaring date object with Overloaded
  // constructor
  Date OldestDate(12, 12, 10000);

  // Declaring string array of months
  string monthName[] = {"January", "February", "March", "April", "May",
                         "June", "July", "August", "September", "October",
                         "November", "December"};

  // For loop that finds oldest date

  for(i = 0; i < numDates; i++)
  {
    if(Dates.at(i).getYear() < OldestDate.getYear())
    {
      OldestDate.setYear(Dates.at(i).getYear());
      OldestDate.setMonth(Dates.at(i).getMonth());
      OldestDate.setDay(Dates.at(i).getDay());
    }
    else if(Dates.at(i).getYear() == OldestDate.getYear() &&
            Dates.at(i).getMonth() < OldestDate.getMonth())
    {
      OldestDate.setYear(Dates.at(i).getYear());
      OldestDate.setMonth(Dates.at(i).getMonth());
      OldestDate.setDay(Dates.at(i).getDay());
    }
    else if(Dates.at(i).getYear() == OldestDate.getYear() &&
            Dates.at(i).getMonth() == OldestDate.getMonth() &&
            Dates.at(i).getDay() < OldestDate.getDay())
    {
      OldestDate.setYear(Dates.at(i).getYear());
      OldestDate.setMonth(Dates.at(i).getMonth());
      OldestDate.setDay(Dates.at(i).getDay());
    }
  }

  // Printing oldest date to output file
  file2 << monthName[OldestDate.getMonth() - 1] << " "
        << OldestDate.getDay() << ", " << OldestDate.getYear() << endl;
}
