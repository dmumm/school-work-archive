#ifndef RNODE_H
#define RNODE_H

#include <iostream>
using namespace std;

struct RNode
{
    int start, end;
    RNode* next;
    RNode* prev;


    // default constructor creates dummy node
    RNode() : next(nullptr), prev(nullptr) {}

    // regular constructor creates data node
    RNode(int s, int e) : start(s), end(e), next(nullptr), prev(nullptr) {}

};

ostream& operator<< (ostream & out, const RNode & rn);

#endif
