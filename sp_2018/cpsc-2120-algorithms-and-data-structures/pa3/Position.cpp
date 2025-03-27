#include "Position.h"

/* constructor */
Position::Position(vector<int> input) : holes(input) {}

bool
Position::isDone() {

  for(int val : holes) {
      if(val > 0)
       return false;
  }

  return true;

}

Position*
Position::afterMove(int move) {

  if(isDone())
    return nullptr;

  int stones = holes[move-1];
  holes[move-1] = 0;
  for(int hole = move; stones > 0; stones--) {
    if(hole < 5) {
      holes[hole]++;
      hole++;
    }
    else {
      hole = 0;
    }
  }

  return this;

}


int
Position::getVal(int hole) const {
  return holes[hole];
}

bool
Position::operator==(const Position &p) const {

  for(int i = 0; i < 5; i++) {
    if(getVal(i) != p.getVal(i))
      return false;
  }

  return true;

}

ostream&
operator<<(ostream& out, const Position& p) {

  out << "[";

  for(int i = 0; i < 4; i++)
    out << p.getVal(i) << ".";

  out << p.getVal(4) << "]";

  return out;

}
