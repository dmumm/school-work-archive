#include <iostream>
#include "MyArray.h"
using namespace std;


int main()
{
    //testing the constructors
    MyArray a = "Hello ";
    MyArray b = a;
    MyArray c;
    MyArray e("world");

    cout << a << e << " " << b << c << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    //testing the = operator
    MyArray d;
    d = a;
    cout << d << a;
    cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    //testing  the == operator and != operator
    bool isEqual = a == d;
    cout << "This should be true (1)\n";
    cout << isEqual << endl;
    cout << endl;
    bool notEqual = a != d;
    cout << "This should be false (0)\n";
    cout << notEqual << endl;

    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    //testing getSize and << ostream operator
    cout << "The size of a is " << a.getSize() << " and its value is " << d << endl;

    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    //testing all + operators
    MyArray f = a + e;
    cout << f << endl;

    MyArray g = f + '!';
    cout << g << endl;

    char t = '!';
    cout << t << endl;
    MyArray h = t + g;
    cout << h << endl;

    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    //testing the istream operator
    MyArray i;
    cin >> i;
    cout << i;
    cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    //testing the []operator;

    MyArray m = "This is the final Programming assignment." ;

    cout << m[50];
    return 0;

}
