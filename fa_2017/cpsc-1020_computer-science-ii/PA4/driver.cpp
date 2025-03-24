// Dylan Mumm
// PA4
// Dr Yvon Feaster, CPSC 1020
// December 8th


#include "Address.hpp"
#include "Date.hpp"
#include "Person.hpp"
#include "ProduceStand.hpp"
#include "Fruit.hpp"
#include "Vegetable.hpp"


#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>

using namespace std;

void readData(ifstream&, ofstream&, ofstream&);

int main(int argc, char const *argv[]) {

  // Creating and validating file pointers

  ifstream input(argv[1]);
  ofstream output(argv[2]);
  ofstream emailList(argv[3]);

  if(argc != 4) {
    cout << "ERROR:  ./executable Input.txt salesOutput.txt customerOutput.txt";
    return -1;
  }

  if(input.fail())  {
    cout << argv[1] << " did not open successfully\n";
  }
  if(output.fail()) {
    cout << argv[2] << " did not open successfully\n";
  }
  if(emailList.fail()) {
    cout << argv[3] << " did not open successfully\n";
  }

  // Calling function

  readData(input, output, emailList);

  // Closing file pointers

  input.close();
  output.close();
  emailList.close();

  return 0;
}

void readData(ifstream &input, ofstream &output, ofstream &emailList) {

  // Declaring varaibles

  string type = " ";
  char choice;
  int count = 0;
  ProduceStand stand;
  vector <Person> list;

  // Read until end of file
  input >> type;
  while(!input.eof())
  {
    // Determines type of produce
    stand.printHeader(output);

    if(type == "Vegetable")
      Vegetable veggie(input, output);

    else if(type=="Fruit")
      Fruit fruit(input, output);

    // Adds applicable customers to mailing list

    input >> choice;
    if(choice == 'y')
    {
      count++;
      int h, z, m, d, y;
      string l, f, em, str, c, sta;

      input >> l >> f >> em >> h >> str >> c >> sta >> z >> m >> d >> y;
      list.push_back(Person(l, f, em, h, str, c, sta, z, m, d, y));
    }

    input >> type;
  }

  Person person;

  // Prints information

  person.printEmail(list, emailList);
  stand.printData(output);

  Fruit fruit;
  fruit.printInfo(output);

  Vegetable veggie;
  veggie.printInfo(output);

  output << "Total customers added to the mailing list: " << count << endl;
}
