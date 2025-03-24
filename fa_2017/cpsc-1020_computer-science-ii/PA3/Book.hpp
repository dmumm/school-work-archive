// Dylan Mumm
// PA3
// Dr Yvon Feaster, CPSC 1020
// November 17th

#ifndef BOOK_HPP
#define BOOK_HPP
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Address.hpp"
#include "Person.hpp"
using namespace std;

class Book
{
  private:
    string title;
    Person author;
    string category;
    string isbn;
    /*static member variable*/
    static int uniqueID;


  public:
    /*Constructors*/

    Book(string, string, string, int, string, string, string, int, string,
            string, string);
    Book();

    /*Getters and Setters*/

    void setTitle(string);
    void setAuthor(Person);
    void setCategory(string);
    void setISBN(string);

    string getTitle();
    Person getAuthor();
    string getCategory();
    string getISBN();

    /*I want you to use a static function to allow you to access the value of
     *the static variable above.*/

    void printBooks() const;
    static int getUniqueID();


};

#endif
