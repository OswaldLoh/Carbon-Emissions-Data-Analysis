#include <iostream>
#include <limits>
#include <iomanip>
#include "residents.h"
#include <string>
#include <functional>
#include <chrono>

using namespace std;

Container citySelection(Container* cities, int size) {    
    int selection;
    bool valid = false;
    cout << "\nCity Selection:" << endl;
    cout << "1. City A" << endl;
    cout << "2. City B" << endl;
    cout << "3. City C" << endl;
    while (!valid) {
        cout << ">>>   ";
        cin >> selection;
        if (cin.fail() || selection > 4 || selection < 1) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please try again." << endl;
        } else {
            valid = true;
        }
    }
    switch (selection) {
        case 1:
            return cities[0];
        case 2:
            return cities[1];
        case 3:
            return cities[2];
    }
    return cities[0];
}

string sortBy() {
    int selection;
    string category;
    bool valid = false;
    cout << "\nSort by:" << endl;
    cout << "1. Age" << endl;
    cout << "2. Daily Distance" << endl;
    cout << "3. Carbon Emission" << endl;
    while (!valid) {
        cout << ">>>   ";
        cin >> selection;
        if (cin.fail() || selection > 3 || selection < 1) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            valid = true;
        }
    }
    switch (selection) {
        case 1:
            category = "Age";
            break;
        case 2:
            category = "Distance";
            break;
        case 3:
            category = "Carbon";
            break;
    }
    return category;
}

string structureSelect() {
    int selection;
    string structure;
    bool valid = false;
    cout << "\nPlease choose data structure" << endl;
    cout << "1. Array" << endl;
    cout << "2. Linked List" << endl;
    while (!valid) {
        cout << ">>>   ";
        cin >> selection;
        if (cin.fail() || selection > 2 || selection < 1) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please try again." << endl;
            } else {
                valid = true;
            }
        }
    switch (selection) {
        case 1:
            structure = "Array";
            break;
        case 2:
            structure = "LinkedList";
            break;
    }
    return structure;
}

string algoSelect() {
    int selection;
    string sort;
    bool valid = false;
    cout << "\nPlease choose sorting method" << endl;
    cout << "1. Bubble Sort" << endl;
    cout << "2. Insert Sort" << endl;
    cout << "3. Merge Sort" << endl;

    while (!valid) {
        cout << ">>>   ";
        cin >> selection;
        if (cin.fail() || selection > 3 || selection < 1) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please try again.";
        } else {
            valid = true;
        }
    }
    switch (selection) {
        case 1:
            sort = "Bubble";
            break;
        case 2:
            sort = "Insert";
            break;
        case 3:
            sort = "Merge";
            break;
    }
    return sort;
}

void printArray(Residents* array, int size) {
    cout << "\n-------------------------------------------" << endl;
    cout << left 
    << setw(7) << "No." 
    << setw(10) << "ID" 
    << setw(7) << "Age" 
    << setw(10) << "Carbon" 
    << setw(15) << "Distance" << endl;
    cout << "-------------------------------------------" << endl;

    for (int i = 0; i < size; i++) {
        string number  = to_string(i+1);
        cout << left 
        << setw(7) << number + "." 
        << setw(10) << array[i].ID 
        << setw(7) << array[i].age 
        << setw(10) << array[i].carbon 
        << setw(15) << array[i].distance << endl;
    }
}

void printList(listResidents* head) {
    listResidents* currNode = head;
    int count = 1;
    cout << "\n-------------------------------------------" << endl;
    cout << left 
         << setw(7) << "No." 
         << setw(10) << "ID" 
         << setw(7) << "Age" 
         << setw(10) << "Carbon" 
         << setw(15) << "Distance" << endl;
    cout << "-------------------------------------------" << endl;
    while (currNode != nullptr) {
        string number = to_string(count);
        cout << left 
            << setw(7) << number + "." 
            << setw(10) << currNode->ID 
            << setw(7) << currNode->age 
            << setw(10) << currNode->carbon 
            << setw(15) << currNode->distance << endl;
        currNode = currNode->nextAddress;
        count++;
    }
}

int measureTime(std::function<void()> func) {
    auto start = std::chrono::steady_clock::now();
    func();
    auto end = std::chrono::steady_clock::now();
    return (int)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

