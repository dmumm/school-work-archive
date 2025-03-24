// Dylan Mumm
// PA4
// Dr Yvon Feaster, CPSC 1020
// December 8th


#include "Vegetable.hpp"

int Vegetable::vegtCount = 0;
double Vegetable::totalVegtSales = 0;

Vegetable::Vegetable() : ProduceStand() {}

Vegetable::Vegetable(ifstream& in, ofstream& out)
{
  // Reads in line from input
  in >> name >> weight >> pricePerlb >> pricePerEach >> howMany;

  // Capitalizes first character
  name[0] = toupper(name[0]);

  // Calls member functions
  this->printReceipt(out);
  this->calculateTax(out);
  this->calculateSale(out);

  // Iterates static variables
  receiptNum++;
  vegtCount++;
}

Vegetable::Vegetable(string n, double w, double pw, double pe, int m) :
                                              ProduceStand(n, w, pw, pe, m) {}

// Getters

double Vegetable::getTotalVegtSales() {
  return totalVegtSales;
}

int Vegetable::getVegtCount() {
  return vegtCount;
}



void Vegetable::calculateTax(ofstream& out)
{
  // If it doesn't have weight, calculates by quantity, else, calculates by lb
  if(weight == 0 && pricePerlb == 0)
  {
    eachSale = pricePerEach * howMany;
    eachSalesTax = eachSale * SALES_TAX;
  }

  else
  {
    eachSale = pricePerlb * weight;
    eachSalesTax = eachSale * SALES_TAX;
  }

  // Adds up sales tax and prints
  dailySalesTax = dailySalesTax + eachSalesTax;
  out << setw(30) << right << fixed << setprecision(2) << eachSalesTax << endl;
}

// Calculates total sales
void Vegetable::calculateSale(ofstream& out)
{
  double dollars;
  dollars = eachSale + eachSalesTax;
  dailySales = dailySales + eachSale;
  totalVegtSales = totalVegtSales + eachSale;
  out << setw(41) << left << "    Total: "
      << right << fixed << setprecision(2) << dollars << endl << endl;
}

//print receipt for each vegetable sale
void Vegetable::printReceipt(ofstream& out)
{
  if(weight == 0 && pricePerlb == 0)
  {
    eachSale = pricePerEach * howMany;
  }

  else
  {
    eachSale=pricePerlb * weight;
  }

  out << setw(41) << left << name << right << fixed << setprecision(2)
      << eachSale << endl << left << "    Sales Tax: ";
}

void Vegetable::printInfo(ofstream& out)
{
  out << "Number of vegetable sales for the day: " << Vegetable::getVegtCount()
      << endl << "Total vegetable sales of $" << Vegetable::getTotalVegtSales()
      << " for the day" << endl;
}
