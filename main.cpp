#include <iostream>
#include "residents.h"

// To run the code, enter in terminal:
// cd  Array
// g++ *.cpp -o run   
// ./run.exe

using namespace std;


int structureSelect() {
    int structure;
    bool valid = false;
    cout << "Please choose data structure;" << endl;
    cout << "1. Array" << endl;
    cout << "2. Linked List" << endl;

    while (!valid) {
        cout << "Please enter a valid selection.";
        cout << ">>>   ";
        cin >> structure;
        }
    return structure;
}

int sortSelect(int structure) {
    int sortSelection;
    cout << "Please choose sorting method" << endl;
    cout << "1. Bubble Sort" << endl;
    cout << "2. Insert Sort" << endl;
    cout << "3. Merge Sort" << endl;
    cout << ">>>   ";
    cin >> sortSelection;
    
    return 0;
}
    
int main() {
    int decision;
    // Initialize Arrays
    Residents arrayA[FILE_A_SIZE];      
    Residents arrayB[FILE_B_SIZE];
    Residents arrayC[FILE_C_SIZE];
    loadCSVArray(FILE_A_PATH, arrayA);        // Loading lines from CSV into arrays
    loadCSVArray(FILE_B_PATH, arrayB);
    loadCSVArray(FILE_C_PATH, arrayC);

    // Initialize Linked Lists
    linkedList ListA, ListB, ListC;
    loadCSVList(FILE_A_PATH,ListA);
    loadCSVList(FILE_B_PATH,ListB);
    loadCSVList(FILE_C_PATH,ListC);

    cout << "Choose operation:" << endl;
    cout << "1. Sorting" << endl;
    cout << "2. Searching" << endl;
    cout << ">>>   ";
    cin >> decision;
    switch (decision) {
        case 3:             // Sorting Algorithms
            int structure = structureSelect();
            int sortAlgo = sortSelect(structure);
    }
    return 0;
}

