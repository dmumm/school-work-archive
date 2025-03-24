/*
 * Clemson_University/Sp2023/CPSC_3120_001_Iuricich/Prog_Assignments/2_Splay_Trees/BinaryTree.h
 * 
 * Description:
 *    - Implementation of simple binary search tree
 *    - Done in header to satisfy assignment requirements
 *    - Methods implemented as they are to satisfy assignment requirements
 * 
 * History:
 *    - Skeleton code given by class
 *    - Dylan Mumm starts 2023-Feb-03
 *    - Initial implementation done 2023-Feb-06, 3pm EST
 *    
 */

#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#endif // BINARYTREE_H_

#include <stdlib.h>
#include <assert.h>

#include <iostream>

using namespace std;

class Node {

  //Each node should have
  //- pointer to the parent node
  //- pointer to left child
  //- pointer to right child
  //- int for storing the key value

  Node* mpParent;
  Node* mpLeftChild;
  Node* mpRightChild;
  int   mValue;

public:

  //constructor
  //remember to always inizialize pointers to NULL

  Node();

  //getter and setter for nodes and value

  Node* parent();
  Node* leftChild();
  Node* rightChild();
  int   value();

  void  setParent(Node*);
  void  setLeftChild(Node*);
  void  setRightChild(Node*);
  void  setValue(int);

};

class BinaryTree {

protected:
  //A tree should store only its root.
  Node* mpRoot;

public:
  //functions required

  //- constructor

  BinaryTree();

  //- getter setter root

  Node* root();

  void  setRoot(Node*);

  //- a function for printing the inorder visit of the tree

  void  printInorderFromRoot();
  void  printInorderFrom(Node*);

  //- a function for inserting a new value in the tree

  Node* insertValue(int);

  //- functions for searching a value in the tree.
  //--- returns true if tree contains parameter integer
  bool  search(int);

  //- - returns first node it finds with parameter integer or parent of where integer would be
  Node* find(int);

};

// ---------------------------------------------------------------------------
// -- NODE FUNCTION DEFINITIONS

Node::Node() {

  mpParent = NULL;
  mpLeftChild = NULL;
  mpRightChild = NULL;
  mValue = -1; 

}

// getters for node class

Node* Node::parent() {
  if(mpParent != NULL)
    return mpParent;
  else 
    return NULL;
}

Node* Node::leftChild() {
  if(mpLeftChild != NULL)
    return mpLeftChild;
  else 
    return NULL;
}

Node* Node::rightChild() {
  if(mpRightChild != NULL)
    return mpRightChild;
  else 
    return NULL;
}

int Node::value() {
  return mValue;
}

// setters for node class

void Node::setParent(Node* candidateParent) {
  this->mpParent = candidateParent;
  assert(mpParent == candidateParent);
}

void Node::setLeftChild(Node* candidateChild) {
  this->mpLeftChild = candidateChild;
  assert(mpLeftChild == candidateChild);
}

void Node::setRightChild(Node* candidateChild) {
  this->mpRightChild = candidateChild;
  assert(mpRightChild == candidateChild);

}

void Node::setValue(int candidateValue) {
  this->mValue = candidateValue;
  assert(mValue == candidateValue);
}

// ---------------------------------------------------------------------------
// -- BINARY TREE FUNCTION DEFINITIONS

BinaryTree::BinaryTree() {
  mpRoot = NULL;
}

// root accessors 

Node* BinaryTree::root() {
  return mpRoot;
}

void  BinaryTree::setRoot(Node* candidateRoot) {
  mpRoot = candidateRoot;
}

// Param: None
// Returns: Nothing, but cout gets all tree's values printed in order
// Assumptions: Tree sorted via value, left to right ascending, no duplicates
void  BinaryTree::printInorderFromRoot() {

  printInorderFrom(mpRoot);

}

// Param: Root of sub-tree wanting printed inorder
// Returns: Nothing, but cout gets all subtree's values printed in order
// Assumptions: Tree sorted via value, left to right ascending, no duplicates
void  BinaryTree::printInorderFrom(Node* crawler) {

  if(crawler == NULL)
    return;

  printInorderFrom(crawler->leftChild());
  cout << crawler->value() << " ";
  printInorderFrom(crawler->rightChild());

}

// Param: Integer to add to new node and be inserted
// Returns: Nothing
// Assumptions: Tree sorted via value, left to right ascending, no duplicates
// Might need destructor for node?
Node* BinaryTree::insertValue(int candidateValue) {

  Node* newNode = new Node();
  newNode->setValue(candidateValue);

  if(mpRoot == NULL) {
    mpRoot = newNode;
    return mpRoot; 
  }
  
  Node* candidate = find(candidateValue);
  if (candidate->value() == candidateValue)
    return candidate; // No insertion, value already there

  newNode->setParent(candidate);

  if (candidate->value() > newNode->value())
    candidate->setLeftChild(newNode);
  else
    candidate->setRightChild(newNode);
  
  return newNode;

}

// Param: Integer to query
// Returns: Whether query is in tree
// Assumptions: Tree sorted via value, left to right ascending
bool  BinaryTree::search(int query) {

  if (mpRoot == NULL)
    return false;

  if (this->find(query)->value() == query)
    return true;
  else 
    return false;

}

// Param: Integer to query
// Returns: Node address with query, if query not found, parent where node would be child of, or null if root null
// Assumptions: Tree sorted via value, left to right ascending
Node* BinaryTree::find(int query) {

  Node* crawler        = mpRoot;
  Node* crawlerParent  = NULL;

  while(crawler != NULL) {
    crawlerParent = crawler;
    if (crawler->value() == query)
      return crawler;
    else if (crawler->value() > query) 
      crawler = crawler->leftChild();
    else // crawler->value() < query
      crawler = crawler->rightChild();
  }
  return crawlerParent;

}