// goddard - 2018
#include <iostream>
using namespace std;
#include "PosPoly.h"

int main( )
{
  PosPoly A, B;
  int cof, pow;
  bool isDone=false;
  cout << "Enter first " << endl;
  while( !isDone )
  {
    cout << "Enter pair (0,0 to finish) ";
    cin >> cof >> pow;
    isDone = (cof==0 && pow==0);
    if( !isDone )
       A.incrementBy( cof, pow );
  }

  isDone=false;
  cout << "Enter second " << endl;
  while( !isDone )
  {
    cout << "Enter pair (0,0 to finish) ";
    cin >> cof >> pow;
    isDone = (cof==0 && pow==0);
    if( !isDone )
     B.incrementBy( cof, pow );
  }

  cout << endl;
  cout << "A is " << A << endl;
  cout << "B is " << B << endl;
  cout << (A==B ? "Equal" : "Not equal" ) << endl;

  return 0;

}
