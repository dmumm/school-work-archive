#include "PropaTree.h"
using namespace std;


PropaTree::PropaTree() : root(nullptr), nextNodeName('A') {}

void PropaTree::addAtLeaf(int number) {
  int count = 0;
  addAtLeaf(new Node(letter++),  number,  count);

}


void PropaTree::addAtLeaf(Node* curr, int number, int count) {
  if(count == 'A') {
    count = 'B';
    root = curr;
  }

  else if (curr->left == nullptr) {
    count++;
    if (count == number) {
      curr->left = new Node(letter++);
      curr->right = new Node(letter++);
    }
  }

  else if (curr != nullptr) {
    addAtLeaf(curr->left, number, count);
    addAtLeaf(curr->right, number, count);
  }
}

/*

void PropaTree::dump() {


}

*/
