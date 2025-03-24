/* Dylan Mumm
 * dmumm
 * Lab 10
 * Nick Glyder, Section 004
 *
 * Victor Gamble
 * mlgambl
 * Lab 10
 * Nick Glyder, Section 005
 */

#include "Person.h"
#include <iostream>
using namespace std;

/*Use initialization list to initialize the two following constructors */

Person::Person(string n, string a, string c, string s, int z)
  : name(n), address(a), city(c), state(s), zip(z)
{

}
Person::Person()
  : name(" "), address(" "), city(" "), state(" "), zip(0)
{

}

/*Setters*/
void Person::setName(string n)
{
    this->name = n;
}
void Person::setAddress(string a)
{
    this->address = a;
}
void Person::setState(string s)
{
    this->state = s;
}
void Person::setCity(string c)
{
    this->city = c;
}
void Person::setZip(int z)
{
    this->zip = z;
}


/*The next two functions are used to print the Sender and Recipient's
 *mailing information*/

void Person::printSenderInfo()
{
  cout << "\n\nSENDER ADDRESS:" << endl;
  cout << this->name << endl;
  cout << this->address << endl;
  cout << this->city << ", " << this->state << "  " << this->zip << endl;
}

void Person::printRecipientInfo()
{
  cout << "\n\nRECIPIENT ADDRESS:" << endl;
  cout << this->name << endl;
  cout << this->address << endl;
  cout << this->city << ", " << this->state << "  " << this->zip << endl;
}
