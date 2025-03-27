#ifndef CHAR_RECORD_H
#define CHAR_RECORD_H
#include <string>

using namespace std;

class CharRecord
{
  public:

    CharRecord();
    CharRecord(string s, int i);
    string getCharString();
    int getCount();

    friend bool operator> (const CharRecord &left, const CharRecord &right);
    friend bool operator< (const CharRecord &left, const CharRecord &right);

  private:

    string chars;
    int count;


};



#endif
