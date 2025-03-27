#ifndef RANGESET_H
#define RANGESET_H

#include <iostream>
#include "RNode.h"
using namespace std;

class RangeSet {
private:

   RNode *head;
   bool errorDetect(int min, int max);
   bool ifEmptyAdd(int min, int max);
   void deleteRange(int min, int max);
   void createMinimalForm(int min, int max);


public:

   // constructor
   RangeSet();

   // destructor
   ~RangeSet();

   // mutators
   void addRange(int min, int max);
   void addLonelyRange(int min, int max);
   bool deleteValue(int val);

   // accessors
   bool isInSet(const int val) const;
   void dump() const;

   // equality operator
   bool operator== (const RangeSet &r) const;

};

#endif
