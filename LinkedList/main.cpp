#include <iostream>
#include "../residentsList.h"

// To run the code, enter in terminal:
// cd  LinkedList
// g++ *.cpp -o run   
// ./run.exe

using namespace std;

int main() {
    linkedList ListA;
    linkedList ListB;
    linkedList ListC;

    loadCSV(FILE_A_PATH,ListA);
    loadCSV(FILE_B_PATH,ListB);
    loadCSV(FILE_C_PATH,ListC);

    cout << "hello";
    Residents* current = ListA.getHeadAddress();

    while (current != nullptr) { 
        cout << current->ID << endl;
        current = current->nextAddress; 
    }
}