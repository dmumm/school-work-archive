// Dylan Mumm
// PA3
// Dr Yvon Feaster, CPSC 1020
// November 17th

#include "Book.hpp"
#include "Address.hpp"
#include "Person.hpp"

using namespace std;

void read(ifstream& in, vector<Book>& l)
{

  // Reads in one book at a time into temp storage, then using a Constructors
  // to push_back to end of vector, with a simple count

  string t, f, la, na, ci, s, w, ca, i, space;
  int nu, z;

  while(getline(in, t))
  {
    getline(in, f);
    getline(in, la);
    in >> nu;
    in.ignore();
    getline(in, na);
    getline(in, ci);
    getline(in, s);
    in >> z;
    in.ignore();
    getline(in, w);
    getline(in, ca);
    getline(in, i);
    getline(in, space);

    l.push_back(Book(t, f, la, nu, na, ci, s, z, w, ca, i));

  }

}

void printLibrary(ofstream& out, vector<Book> l)
{

  // Loops through vectors, using print functions

  for(int i=0; i<Book::getUniqueID(); i++)
  {
    l.at(i).printBooks();
  }

  cout << "*********************************" << endl;
  cout << "There are " << Book::getUniqueID() << " books in this library"
       << endl;

}


int main(int argc, char const *argv[]) {

  // file i/o

  ifstream input(argv[1]);
  ofstream output(argv[2]);

  if(argc != 3) {
    cout << "USAGE ERROR:  ./executable input output";
    return -1;
  }
  if(input.fail())  {
    cout << argv[1] << " did not open successfully\n";
  }
  if(output.fail()) {
    cout << argv[2] << " did not open successfully\n";
  }

  //declaring vector and calling functions

  vector<Book> library;

  read(input, library);
  printLibrary(output, library);

  input.close();
  output.close();


  return 0;
}
