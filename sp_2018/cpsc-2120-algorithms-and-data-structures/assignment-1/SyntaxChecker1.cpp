// SyntaxChecker for Caesar Asg - Goddard
#include <iostream>
using namespace std;
#include "MySentence.h"

int main( ) 
{
   string A = "aaa";
   string B = "bbb";
   string Z = "Zz9 aa. ";
   MySentence M(A), N(B);
   cout << M << endl;
   cout << boolalpha << (M==N) << endl;
   M.rotate( );
   cout << M << endl;
   cout << boolalpha << (M==N) << endl; // should be true
   MySentence Q(Z);
   Q.rotate( );
   cout << Q << endl;
   Q.reverse( );
   cout << Q << endl;
   return 0;
}
