/*
 * Clemson_University/Sp2023/CPSC_3120_001_Iuricich/Prog_Assignments/2_Splay_Trees/main.cpp
 * 
 * Description:
 *    - Tests included binary search tree and splay tree implementations
 * 
 * History:
 *    - Skeleton code given by class
 *    - Dylan Mumm starts 2023-Feb-03
 * 
 *    
 */

#include "SplayTree.h"

#include <list>
#include <random>

#include "Timer.h"

using namespace std;

int main(int argc, char* argv[]){

  int  values[]  = { 48270, 22497, 73541, 20860, 47696, 59586, 92798, 19746, 56174, 32938, 60977, 33166, 94947, 54624, 48515, 95830, 96696, 99411, 86073, 34675, 97170, 42522, 54404, 70355, 98970, 701, 94519, 47916, 194, 4256, 18357, 2090, 38160, 24527, 41478, 14242, 54671, 77724, 69339, 94216, 16603, 85762, 95622, 1443, 31618, 67805, 92368, 75686, 19966, 70803, 99484, 28177, 52310, 10624, 15963, 27755, 16227, 78077, 86798, 59516, 34, 25743, 13806, 44219, 83926, 72321, 97035, 68232, 52465, 20385, 59841, 97071, 29049, 73848, 12950, 94485, 25951, 59170, 59426, 97298, 21340, 3683, 98787, 91662, 92192, 11512, 9484, 25890, 40526, 34767, 69422, 8020, 28695, 27498, 70169, 15441, 2699, 63790, 17139, 57463};

  Timer time;
  time.start();

  SplayTree* splayTestTree = new SplayTree(); // constructor for splay tree
  for(auto i : values){
      splayTestTree->insertValue(i); // call insert on splay tree
  }
  time.stop();
  splayTestTree->printInorderFromRoot();

  //search numbers in binary tree
  time.start();
  for(auto i : values){
      splayTestTree->search(i);
  }
  time.stop();

  splayTestTree->printInorderFromRoot();
}
