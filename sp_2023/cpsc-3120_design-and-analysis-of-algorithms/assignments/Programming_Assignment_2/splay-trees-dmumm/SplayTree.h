/*
 * Clemson_University/Sp2023/CPSC_3120_001_Iuricich/Prog_Assignments/2_Splay_Trees/SplayTree.h
 *
 * Description:
 *    - Implementation of splay tree
 *    - Done in header to satisfy assignment requirements
 *
 * History:
 *    - Skeleton code given by class
 *    - Dylan Mumm starts 2023-Feb-06
 *
 */

#include "BinaryTree.h"

// class implementing the Splay tree
class SplayTree : public BinaryTree
{

    // extending the Binary you raughly have everything you need

public:

    void insertValue(int);       // a new function for inserting a node into the tree, performs plays
    bool search(int);           // a new function for searching a node into the tree, performs splays
    void splay(Node*);          // a new function for performing splay

    // splay helper functions
    void rotateRight(Node*);    
    void rotateLeft(Node*);

};

void SplayTree::insertValue(int query)
{
    Node* insertedNode = this->BinaryTree::insertValue(query);
    assert(insertedNode != NULL);
    this->splay(insertedNode);
}

bool SplayTree::search(int query)
{

    if (mpRoot == NULL) return false;

    Node* lastNode = this->find(query);
    assert(lastNode != NULL);

    this->splay(lastNode);

    if (lastNode->value() == query) return true;
    
    return false;
}

void SplayTree::splay(Node* target) {

    if (target == NULL) return;
    if (target->parent() == NULL) {
        mpRoot = target;
        return;
    }

    Node* parent = target->parent();
    Node* grandparent = parent->parent();

    // if target has no grandparent
    if (grandparent == NULL)
    {
        if (target == parent->leftChild()) 
            this->rotateRight(parent);

        else
            this->rotateLeft(parent);
    }

    // if target has a grandparent and both target and parent are left children
    else if (target == parent->leftChild() && parent == grandparent->leftChild()) {
        this->rotateRight(grandparent);
        this->rotateRight(parent);    
    }
    // if target has a grandparent and both target and parent are right children
    else if (target == parent->rightChild() && parent == grandparent->rightChild()) {
        this->rotateLeft(grandparent);
        this->rotateLeft(parent);      
    }
    // if target has grandparent but target left child and parent right child
    else if (target == parent->leftChild() && parent == grandparent->rightChild()){
        this->rotateRight(grandparent);
        this->rotateLeft(parent);
    }
    // if target has grandparent but target right child and parent left child
    else if (target == parent->rightChild() && parent == grandparent->leftChild()) {
        this->rotateLeft(grandparent);
        this->rotateRight(parent);
    }

    if (target->parent() == NULL){
        mpRoot = target; // point root pointer at target as it is now the new root
        return;
    }

    splay(target); // recurse until root reached


}

void SplayTree::rotateRight(Node* target) {

    Node* newParent = target->leftChild();

    if (newParent) { // check if newParent is not null
        target->setLeftChild(newParent->rightChild());
        if(newParent->rightChild())
            newParent->rightChild()->setParent(target);  
        newParent->setParent(target->parent());
    }

    else { // if newParent is null, set target's left child and parent to null
        target->setLeftChild(NULL);
        target->setParent(NULL);
    }

    if(target->parent() == NULL) {
        mpRoot = newParent;
        return;
    }
    else if (target == target->parent()->rightChild())
        target->parent()->setRightChild(newParent);
    else
        target->parent()->setLeftChild(newParent);

    newParent->setRightChild(target);
    target->setParent(newParent);
}

void SplayTree::rotateLeft(Node* target) {

    Node* newParent = target->rightChild();

    if (newParent) { // check if newParent is not null
        target->setRightChild(newParent->leftChild());
        if(newParent->leftChild())
            newParent->leftChild()->setParent(target);  
        newParent->setParent(target->parent());
    }

    else { // if newParent is null, set target's right child and parent to null
        target->setRightChild(NULL);
        target->setParent(NULL);
    }

    if(target->parent() == NULL) {
        mpRoot = newParent;
        return;
    }
    else if (target == target->parent()->leftChild())
        target->parent()->setLeftChild(newParent);
    else
        target->parent()->setRightChild(newParent);

    newParent->setLeftChild(target);
    target->setParent(newParent);

}