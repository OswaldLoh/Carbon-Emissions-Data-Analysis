#include <iostream>
#include "../residentsArray.h"

// To run the code, enter in terminal:
// cd  Array
// g++ *.cpp -o run   
// ./run.exe

using namespace std;

int main() {
    Residents arrayA[FILE_A_SIZE];       // Initialize array of structs
    Residents arrayB[FILE_B_SIZE];
    Residents arrayC[FILE_C_SIZE];

    loadCSV(FILE_A_PATH, arrayA);        // Loading lines from CSV into arrays
    loadCSV(FILE_B_PATH, arrayB);
    loadCSV(FILE_C_PATH, arrayC);

    return 0;
}