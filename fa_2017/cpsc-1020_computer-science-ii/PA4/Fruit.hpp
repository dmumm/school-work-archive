#ifndef FRUIT_H
#define FRUIT_H

#include <string>
#include "ProduceStand.hpp"
#include <fstream>
#include <iostream>
#include <cctype>

#define SALES_TAX 0.08

using namespace std;

class Fruit : public ProduceStand
{
  private:

    static double totalFruitSales;
    static int fruitCount;

  public:

    Fruit();
    Fruit(ifstream&, ofstream&);
    Fruit(string, double, double, double, int);

    ~Fruit() {}

    static double getTotalFruitSales();
    static int getFruitCount();

    virtual void calculateTax(ofstream&);
    virtual void calculateSale(ofstream&);
    virtual void printReceipt(ofstream&);

    void printInfo(ofstream& out);


};

#endif
