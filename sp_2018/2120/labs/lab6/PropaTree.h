// original by Goddard
// ADAPT AS DESIRED
#ifndef PROPA_TREE_H
#define PROPA_TREE_H

struct Node
{
  const char name;
  int leavesInSubtree;
  Node *left, *right;

  Node(char nam) : name(nam), leavesInSubtree(1),
     left(nullptr), right(nullptr)
  { }
};

class PropaTree
{
  public:
    PropaTree();
    void addAtLeaf(int number);
    void dump();
    int getImbalance( );  // for next lab
 private:
    char letter = 'A';
    int count = 0;


    Node* root;
    char nextNodeName;
    void addAtLeaf(Node* curr, int number);
    void preorderPrint(Node *curr, int depth);  // recursive
    int getHalf(Node* curr);

};

#endif
