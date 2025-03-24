// Dylan Mumm
// PA3
// Dr Yvon Feaster, CPSC 1020
// November 17th

#ifndef ADDRESS_HPP
#define ADDRESS_HPP
#include <iostream>
#include <string>

using namespace std;

class Address
{
  private:
    int streetNum;
    string streetName;
    string city;
    string state;
    int zip;
    string site;

  public:

    /*Constructors*/
    Address(int , string , string , string , int , string );
    Address();

    /*Getters and Setters*/
    void setStreetNum(int);
    void setStreetName(string);
    void setCity(string);
    void setState(string);
    void setZip(int);
    void setSite(string);

    int getStreetNum();
    string getStreetName();
    string getCity();
    string getState();
    int getZip();
    string getSite();


    /*Other functions*/
    void printAddress() const;


};

#endif
