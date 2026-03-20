#include <iostream>
#include "../residentsList.h"

using namespace std;

int main() {
    linkedList L1;
    linkedList L2;
    linkedList L3;

    loadCSV(FILE_A_PATH,L1);
    loadCSV(FILE_B_PATH,L2);
    loadCSV(FILE_C_PATH,L3);

    cout << "hello";
    Residents* current = L1.getHeadAddress();

    while (current != nullptr) { 
        cout << current->ID << endl;
        current = current->nextAddress; 
    }
}