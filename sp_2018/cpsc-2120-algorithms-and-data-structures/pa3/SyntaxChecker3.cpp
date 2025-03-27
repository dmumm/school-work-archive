// primitive test - wdg 2015
#include "Position.h"
#include <iostream>
using namespace std;

int main()
{
	vector<int> first = { 1, 1, 1, 1, 1};
	Position A(first);
        cout << A << endl;
	cout << (A.isDone() ? "Done" : "not done") << endl;

        vector<int> second = { 1, 1, 1, 1, 0 };
        Position B(second);

        for(int i=1; i<=5; i++) {
            Position *after = A.afterMove(i);
            if( after!=nullptr ) {
	      cout << *after;
              cout << boolalpha << (B==(*after));
              cout << endl;
//              delete after;
            }
            else cout << "Invalid" << endl;
        }
        cout << endl;

        vector<int> third = {10, 8, 4, 0, 2 };
        Position C(third);
        for(int i=1; i<=5; i++) {
            Position *after = C.afterMove(i);
            if( after!=nullptr ) {
	       cout << *after << endl;
//               delete after;
            }
            else cout << "Invalid" << endl;
        }

        return 0;
    }

/****************************
OUTPUT
*****************************
[1.1.1.1.1]
not done
[0.2.1.1.1]false
[1.0.2.1.1]false
[1.1.0.2.1]false
[1.1.1.0.2]false
[1.1.1.1.0]true

[1.10.6.2.4]
[11.1.6.2.3]
[11.8.0.1.3]
Invalid
[11.8.4.0.0]
******************************/
