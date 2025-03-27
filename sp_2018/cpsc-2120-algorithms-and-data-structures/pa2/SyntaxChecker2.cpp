// SyntaxChecker for rangeset asg - wdg
#include <iostream>
using namespace std;
#include "RangeSet.h"

int main( )
{
      RangeSet S,T;
//      S.addLonelyRange(1,1);
//      S.addLonelyRange(22,33);
//      S.addLonelyRange(77,78);
      S.addLonelyRange(1,100);
      S.deleteValue(14);

      S.dump( );

      cout << boolalpha << S.isInSet(10) << ":" << S.isInSet(30) << ":" << S.isInSet(1) << endl;

      T.dump( );  // should print "Empty"
      cout << boolalpha << (S==T) << endl;  // should be false


  /*    T.addRange(22,33);
      T.addRange(77,95);
      T.addRange(55,55);
      T.dump(); */
      T.addRange(25, 90);
      T.dump();
      T.addRange(20, 100);
      T.dump();
      T.addRange(90, 110);
      T.dump();

      return 0;

}
