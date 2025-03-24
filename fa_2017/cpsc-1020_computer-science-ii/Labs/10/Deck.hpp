// Dylan Mumm, dmumm
// Lab 10, Section 002
// Nick Glyder, nglyder

#ifndef DECK_H
#define DECK_H

#include "Card.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

class Deck {

  private:
    vector<Card> cards;

  public:
    Deck ();
    ~Deck () {};

    int num_cards();
    void shuffle();
    void reset();
    Card draw();
    vector<Card> draw(int num);
    string print() const;
};

#endif
