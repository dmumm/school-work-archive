//@ Dylan Mumm, 2120
//@ Assignment 1
//@ February 11th

#include "MySentence.h"

MySentence::MySentence(string s) : str(s), size(s.length()) {}

// Swaps sides of chars
void MySentence::reverse() {
  for(int i = 0; i < size / 2; i++)
    swap(str[i], str[size-i-1]);
}

// If a letter, iterates it up one, depending on capital or not, and wraps
// around if 'z'
char MySentence::rotationOf(char ch) {
  if (isalpha(ch)) {
    if (ch == 'z')
        ch = 'a';
    else if (ch == 'Z')
        ch = 'A';
    else
        ch++;
  }
  return ch;
}

// calls rotationOf() for each char in sentence
void MySentence::rotate() {
  for(int i = 0; i < size; i++)
    str[i] = rotationOf(str[i]);
}

// calls rotate() multiple times as parameter instructs
void MySentence::rotate(const int shifts) {
  for(int i = 0; i < shifts; i++)
    rotate();
}

// adds up and returns "score" for MySentence
double MySentence::scoreWith(const Corpus& corp) const{
  double score = 0;
  for(int i = 0; i < size; i++) {
    if(isalpha(str[i])) {
      score += corp.proportion(tolower(str[i]));
    }
  }
  return score;
}

// reverses, finds what rotation has highest score, and decrypts to that
void MySentence::decode(const Corpus& corp) {
  double maxScore = 0;
  int best = 0;

  reverse();

  for(int i = 0; i <= 26; i++) {
    rotate();
    if(scoreWith(corp) > maxScore) {
      best = i;
      maxScore = scoreWith(corp);
    }
  }
  rotate(best);
}

// returns true if inputted string is equal to object
bool MySentence::operator==(const MySentence& right) const {
  return !(str.compare(right.str));
}

// prints out inputted object
ostream& operator<<(ostream& left, const MySentence& right) {
  for(int i = 0; i < right.size; i++)
    left << right.str[i];
  return left;
}
