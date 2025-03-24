// Dylan Mumm, dmumm
// Lab 9, Section 002
// Nick Glyder, nglyder

#ifndef CARD_H
#define CARD_H

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

class Card {

  public:

    enum class Suit { HEARTS=0, DIAMONDS=1, SPADES=2, CLUBS=3 };

    // constructors
    Card ();
    Card (int value, Suit cardSuit);

    // destructor

    ~Card();

    // getters

    int getValue() const;
    Suit getSuit() const;

    // setters

    void setValue(int value);
    void setSuit(Suit cardSuit);

    void print();

  private:
    int value;
    Suit cardSuit;


};

#endif
