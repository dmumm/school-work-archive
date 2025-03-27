#include "PropaTree.h"
#include <iostream>
using namespace std;



PropaTree::PropaTree() : root(nullptr), nextNodeName('A') {}

void PropaTree::addAtLeaf(int number) {
  count = 0;
  if(letter == 'A') {
    letter = 'B';
    root = new Node('A');
  }
  addAtLeaf(root,  number);
}


void PropaTree::addAtLeaf(Node* curr, int number) {

  if(root->left == nullptr) {
    root->left = new Node(letter++);
    root->right = new Node(letter++);
  }

  else if (curr->left == nullptr) {
    count++;
    if (count == number) {
      curr->left = new Node(letter++);
      curr->right = new Node(letter++);
    }
  }

  else if (curr != nullptr) {
    addAtLeaf(curr->left, number);
    addAtLeaf(curr->right, number);
  }
}



void PropaTree::dump() {
  preorderPrint(root, 0);

}

void PropaTree::preorderPrint(Node* curr, int depth) {
  if(curr == nullptr) {
    return;
  }

  for(int i = 0; i < depth; i++) {
    cout << "...";
  }
  depth++;
  cout << curr->name << endl;
  preorderPrint(curr->left, depth);
  preorderPrint(curr->right, depth);

}

int PropaTree::getImbalance() {

  if(root == nullptr)
    return 0;
  else if(getHalf(root->left) > getHalf(root->right))
    return getHalf(root->left) - getHalf(root->right);
  else
    return getHalf(root->right) - getHalf(root->left);
}

int PropaTree::getHalf(Node* curr) {
  if (curr == nullptr) 
    return 0;
  if(curr->left == nullptr && curr->right == nullptr)
    return 1;
  else
    return getHalf(curr->left) + getHalf(curr->right);


}
