// Dylan Mumm
// PA4
// Dr Yvon Feaster, CPSC 1020
// December 8th


#include "Fruit.hpp"

// Static variables

int Fruit::fruitCount = 0;
double Fruit::totalFruitSales = 0;

// Constructors

Fruit::Fruit() : ProduceStand() {}

Fruit::Fruit(ifstream& in, ofstream& out)
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
  fruitCount++;
}

Fruit::Fruit(string n, double w, double pw, double pe, int m) :
                                              ProduceStand(n, w, pw, pe, m) {}

// Getters
double Fruit::getTotalFruitSales() {
  return totalFruitSales;
}

int Fruit::getFruitCount() {
  return fruitCount;
}

void Fruit::calculateTax(ofstream& out)
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
void Fruit::calculateSale(ofstream& out)
{
  double dollars;
  dollars = eachSale + eachSalesTax;
  dailySales = dailySales + eachSale;
  totalFruitSales = totalFruitSales + eachSale;
  out << setw(41) << left << "    Total: "
      << right << fixed << setprecision(2) << dollars << endl << endl;
}

// Print receipt for each fruit sale
void Fruit::printReceipt(ofstream& out)
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

void Fruit::printInfo(ofstream& out)
{
  out << "Number of fruit sales for the day: " << Fruit::getFruitCount()
      << endl << "Total fruit sales of $" << Fruit::getTotalFruitSales()
      << " for the day" << endl;
}
