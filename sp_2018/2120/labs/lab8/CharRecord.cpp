#include "CharRecord.h"


CharRecord::CharRecord() : chars("   "), count(0) {}


CharRecord::CharRecord(string s, int i) {
  chars = s;
  count = i;
}

string
CharRecord::getCharString() {
  return chars;
}

int
CharRecord::getCount() {
  return count;
}

bool
operator> (const CharRecord &left, const CharRecord &right) {
  return left.count > right.count;
}

bool
operator< (const CharRecord &left, const CharRecord &right) {
  return left.count < right.count;
}
