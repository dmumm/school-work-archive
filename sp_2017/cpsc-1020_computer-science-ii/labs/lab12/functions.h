#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <cstdlib>

void printArray(int array[], int array_size );
void quickSort(int array[], int start, int end);
int partition(int array[], int start, int end);
int binarySearch(const int array[], int first, int last, int value);


#endif
