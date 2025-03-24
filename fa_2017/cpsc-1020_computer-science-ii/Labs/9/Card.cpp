// Dylan Mumm, dmumm
// Lab 9, Section 002
// Nick Glyder, nglyder

#include "Card.hpp"

Card::Card() {
  this->value = 2;
  this->cardSuit = Card::Suit::HEARTS;
}

Card::Card(int value, Card::Suit cardSuit) {
  this->value = value;
  this->cardSuit = cardSuit;
}

Card::~Card() {}

int Card::getValue() const {
  return this->value;
}

Card::Suit Card::getSuit() const {
  return this->cardSuit;
}

void Card::setValue(int value) {
  this->value = value;
}

void Card::setSuit(Card::Suit cardSuit) {
  this->cardSuit = cardSuit;
}

void Card::print() {
  if(this->value == 14)
    cout << "A";
  else if(this->value == 13)
    cout << "K";
  else if(this->value == 12)
    cout << "Q";
  else if(this->value == 11)
    cout << "J";
  else
    cout << this->value;

  switch (this->cardSuit) {
    case Card::Suit::HEARTS:
      cout << "\u2665";
      break;
    case Card::Suit::DIAMONDS:
      cout << "\u2666";
      break;
    case Card::Suit::SPADES:
      cout << "\u2660";
      break;
    case Card::Suit::CLUBS:
      cout << "\u2663";
    }
}
