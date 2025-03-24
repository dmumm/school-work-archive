#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <vector>
using namespace std;

class Position {
private:

   vector<int> holes;

public:

   // constructor
   Position(vector<int>);

   // destructor
// ~Position();

   // methods
   int getVal(int) const;
   bool isDone();
   Position* afterMove(int);

   // operators
   bool operator== (const Position &p) const;

   // friends
   friend ostream& operator<< (ostream &out, const Position&);

};

#endif
