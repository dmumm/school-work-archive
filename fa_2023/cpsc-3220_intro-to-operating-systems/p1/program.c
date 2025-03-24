#include <stdlib.h>
#include <stdio.h>

int main() {
    int rows = 10;
    int cols = 10;
   int memCount = 0; 
    // Allocate memory for the array of pointers
    int** matrix = (int**)malloc(rows * sizeof(int*));
memCount = memCount + (rows * sizeof(int*));
    // Allocate memory for each row
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
	memCount = memCount + (cols * sizeof(int));
    }
    // Forget to free it, causing a memory leak
    fprintf(stderr,"hi %d", memCount);
    return 0;
}
