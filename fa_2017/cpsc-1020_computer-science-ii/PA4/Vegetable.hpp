#ifndef VEGETABLE_H
#define VEGETABLE_H

#include <string>
#include "ProduceStand.hpp"
#include <fstream>
#include <iostream>
#include <cctype>

#define SALES_TAX 0.08

using namespace std;

class Vegetable : public ProduceStand
{
  private:

    static double totalVegtSales;
    static int vegtCount;

  public:
    //constructor
    Vegetable();
    Vegetable(ifstream&, ofstream& out);
    Vegetable(string, double, double, double, int);
    virtual ~Vegetable() {}

    virtual void calculateTax(ofstream& out);
    virtual void calculateSale(ofstream& out);
    virtual void printReceipt(ofstream& out);
    void printInfo(ofstream& out);

    static double getTotalVegtSales();
    static int getVegtCount();

};

#endif
