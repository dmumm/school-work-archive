/*
 *  CPSC 3120-001, Prof. Federico Iuricich 
 *  Spring 2023, Clemson University
 *  Dylan Mumm
 *
 */

#include "DynamicTable.h"


void DynamicTable::insert(int value, bool dummy_version) {

/*
    std::cout << "INSERTING VALUE " << value 
              << " AT TABLE["       << last+1
              << "] AFTER "         << table[last]
              << " AT TABLE["       << last
              << "]\n";
*/


    //add a new element in the table
    //use `dummy_version` to decide which version of resize you want to call

/*
    std::cout << "  Printing original table[] without modification:\n           ";
    for(int i = 0; i < size; i++) {
        std::cout << table[i] << ".";
    }
    std::cout << "\n";
*/

    // when dummy_version = true, calls dummy resize
    if(size <= last+1) {
        if(dummy_version == true) {
            //std::cout << "  Calling resize_dummy()\n"; // debug
            resize_dummy();
        } else {
           // std::cout << "  Calling resize()\n"; // debug
            resize();
        }
    } /*else {
        std::cout << "  Table not resized, as it is not full\n"; // debug
    } */


    table[last + 1] = value;
    last = last + 1;

/*
    std::cout << "  Printing current table[], including inserted value:\n           ";
    for(int i = 0; i < size; i++) {
        std::cout << table[i] << ".";
    }
    std::cout << "\n\n";
*/


}

void DynamicTable::resize_dummy() {
    n_resize_called++;
/*
    std::cout << "      RESIZING +1\n"; // debug

    std::cout << "      Printing source table[]:\n           "; // debug
    for(int i = 0; i < size; i++) {
        std::cout << table[i] << "."; // debug
    }
    std::cout << "\n"; // debug
*/

    int* temp_table = new int[size+1];

    for (int i = 0; i < size+1; i++){ // fills "empty" elements in new table for debug
      temp_table[i] = 420;
    }
/*
    std::cout << "      Printing new temp_table[]:\n           ";
    for(int i = 0; i < size+1; i++) {
        std::cout << temp_table[i] << "."; // debug
    }
    std::cout << "\n"; // debug
*/
    for(int i = 0; i < size; i++) {
        temp_table[i] = table[i];
    }

/*
    std::cout << "      Printing temp_table[] after copying source table:\n           ";
    for(int i = 0; i < size+1; i++) {
        std::cout << temp_table[i] << ".";
    }
    std::cout << "\n";
*/
    delete[] table;
    table = temp_table;
    size = size + 1;
/*
    std::cout << "      Printing new table[]:\n           ";
    for(int i = 0; i < size; i++) {
        std::cout << table[i] << ".";
    }
    std::cout << "\n";
*/    
}

void DynamicTable::resize() {
    n_resize_called++;
/*
    std::cout << "      RESIZING x2\n";

    std::cout << "      Printing source table[]:\n           ";
    for(int i = 0; i < size; i++) {
        std::cout << table[i] << ".";
    }
    std::cout << "\n";
*/
    int* temp_table = new int[size*2];

    for (int i = 0; i < size*2; i++){ // PLACEHOLDER UNDECLARED INTS FOR DEBUG
      temp_table[i] = 420;
    }
/*
    std::cout << "      Printing new temp_table[]:\n           ";
    for(int i = 0; i < size*2; i++) {
        std::cout << temp_table[i] << ".";
    }
    std::cout << "\n";
*/
    for(int i = 0; i < size; i++) {
        temp_table[i] = table[i];
    }

/*
    std::cout << "      Printing temp_table[] after copying source table:\n           ";
    for(int i = 0; i < size*2; i++) {
        std::cout << temp_table[i] << ".";
    }
    std::cout << "\n";
*/
    delete[] table;
    table = temp_table;
    size = size*2;
/*
    std::cout << "      Printing new table[]:\n           ";
    for(int i = 0; i < size; i++) {
        std::cout << table[i] << ".";
    }
    std::cout << "\n";
*/

}