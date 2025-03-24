#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include "stdlib.h"



using namespace std;

class Card {
  public: enum class Suit { HEARTS=0, DIAMONDS=1, SPADES=2, CLUBS=3 };

  private:
    int value;
    Suit suit;

  public:
    Card ();
    Card (int, Suit);
    Card (const Card&);
    virtual ~Card () {};

    int test;

    int get_value() const;
    void set_value(int value);

    Suit get_suit() const;
    void set_suit(Suit suit);

    string print() const;
};

#endif
