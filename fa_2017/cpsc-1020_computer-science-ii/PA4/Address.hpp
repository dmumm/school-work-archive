// Dylan Mumm
// PA4
// Dr Yvon Feaster, CPSC 1020
// December 8th


#ifndef ADDRESS_H
#define ADDRESS_H
#include <string>
#include <iostream>

using namespace std;

class Address
{
  private:
    int house;
    string street;
    string city;
    string state;
    int zip;

  public:

    Address();
    Address(int, string, string, string, int);

    void setHouse(int);
    void setStreet(string);
    void setCity (string);
    void setState(string);
    void setZip(int);

    void printAddress(ostream&);


};

#endif
