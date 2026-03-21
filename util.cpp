#include <iostream>
#include <limits>
#include "residents.h"

using namespace std;

string citySelection() {    
    int selection;
    string city;
    bool valid = false;
    cout << "City Selection:" << endl;
    cout << "1. City A" << endl;
    cout << "2. City B" << endl;
    cout << "3. City C" << endl;
    while (!valid) {
        cout << ">>>   ";
        cin >> selection;
        if (cin.fail() || selection > 4 || selection << 1) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please try again." << endl;
        } else {
            valid = true;
        }
    }
    switch (selection) {
        case 1:
            city = "A";
        case 2:
            city = "B";
        case 3:
            city = "C";
    }
return city;

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
        if (cin.fail() || selection > 3 || selection << 1) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            valid = true;
        }
    }
    switch (selection) {
        case 1:
            category = "Age";
        case 2:
            category = "Distance";
        case 3:
            category = "Carbon";
    }
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
        case 2:
            structure = "LinkedList";
    }
    return structure;
}

string sortSelect() {
    int selection;
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
    return 0;
}