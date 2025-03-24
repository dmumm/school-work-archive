#include <iostream>
using namespace std;
#include "PosPoly.h"

// default constructor, makes array of 100 structs, of ascending powers but
// coefficients of 0
PosPoly::PosPoly() {
  powerCount = 0;
  pairs = new Pair[100];
  for(int i=1; i <= 100; i++) {
    pairs[i].power = i;
    pairs[i].coeff = 0;
} }

// increments coefficients of parameter, increments powerCount when coefficient
// now above 0
void PosPoly::incrementBy(int c, int p) {
  if(pairs[p].coeff == 0) {
      powerCount++;
  }
  pairs[p].coeff += c;
}

// loops through whole array of structs, ensuring both have the same
// coefficients for each power
bool PosPoly::operator==(const PosPoly& right) const {
  if(powerCount == right.powerCount) {
    for(int i=1; i <= 100; i++) {
      if(pairs[i].coeff != right.pairs[i].coeff) {
        return false;
  } } }
  if (powerCount != right.powerCount) {
    return false;
  }
  else {
    return true;
} }

// Loops through array, printing terms without a coefficient of 0
ostream& operator<<(ostream& os, const PosPoly& right) {
  for(int i = 100; i >= 1; i--) {
    if(right.pairs[i].coeff != 0) {
      os << " + " << right.pairs[i].coeff << "x^" << right.pairs[i].power;
  } }
  return os;
}
