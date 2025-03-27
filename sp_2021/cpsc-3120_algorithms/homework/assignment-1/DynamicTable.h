
#ifndef UNTITLED_DYNAMICTABLE_H
#define UNTITLED_DYNAMICTABLE_H

#include <stdlib.h>

class DynamicTable {


public:
    DynamicTable(){
        size = 1;
        table = new int[size];
        for (int i = 0; i < size; i++) {
            table[i] = 0;
        }
        last = 0;
    }

    ~DynamicTable(){
        delete [] table;
        table = NULL;
    }

    void insert(int value, bool dummy_version); 


private:

    void resize_dummy();
    void resize();

    int* table; //array containing the"list" of elements
    int size; //the size of the array
    int last; //the position of the last element

};


#endif //UNTITLED_DYNAMICTABLE_H
