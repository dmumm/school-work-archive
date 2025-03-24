//@ Dylan Mumm, 2120
//@ Assignment 1
//@ February 11th


#include "Corpus.h"

// Uses scrabble set to determine proportions, prints out frequencies
Corpus::Corpus() : prop{0.09, 0.02, 0.02, 0.04, 0.12, 0.02, 0.03, 0.02, 0.09,
                        0.01, 0.01, 0.04, 0.02, 0.06, 0.08, 0.02, 0.01, 0.06,
                        0.04, 0.06, 0.04, 0.02, 0.02, 0.01, 0.02, 0.01} {
  cout << "Frequences are ";
  for(int i = 0; i < 9; i++)
    cout << fixed << setprecision(3) << prop[i] << ", ";
  cout << endl << "               ";
  for(int i = 9; i < 18; i++)
    cout << fixed << setprecision(3) << prop[i] << ", ";
  cout << endl << "               ";
  for(int i = 18; i < 26; i++)
    cout << fixed << setprecision(3) << prop[i] << ", ";
  cout << endl;
}

// Uses inputted file to determine proportions, prints out frequencies
Corpus::Corpus(const string file) {

  double totalCount = 0;
  double count[26] {0};
  ifstream input(file);

  char ch;
  while(input) {
    input.get(ch);
    if(isalpha(ch)) {
      ch = tolower(ch);
      count[ch - 97]++;
      totalCount++;
    }
  }

  for(int i = 0; i < 26; i++)
    prop[i] = count[i] / totalCount;

    cout << "Frequences are ";
    for(int i = 0; i < 9; i++)
      cout << fixed << setprecision(3) << prop[i] << ", ";
    cout << endl << "               ";
    for(int i = 9; i < 18; i++)
      cout << fixed << setprecision(3) << prop[i] << ", ";
    cout << endl << "               ";
    for(int i = 18; i < 26; i++)
      cout << fixed << setprecision(3) << prop[i] << ", ";
    cout << endl;

}

// returns proportion of inputted lowercase char
double Corpus::proportion(const char ch) const {
  return prop[ch - 97];
}
