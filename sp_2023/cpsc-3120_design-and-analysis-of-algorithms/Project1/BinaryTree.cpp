#include <stdlib.h>
#include <iostream>

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





int main(){

	BinaryTree *tree = new BinaryTree();

	tree->insert(10, tree->getRoot());
	tree->insert(6, tree->getRoot());
	tree->insert(14, tree->getRoot());
	tree->insert(5, tree->getRoot());
	tree->insert(8, tree->getRoot());
	tree->insert(11, tree->getRoot());
	tree->insert(18, tree->getRoot());
  tree->search(11);
  tree->search(34);



	tree->inorder(tree->getRoot());

}
