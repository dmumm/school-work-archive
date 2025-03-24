// Dylan Mumm
// PA3
// Dr Yvon Feaster, CPSC 1020
// November 17th

#include "Book.hpp"

int Book::uniqueID = 0;

Book::Book(string t, string f, string l, int nu,
           string na, string ci, string s, int z, string w,
           string ca, string i)
           : title(t),
             author(f, l, nu, na, ci, s, z, w),
             category(ca), isbn(i)
{
  uniqueID++;
}

Book::Book() :
        title("title"),
        author("first", "last", 0, "streetName", "city", "state", 0, "site"),
        category("category"), isbn("isbn")
{
}


void Book::setTitle(string t)
{
  this->title = t;
}

void Book::setAuthor(Person a)
{
  this->author = a;
}

void Book::setCategory(string c)
{
  this->category = c;
}

void Book::setISBN(string i)
{
  this->isbn = i;
}

string Book::getTitle()
{
  return title;
}

Person Book::getAuthor()
{
  return author;
}

string Book::getCategory()
{
  return category;
}

string Book::getISBN()
{
  return isbn;
}

void Book::printBooks() const
{
  cout << "*********************************" << endl;

  cout << "Book Title:" << endl
       << this->title << endl << endl;

  this->author.printPerson();

  cout << "Category:" << endl
       << this->category << endl << endl;

  cout << "Book's ISBN:"
       << this->isbn << endl << endl;
}


 int Book::getUniqueID()
{
  return uniqueID;
}
