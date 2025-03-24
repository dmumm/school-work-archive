// Dylan Mumm, dmumm
// Lab 10, Section 002
// Nick Glyder, nglyder

#include "Deck.hpp"

Deck::Deck()
{
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 13; j++) {
      switch(i) {
        case 0:
          this->cards.push_back(Card(j+2, Card::Suit::HEARTS));
          break;
        case 1:
          this->cards.push_back(Card(j+2, Card::Suit::DIAMONDS));
          break;
        case 2:
          this->cards.push_back(Card(j+2, Card::Suit::SPADES));
          break;
        case 3:
          this->cards.push_back(Card(j+2, Card::Suit::CLUBS));
      }
    }
  }
}

int Deck::num_cards()
{
  return this->cards.size();
}

void Deck::shuffle()
{
  random_shuffle(this->cards.begin(), this->cards.end());
}

void Deck::reset()
{
  this->cards.clear();
  Deck();
}


Card Deck::draw()
{
  Card drawn;
  drawn = this->cards.back();
  this->cards.pop_back();
  return drawn;
}

vector<Card> Deck::draw(int num)
{
  vector<Card> hand;
  for(int i=0; i<num; i++)
  {
    hand.push_back(this->cards.back());
    this->cards.pop_back();
  }
  return hand;
}

string Deck::print() const
{
  stringstream out;
  out << endl << "Deck has " << this->cards.size() << " cards" << endl;
  for (auto itr = this->cards.cbegin(); itr != this->cards.cend(); itr++)
  {
    out << (*itr).print() << " ";
  }
  return out.str();
}
