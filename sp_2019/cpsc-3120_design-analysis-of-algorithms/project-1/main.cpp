#include "Timer.h"
#include <stdlib.h>
#include <iostream>

#include <list>
#include <random>

using namespace std;

class Node {

  //- pointer to the parent node
  Node* parent;

  //- pointer to left child
  Node* left;

  //- pointer to right child
  Node* right;

  //- int for storing the key value
  int   value;

public:

  //constructor
  Node();

  // setters
  void setParent(Node* p);
  void setRight(Node* r);
  void setLeft(Node* l);
  void setValue(int v);

  // getters
  Node* getParent();
  Node* getRight();
  Node* getLeft();
  int   getValue();

};

class BinaryTree{

protected:
  //A tree should store (or at least furnish as accessible) only its root.
  Node* root;

public:
  //- constructor
  BinaryTree();

  //- getter setter root
  Node* getRoot();

  //- a function for printing the inorder visit of the tree
  void inorder(Node* node);

  //- a function for inserting a new value in the tree
  Node* insert(int val, Node* node);

  //- a function for searching a value in the tree->
  Node* search(int val);
  Node* search(int val, Node* node);


};

Node::Node() {
  parent = NULL;
  right  = NULL;
  left   = NULL;
  value  = 0;
}

void Node::setParent(Node* p) {
  this->parent = p;
}

void Node::setRight(Node* r) {
  this->right = r;
}

void Node::setLeft(Node* l) {
  this->left = l;
}

void Node::setValue(int v) {
  this->value = v;
}

Node* Node::getParent() {
  return parent;
}

Node* Node::getRight() {
  return right;
}

Node* Node::getLeft() {
  return left;
}

int Node::getValue() {
  return value;
}

BinaryTree::BinaryTree() {
  root = NULL;
}

Node* BinaryTree::getRoot() {
  return root;
}

void BinaryTree::inorder(Node* n) {
  if (n == NULL)
    return;

  inorder(n->getLeft());
  cout << n->getValue() << " ";
  inorder(n->getRight());

}

Node* BinaryTree::insert(int v, Node* n) {
  if(n == NULL) {
    Node* temp = new Node;
    temp->setValue(v);
    root = temp;
    return n;
  }
	else if(v < n->getValue()) {
		if(n->getLeft() != NULL) {
			insert(v, n->getLeft());
		}
    else {
			Node* temp = new Node;
			temp->setValue(v);
      temp->setParent(n);
      n->setLeft(temp);
      return n;
		}
  }
  else if(v >= n->getValue()) {
	   if(n->getRight() != NULL) {
			insert(v, n->getRight());
		 }
     else {
       Node* temp = new Node;
 			 temp->setValue(v);
       temp->setParent(n);
       n->setRight(temp);
       return n;
		}
	}
}

Node* BinaryTree::search(int val) {
  return search(val, root);
}

Node* BinaryTree::search(int val, Node* n) {
  if(n != NULL) {
    if(val == n->getValue()) {
      return n;
    }
    else if(val < n->getValue()) {
      return search(val, n->getLeft());
    }
    else {
      return search(val, n->getRight());
    }
  }
  else {
    return NULL;
  }
}


int main(int argc, char* argv[]){

  list<float> results_binary; //time for binary

  //for an increasing set of integers
  int tot=10000000;
  for(int numbers=1; numbers<tot; numbers*=2){
    int min=0;
    int max=20;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(min,max);

    list<int> values;
    for (int i=0; i<numbers; ++i) {
      double number = distribution(generator);
      values.push_back(int(number));
    }

    //build up a binary tree
    Timer time;
    time.start();

    BinaryTree *tree = new BinaryTree();

    for(auto i : values){
        tree->insert(i, tree->getRoot());
    }
    time.stop();
    cout << "Time for building " << time.getElapsedTimeInSec() << endl;

    //search numbers in binary tree
    time.start();
    for(auto i : values){
      tree->search(i);
    }
    time.stop();
    results_binary.push_back(time.getElapsedTimeInSec());
    cout << "Time for searches " << time.getElapsedTimeInSec() << endl;


  //save timings
  FILE* file = fopen("results_binary.txt", "w");
  for(auto val : results_binary)
    fprintf(file, "%f ", val);
  fclose(file);
}
}
