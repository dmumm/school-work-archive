/*
 *  CPSC 3120-001, Prof. Federico Iuricich 
 *  Spring 2023, Clemson University
 *  Dylan Mumm
 *
 */


#ifndef UNTITLED_DYNAMICTABLE_H
#define UNTITLED_DYNAMICTABLE_H

#include <stdlib.h>
//#include <iostream> // DEBUG, COMMENT OUT AFTER
//#include <cstring> // debug
//#include <cstdio> // debug
//#include <array> // DEBUG
//#include <fstream> // debug

class DynamicTable {


public:
    DynamicTable(){
        n_resize_called = 0; // ignore
        
        //implement the constructor
        //when created the table should have space for one element
        //variable `size` and `last` should be set accordingly

//        std::cout   << "Constructor called\n";

        // default object is size 1 with no last element
        size = 1;
        last = -1;

        table = new int[size];

        for (int i = 0; i < size; i++){ // fills default table with 666s for debug
          table[i] = 666;
        }

/*
        std::cout   << "Constructed new DynamicTable object of size " << size 
                    << " and its last element, " << table[last] 
                    << ", is in position [" << last << "].\n";
*/
    }

    ~DynamicTable(){

        //TODO: implement the destructor
        //when destroyed you should call explicitly the destructor for the array

        int *location;
        location = &table[0];

/*        // debug

        std::cout   << "Destructor called\n";
        std::cout   << "Element where table[0] is is " << *location << "\n";
        std::cout   << "Element where table[last] is is " << *location << "\n";
*/
        // explicitly calling destructor for the array

        delete[] table;

 /*       // debug

        std::cout   << "Element where table[0] used to be is " << *location << "\n";
        std::cout   << "Element where table[last] used to be is " << *location << "\n";

*/
    }

    inline int get_n_resize(){return n_resize_called;}

    void insert(int value, bool dummy_version); //TODO: implement the insert function


private:

    void resize_dummy(); // an inefficient resize function that will expand the array adding only 1 empty spot every time the array is full.
    void resize(); //ma resize function that doubles the size of the array every time it is full.

    int* table; //array containing the"list" of elements
    int size; //the size of the array
    int last; //the position of the last element

    int n_resize_called; //you can ignore this value. It is used for debug purposes

};


#endif //UNTITLED_DYNAMICTABLE_H
