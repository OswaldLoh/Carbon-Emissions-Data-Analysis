#include <iostream>
#include <limits>
#include "residents.h"

using namespace std;

Array citySelection(Array* arrays, int size) {    
    int selection;
    bool valid = false;
    cout << "City Selection:" << endl;
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
            return arrays[0];
        case 2:
            return arrays[1];
        case 3:
            return arrays[2];
    }
    return arrays[0];
}

string sortBy() {
    int selection;
    string category;
    bool valid = false;
    cout << "Sort by:" << endl;
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
    cout << "hello!";
    return category;
}

string structureSelect() {
    int selection;
    string structure;
    bool valid = false;
    cout << "Please choose data structure" << endl;
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

string sortSelect() {
    int selection;
    string sort;
    bool valid = false;
    cout << "Please choose sorting method" << endl;
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