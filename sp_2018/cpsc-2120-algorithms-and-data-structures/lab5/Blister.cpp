//@ Dylan Mumm, 2121
//@ Lab 5
//@ February 23rd

#include "Blister.h"
using namespace std;

// Constructor
Blister::Blister(string init) : start(nullptr) {
  // Builds linked list from last letter to first
  for(int i=init.length()-1; i >= 0; i--) {
    Bode *ptr = new Bode(init[i]);
    ptr->next = start;
    start = ptr;
  }
}

// Destructor
Blister::~Blister()  {
  Bode* grab;
  while(start != nullptr) {
    grab = start;
    start = start->next;
    grab->next = nullptr;
    delete grab;
  }
}

// Returns length of list
int Blister::length() const {
  // Starting from start of list, traverses through list, adding count for each
  // node until reaching nullptr
  int count = 0;
  for(Bode* cursor = start; cursor != nullptr; cursor = cursor->next)
    count++;
  return count;
}

// compares two base-sequences and returns true if
// they have the same length and differ in exactly one base.
bool Blister::isSubstitutionOf(const Blister& other) const {
  // Returns false if different length
  if(length() != other.length())
    return false;

  // Iterates through list, counts each instance of them not matching, returns
  // true if just one
  int count = 0;
  Bode* cursor1; Bode* cursor2;
  for(cursor1 = start, cursor2 = other.start;
      cursor1 != nullptr && cursor2 != nullptr;
      cursor1 = cursor1->next, cursor2 = cursor2->next) {
        if(cursor1->base != cursor2->base)
          count++;
      }
  return (count == 1);
}


// member function compares two base-sequences and returns true if the
// one it is called on is obtained by adding exactly one base to the
// other base-sequence.
bool Blister::isInsertionOf(const Blister& other) const {
  // returns false if other is not one less than the called on class
  if(length() - other.length() != 1)
    return false;

  // iterates through called on class, when they line up, increments counts
  // and iterates the other list. returns true if count equals length of other
  Bode* cursor1; Bode* cursor2;
  int count = 0;
  for(cursor1 = start, cursor2 = other.start;
      cursor1 != nullptr && cursor2 != nullptr;
      cursor1 = cursor1->next) {
        if(cursor1->base == cursor2->base) {
          count++;
          cursor2 = cursor2->next;
        }
      }
  return(count == other.length());
}

// outputs the sequence
ostream& operator<<(ostream& out, const Blister& bl) {
  // if empty, prints empty
  if(bl.start == nullptr )
    out << "--Empty--";

  // else, iterates through list and prints base until reaching nullptr
  else {
    for(Bode* cursor = bl.start; cursor != nullptr; cursor = cursor->next)
      out << cursor->base;
  }
  return out;
}
