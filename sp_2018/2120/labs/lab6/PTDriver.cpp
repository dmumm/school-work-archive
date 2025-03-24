// final PTDriver for propa-tree lab
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;
#include "PropaTree.h"

int main(int argc, char *argv[])
{
  int LEAVES = atoi(argv[1]);
  double count = 0;
  srand(time(NULL));
  for(int i = 0; i < 10; i++) {
    PropaTree T;
    for(int i = 0; i < LEAVES; i++) {
      T.addAtLeaf(rand() % (i+1) + 1);
    }

    count += T.getImbalance();
    cout << T.getImbalance() << " ";
  }

  cout << endl << "Average: " << count / 10.0 << endl;

}
