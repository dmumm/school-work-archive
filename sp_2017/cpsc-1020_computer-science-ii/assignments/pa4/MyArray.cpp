#include "MyArray.h"

/*These are two client (helper) functions that you may use */
int MyArrayLength(const char* str)
{
  //cout << "MyArrayLength\n";
  int len = 0;
  const char* s = str;
  while( *s != '\0')
  {
    len++;
    s++;
  }
  return len;
}

void MyArrayCopy(char* dest, const char* src, int n)
{
  //cout << "MyArrayCopy\n";
  int i;
  for(i = 0; i < n; i++)
  {
    dest[i] = src[i];
  }
}

/*Implement the class functions here. */

MyArray::MyArray()
{
  cout << "Default constructor" << endl;

  ptr = new char[4]
  ptr = "rofl";
  size = strlen(ptr);
}

MyArray::MyArray(const char* arr)
{
  cout << "Regular constructor" << endl;

  ptr = new char[strlen(arr)];
  ptr = arr;
  size = strlen(ptr);
}

MyArray::MyArray(const MyArray &obj)
{
  cout << "Copy constructor" << endl;

  size = obj.size;
  ptr = new char[size];
  *ptr = *obj.ptr;
}

MyArray::~MyArray()
{
  delete [] ptr;
}

int MyArray::getSize()
{
  return size;
}

const MyArray MyArray::operator=(const MyArray &obj)
{
  if(size > 0)
    delete [] ptr;
  size = obj.size;
  ptr = new char[size];
  for(int i=0; i<size; i++)
  {
    ptri] = obj.ptr[i];
  }
  return *this;

}

bool MyArray::operator==(const MyArray &obj) const
{
  if(size != obj.size)
    return false;
  for(int i=0; i<size; i++)
  {
    if(ptr[i] = obj.ptr[i])
      return false;
  }
  return true;
}

bool MyArray::operator!=(const MyArray &obj) const
{
  return !(*this == obj);
}

char& MyArray::operator[](int obj)
{
  assert(0 <= obj && obj < size);
  return ptr[obj];
}
