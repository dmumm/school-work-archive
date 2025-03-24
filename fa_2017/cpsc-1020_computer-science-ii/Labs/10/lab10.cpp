// Dylan Mumm, dmumm
// Lab 10, Section 002
// Nick Glyder, nglyder

#include "Deck.hpp"
#include "Card.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
  Deck player;
  player.shuffle();

  cout << player.print() << endl;;

  cout << "Draw 5 cards" << endl;
  vector<Card> hand = player.draw(5);

  for(int i=0; i<5; i++)
  {
    if(hand.at(i).get_value() == 14)
      cout << "A";
    else if(hand.at(i).get_value() == 13)
      cout << "K";
    else if(hand.at(i).get_value() == 12)
      cout << "Q";
    else if(hand.at(i).get_value() == 11)
      cout << "J";
    else
      cout << hand.at(i).get_value();

    switch (hand.at(i).get_suit()) {
      case Card::Suit::HEARTS:
        cout << "\u2665 ";
        break;
      case Card::Suit::DIAMONDS:
        cout << "\u2666 ";
        break;
      case Card::Suit::SPADES:
        cout << "\u2660 ";
        break;
      case Card::Suit::CLUBS:
        cout << "\u2663 ";
      }
  }

  cout << player.print() << endl;

  return 0;
}
