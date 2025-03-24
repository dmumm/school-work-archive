/**
 * List-based implementation for the union find algorithm.
 * 
 * Author: Guoxi Liu
 * Clemson University
 * Date: 01/31/2023
*/
#include <cassert>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

class UnionFind
{
    // Declare the existence of two classes to avoid reference cycle 
    struct Element;
    struct Header;

    // Define helper classes: Header and Element
    struct Header {
        std::string name;
        std::list<Element*> element_list;
    };

    struct Element {
        int value;
        Header* header_ptr;
        Element() {}
        Element(int val) : value(val) {}
    };

private:
    std::list<Header*> headers;     // keep track of headers 
    std::unordered_map<int, Element*> mp;    // map the integer value to the Element struct

public:
    UnionFind() {}
    // Destructor needs to remove all the header pointers
    ~UnionFind() {
        for(auto &h : headers) delete h;
    }
    
    void MakeSet(int val) {
        Header *h = new Header();
        Element *ele = new Element(val);
        h->name = std::to_string(val);
        h->element_list.push_back(ele);
        ele->header_ptr = h;
        mp[val] = ele;
        headers.push_back(h);
    }

    Header* Find(int x) {
        assert(mp.count(x) > 0);
        return mp[x]->header_ptr;
    }

    void Union(int x, int y) {
        Header *set_x = Find(x);
        Header *set_y = Find(y);
        if (set_x != set_y) {
            // make sure that set_x is always the one with more elements 
            if (set_x->element_list.size() < set_y->element_list.size())
                std::swap(set_x, set_y);
            // merge set_y to set_x 
            for (auto &yi : set_y->element_list) {
                yi->header_ptr = set_x;
                set_x->element_list.push_back(yi);
            }
            
            // we will have a dangling pointer of set_y, but we will delete it in destructor 
            set_y->element_list.clear();
        }
        else {
            std::cout << "set of " << x << " is equal to set of " << y << std::endl;
        }
    }

    void Print() {
        for (auto &h : headers) {
            if (!h->element_list.empty()) {
                std::cout << h->name << ":[ ";
                for (auto &e : h->element_list) {
                    std::cout << e->value << " ";
                }
                std::cout << "]" << std::endl;
            }
        }
    }
};


/**
 * Main entry. 
*/
int main()
{
    UnionFind uf;
    // In-class exercise example. 
    for (int i = 1; i <= 16; i++) uf.MakeSet(i);
    std::cout << "---------- After first for-loop ----------" << std::endl;
    uf.Print();

    for (int i = 1; i < 16; i+=2) uf.Union(i, i+1);
    std::cout << "---------- After second for-loop ----------" << std::endl;
    uf.Print();

    for (int i = 1; i < 14; i+=4) uf.Union(i, i+2);
    std::cout << "---------- After third for-loop ----------" << std::endl;
    uf.Print();

    uf.Union(1, 5);
    std::cout << "---------- After fourth operation ----------" << std::endl;
    uf.Print();

    uf.Union(11, 13);
    std::cout << "---------- After fifth operation ----------" << std::endl;
    uf.Print();
    
    uf.Union(1, 10);
    std::cout << "---------- After sixth operation ----------" << std::endl;
    uf.Print();

    std::cout << "Find(2): " << uf.Find(2) << std::endl;
    std::cout << "Find(9): " << uf.Find(9) << std::endl;
    
    return 0;
}
