// Dylan Mumm
// PA4
// Dr Yvon Feaster, CPSC 1020
// December 8th

#include "Address.hpp"

// Constructors

Address::Address() : house(0), street("street"), city("city"), state("ST"),
                     zip(01234) {}

Address::Address(int h, string str, string c, string sta, int z) : house(h),
                                    street(str), city(c), state(sta), zip(z) {}

// Setters

void Address::setHouse(int h){
  this->house = h;
}

void Address::setStreet(string str){
  this->street = str;
}

void Address::setCity (string c){
  this->city = c;
}

void Address::setState(string sta){
  this->state = sta;
}

void Address::setZip(int z){
  this->zip = z;
}

// Prints address

void Address::printAddress(ostream& out){
  out << house << " " << street << endl
      << city << ", " << state << " " << zip << endl;
}
