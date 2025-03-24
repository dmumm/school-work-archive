// Dylan Mumm, dmumm
// Lab 6, Section 002
// TA: Nick Glyder, nglyder

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

int main (int argc, char* argv[])
{

  // declaring variables

  int id;
  long double price;
  double sumPrices;
  double countPrices;

  // initializing column values

  int idColumnWidth = 4;
  int titleColumnWidth = 27;
  int priceColumnWidth = 10;

  int totalCharacterReplacement = 3;
  char replacementCharacter = '.';

  unsigned int titleLength = 25;


  // initializing file pointers and ensuring they're working

  ifstream input(argv[1]);
  ofstream output(argv[2]);

  if(input.fail()){
    cout << argv[1] << " did not open successfully\n";
    return 0;
  }

  if(output.fail()){
    cout << argv[2] << " did not open successfully\n";
    return 0;
  }

 // column titles

  output << setw(idColumnWidth) << "ID" << setw(titleColumnWidth) << "Title"
         << setw(priceColumnWidth) << "Price" << endl;

  // Reading, finding, and printing row info

  while(input >> id)
  {

    sumPrices = 0;
    countPrices = 0;
    string title;

    // Reading prices, adding them up, and incrementing count
    input.imbue(std::locale("en_US.UTF-8"));
    while(input >> get_money(price)){
      sumPrices += price;
      countPrices++;
    }

    // clearing flags and reading title
    input.clear();
    getline(input, title);

    // if applicable, shortening too long of titles to 25 and adding "..."

    if(title.length() > titleLength)
    {
      title.erase(titleLength, string::npos);
      title.replace(titleLength - totalCharacterReplacement,
                    string::npos, totalCharacterReplacement,
                    replacementCharacter);
    }

    // printing to output

    output.imbue(std::locale("en_US.UTF-8"));
    output << setw(idColumnWidth) << id << setw(titleColumnWidth) << title
           << setw(priceColumnWidth) << put_money(sumPrices / countPrices)
           << endl;
  }

  input.close();
  output.close();

  return 0;
}
