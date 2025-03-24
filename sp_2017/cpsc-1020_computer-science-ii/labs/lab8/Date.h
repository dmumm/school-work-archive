/* Dylan Mumm
 * dmumm
 * Lab 8
 * Nick Glyder, Section 004
 */

#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Date
{
	private:
		int month;
		int day;
		int year;

	public:
		/*Default constructors*/
		Date();

		/*Overloaded constructor*/
		Date(int, int, int);

		/*Setters*/
		void setMonth(int);
		void setDay(int);
		void setYear(int);

		/*Getters*/
		int getMonth();
		int getDay();
		int getYear();

};

#endif
