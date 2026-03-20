#include <iostream>
#include "residents.h"

// To run the code, enter in terminal:
// cd  Array
// g++ *.cpp -o run   
// ./run.exe

using namespace std;

int main() {
    Residents arrayA[FILE_A_SIZE];       // Initialize array of structs
    Residents arrayB[FILE_B_SIZE];
    Residents arrayC[FILE_C_SIZE];

    loadCSVArray(FILE_A_PATH, arrayA);        // Loading lines from CSV into arrays
    loadCSVArray(FILE_B_PATH, arrayB);
    loadCSVArray(FILE_C_PATH, arrayC);

    linkedList ListA;
    linkedList ListB;
    linkedList ListC;

    loadCSVList(FILE_A_PATH,ListA);
    loadCSVList(FILE_B_PATH,ListB);
    loadCSVList(FILE_C_PATH,ListC);
    return 0;
}