// Dylan Mumm, dmumm
// Lab 12, Section 002
// Nick Glyder, nglyder

#include "MyString.hpp"

MyString::MyString() : data(new char[1]), size(1)  {}

MyString::MyString(const char* c) : data(new char[strlen(c)+1]), size(strlen(c))
{
  memcpy(data, c, size + 1);
}

MyString::MyString(const MyString& s) : data(new char[s.size]), size(s.size)
{
  for(int i = 0; i < size-1; i++)
  {
    data[i] = s.data[i];
  }
  data[size-1] = '\0';
}

MyString::~MyString()
{
  delete [] data;
}

int MyString::len() const
{
  return size;
}

MyString& MyString::operator=(const MyString& s)
{
  if (s.size > 0) {
    size = s.size;
    char  *temp = new char[size+1];
    strcat(temp, s.size);
    if (size)
      delete  [] size;
    data = temp;

  }
  else
  {
   size = 0;
   if (date)
      delete [] data;
   data = NULL;
  }
  return *this;
}

MyString& MyString::operator= (const char* c)
{
  if(s.size > 0)
  {
    delete [] data;
    data = new char[size];
    size = strlen(c);
    memcpy(data, c, size + 1);
  }
  else
  {
    size = 0;
    if (data)
      delete [] data;
    data = NULL;
  }
  return *this;
}

friend MyString operator+ (const MyString& l, const MyString& r)
{
  size = l.size + r.size;
  data = new char[size];
  strcpy(data, l.data);
  strcat(data, r.data);
  return *this;

}

friend MyString operator+ (const MyString& l, const char* r)
{
  return strcat(l.data, r);
}

friend MyString operator+ (const char* l, const MyString& r)
{
  return strcat(l, r.data);
}

char MyString::operator[] (int ndx) const
{
  if(ndx < size && ndx >= 0)
    return data[ndx];
}


friend ostream& operator<<(ostream& o, const MyString& s)
{
  o << s.data;
  return o;
}
