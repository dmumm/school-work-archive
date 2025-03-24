// Dylan Mumm
// PA4
// Dr Yvon Feaster, CPSC 1020
// December 8th


#include "ProduceStand.hpp"

// Static variables

int ProduceStand::receiptNum = 1;
double ProduceStand::dailySales = 0;
double ProduceStand::dailySalesTax = 0;

// Constructors

ProduceStand::ProduceStand() : name("name"), weight(0), pricePerlb(0),
                               pricePerEach(0), howMany(0) {}

ProduceStand::ProduceStand(string n, double w, double pw, double pe, int m) :
              name(n), weight(w), pricePerlb(pw), pricePerEach(pe), howMany(m){}

// Deconstructor

ProduceStand::~ProduceStand() {}

// Setter

void ProduceStand::setStandName(string n) {
  standName = n;
}

// Getters

string ProduceStand::getStandName() {
  return standName;
}

int ProduceStand::getReceiptNum() {
  return receiptNum;
}

double ProduceStand::getDailySales() {
  return dailySales;
}

double ProduceStand::getDailySalesTax() {
  return dailySalesTax;
}

// Prints header

void ProduceStand::printHeader(ofstream& out)
{
  out << "**************************************************" << endl;
  out << "Dylan's Produce Stand" << " | " << "Clemson, SC" << " | "
      << "Receipt #" << receiptNum << endl;

  out << "**************************************************" << endl << endl;

}

// Prints total sales

void ProduceStand::printData(ofstream& out)
{
  out << "Total sales for the day: $" << ProduceStand::getDailySales() << endl
      << "Total sales tax collected for the day: $"
      << ProduceStand::getDailySalesTax() << endl;
}
