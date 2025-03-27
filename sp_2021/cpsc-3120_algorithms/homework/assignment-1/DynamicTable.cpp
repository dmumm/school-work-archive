
#include "DynamicTable.h"

void DynamicTable::insert(int value, bool dummy_version) {

    if (size == last and dummy_version) {
    	resize_dummy();
    }
    if (size == last and not dummy_version) {
    	resize();
    }
    table[last+1] = value;

}

void DynamicTable::resize_dummy() {

    int * newTable = new int[size + 1];
    for(int i = 0; i < size; i++) {
    	newTable[i] = table[i];
    }

    delete [] table;
    table = newTable;
    size = size + 1;

}

void DynamicTable::resize() {

    int * newTable = new int[size * 2];
    for(int i = 0; i < size; i++) {
    	newTable[i] = table[i];
    }

    delete [] table;
    table = newTable;
    size = size * 2;

}