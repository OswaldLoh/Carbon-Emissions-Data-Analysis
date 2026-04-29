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

    
    Residents arrayA[FILE_A_SIZE];
    Residents arrayB[FILE_B_SIZE];
    Residents arrayC[FILE_C_SIZE];

    linkedList ListA, ListB, ListC;

    char runAgain = 'y';
    do {
        valid = false;

        // --- Reinitialize data structures from CSV each iteration ---
        loadCSVArray(FILE_A_PATH, arrayA);
        loadCSVArray(FILE_B_PATH, arrayB);
        loadCSVArray(FILE_C_PATH, arrayC);

        ListA.clear();
        ListB.clear();
        ListC.clear();
        loadCSVList(FILE_A_PATH, ListA);
        loadCSVList(FILE_B_PATH, ListB);
        loadCSVList(FILE_C_PATH, ListC);

        // Rebuild city container with fresh data
        Container cities[] = {
            {"A", ListA, arrayA, FILE_A_SIZE},
            {"B", ListB, arrayB, FILE_B_SIZE},
            {"C", ListC, arrayC, FILE_C_SIZE}
        };
        // ------------------------------------------------------------

        cout << "\n==============================" << endl;
        cout << "  Choose operation:" << endl;
        cout << "  1. Categorization" << endl;
        cout << "  2. Carbon Analysis" << endl;
        cout << "  3. Sorting" << endl;
        cout << "  4. Searching" << endl;
        cout << "==============================" << endl;

        while (!valid) {
            cout << ">>>   ";
            cin >> decision;
            if (cin.fail() || decision > 5 || decision < 1) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid option. Please try again." << endl;
            } else {
                valid = true;
            }
        }

        switch (decision) {
            case 1: {
                Container selectedCity = citySelection(cities, 4);
                string structure = structureSelect();

                if (structure == "Array") {
                    // Access the pointer and size directly from the struct
                    categorizeArray(selectedCity.array, selectedCity.size);
                } else {
                    // Map the struct name back to the correct Linked List
                    categorizeList(selectedCity.list);
                    // !! Simplified the code after adding list into the main container !!
                }
                break;
            }
            case 2: {           // Carbon Analysis
                carbonAnalysis(cities, 3);
                break;
            }
            case 3: {           // Sorting Algorithms
                Container city = citySelection(cities, 4);
                string category = sortBy();
                string structure = structureSelect();
                string algo = algoSelect();
                string state = stateSelect();
                sorting(structure, algo, city, category, state);
                break;
            }
            case 4: {
                Container city = citySelection(cities, 4);
                string state = stateSelect();
                searchMenu(city, state);
                break;
            }
            case 5: {           // [DEV] Benchmark
                runBenchmark();
                break;
            }
        }

        // Ask user if they want to run another operation
        cout << "--------------------------------------------------------" << endl;
        cout << "Do you want to perform another operation? (y/n): ";
        cin >> runAgain;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (runAgain == 'y' || runAgain == 'Y');


    cout << "\nExiting program. Goodbye!" << endl;
    return 0;
}


