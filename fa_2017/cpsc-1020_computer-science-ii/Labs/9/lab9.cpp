// Dylan Mumm, dmumm
// Lab 9, Section 002
// Nick Glyder, nglyder

#include "Card.hpp"


int main(int argc, char *argv[])
{

  int P1Wins = 0;
  int P2Wins = 0;
  int Draws = 0;



  Card deck1[52];
  Card deck2[52];

  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 13; j++) {
      deck1[(i * 13) + j].setValue(j+2);
      deck2[(i * 13) + j].setValue(j+2);
      switch(i) {
        case 0:
          deck1[(i * 13) + j].setSuit(Card::Suit::HEARTS);
          deck2[(i * 13) + j].setSuit(Card::Suit::HEARTS);
          break;
        case 1:
          deck1[(i * 13) + j].setSuit(Card::Suit::DIAMONDS);
          deck2[(i * 13) + j].setSuit(Card::Suit::DIAMONDS);
          break;
        case 2:
          deck1[(i * 13) + j].setSuit(Card::Suit::SPADES);
          deck2[(i * 13) + j].setSuit(Card::Suit::SPADES);
          break;
        case 3:
          deck1[(i * 13) + j].setSuit(Card::Suit::CLUBS);
          deck2[(i * 13) + j].setSuit(Card::Suit::CLUBS);
      }
    }
  }


  random_shuffle(begin(deck1), end(deck1));
  random_shuffle(begin(deck2), end(deck2));

  for(int i = 0; i < 52; i++) {

    deck1[i].print();
    deck2[i].print();

    if(deck1[i].getValue() > deck2[i].getValue()) {
      cout << "P1 Wins" << endl;
      P1Wins++;
    }

    else if(deck1[i].getValue() < deck2[i].getValue()) {
      cout << "P2 Wins" << endl;
      P2Wins++;

    }

    else {
      cout << "Draw" << endl;
      Draws++;
    }
  }

  cout << "P1 Total Wins = " << P1Wins << endl;
  cout << "P2 Total Wins = " << P2Wins << endl;
  cout << "Draws = "         << Draws  << endl;

  return 0;

}
