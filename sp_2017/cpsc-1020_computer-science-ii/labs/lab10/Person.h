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

#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

class Person
{
  private:
    string name;
    string address;
    string city;
    string state;
    int zip;

  public:
    Person(string, string, string, string, int);
    Person();
    void setName(string);
    void setAddress(string);
    void setState(string);
    void setCity(string);
    void setZip(int);

    void printSenderInfo();
    void printRecipientInfo();

};

#endif
