// Dylan Mumm
// PA3
// Dr Yvon Feaster, CPSC 1020
// November 17th

#include "Address.hpp"


Address::Address(int streetNum, string streetName, string city, string state,
                 int zip, string site)
                 : streetNum(streetNum), streetName(streetName), city(city),
                   state(state), zip(zip), site(site)
{
}

Address::Address() : streetNum(0), streetName("streetName"), city("city"),
  state("state"), zip(0), site("site")
{
}

void Address::setStreetNum(int streetNum)
{
  this->streetNum = streetNum;
}
void Address::setStreetName(string streetName)
{
  this->streetName = streetName;
}
void Address::setCity(string city)
{
  this->city = city;
}
void Address::setState(string state)
{
  this->state = state;
}
void Address::setZip(int zip)
{
  this->zip = zip;
}
void Address::setSite(string site)
{
  this->site = site;
}

int Address::getStreetNum()
{
  return streetNum;
}

string Address::getStreetName()
{
  return streetName;
}

string Address::getCity()
{
  return city;
}

string Address::getState()
{
  return state;
}

int Address::getZip()
{
  return zip;
}

string Address::getSite()
{
  return site;
}

void Address::printAddress() const
{
  cout  << this->streetNum << " "
        << this->streetName << endl
        << this->city << ", "
        << this->state << "  "
        << this->zip << "  " << endl
        << this->site << "  " << endl << endl;
}
