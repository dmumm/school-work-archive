#include <iostream>
using namespace std;

struct Pair {
  int power;
  int coeff;
};

class PosPoly {
  public:

    PosPoly();

    void incrementBy(int, int);
    bool operator==(const PosPoly&) const;
    friend ostream& operator<<(ostream&, const PosPoly&);

  private:

    int powerCount;
    Pair* pairs;


};
