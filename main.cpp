#include <iostream>
#include <limits>
#include "residents.h"

// To run the code, enter in terminal:
// g++ *.cpp -o run   
// ./run.exe

using namespace std;



int main() {
    int decision;
    bool valid = false;

    // Initialize Arrays
    Residents arrayA[FILE_A_SIZE];      
    Residents arrayB[FILE_B_SIZE];
    Residents arrayC[FILE_C_SIZE];

    Array arrays[] = {
        {"A",arrayA,FILE_A_SIZE},           // Array that contains all arrays
        {"B",arrayB,FILE_B_SIZE},
        {"C",arrayC,FILE_C_SIZE}
    };

    
    loadCSVArray(FILE_A_PATH, arrayA);        // Loading lines from CSV into arrays
    loadCSVArray(FILE_B_PATH, arrayB);
    loadCSVArray(FILE_C_PATH, arrayC);

    // Initialize Linked Lists
    linkedList ListA, ListB, ListC;
    loadCSVList(FILE_A_PATH,ListA);
    loadCSVList(FILE_B_PATH,ListB);
    loadCSVList(FILE_C_PATH,ListC);

    cout << "Choose operation:" << endl;
    cout << "1. Categorization" << endl;
    cout << "2. Carbon Analysis" << endl;
    cout << "3. Sorting" << endl;
    cout << "4. Searching" << endl;

    while (!valid) {
        cout << ">>>   ";
        cin >> decision;
        if (cin.fail() || decision > 4 || decision < 1) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid option. Please try again." << endl;
            } else {
                valid = true;
            }
        switch (decision) {
            case 1:             // Categorization
                cout << "In Progress" << endl;
                break;
            case 2:             // Carbon Analysis
                cout << "In Progress" << endl;
                break;
            case 3: {           // Sorting Algorithms
                Array city = citySelection(arrays,3);
                string category = sortBy();
                string structure = structureSelect();
                string algo = sortSelect();
                sorting(structure,algo,city,category);
                break;
                }
            case 4:
                cout << "In progress" << endl;
                break;
            }
    }
    return 0;
}

