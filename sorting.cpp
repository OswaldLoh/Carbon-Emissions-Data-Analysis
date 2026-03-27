#include <iostream>
#include <limits>
#include <functional>
#include <iomanip>
#include "residents.h"

using namespace std;

void sorting(string structure, string algo, Array city, string category) {
    if (structure == "Array") {
        if (algo == "Bubble") {
            sortBubbleArray(city.array, city.size, category);
        } else if (algo == "Insert") {

        } else if (algo == "Merge") {

        }
    } else if (structure == "LinkedList") {   
        if (algo == "Bubble") {

        } else if (algo == "Insert") {

        } else if (algo == "Merge") {

        }
    }
}

void sortBubbleList(linkedList& list, string category) {
    listResidents* head = list.getHead();
    int size = list.getSize();
    int i = 0;
    bool swapped;

    while (i < size) {
        listResidents* currNode = head;
        listResidents* prevNode = head;
  
        // [99,5,10,9,7,21]
        while (currNode->nextAddress != nullptr) {
            listResidents* temp = currNode->nextAddress;
            if (currNode->age > temp->age) {
                swapped = true;
                if (currNode == head) {
                    currNode->nextAddress = temp->nextAddress; // cur.nextAddress lets go of 5 and point to 10
                    temp->nextAddress = currNode; // temp (5) next address lets go of 10 and points to 99
                    prevNode = temp;              // prevNode is now temp (5)
                    head = prevNode;             
                } else {
                    currNode->nextAddress = temp->nextAddress;  // currNode(9) lets go of 7 and points to 21
                    temp->nextAddress = currNode; // temp (7) points back to 9 (swap happens)
                    prevNode->nextAddress = temp; // prevNode.nextAddress lets go of 9 and points to temp (7)
                    prevNode = temp;              // curr node progress to 9, so previous should be 7
                }
                continue;
            } // No swap occur
            prevNode = currNode;
            currNode = currNode->nextAddress;
        }
        if (!swapped) {
            break;
        }
        i++;
    }
}

void sortBubbleArray(Residents *array, int size, string category) {
    function<bool(const Residents&, const Residents&)> compare;
    if (category == "Age") {
        compare = [](const Residents& a, const Residents& b) {
            return a.age > b.age;
        };
    } else if (category == "Distance") {
        compare = [](const Residents&a, const Residents& b) {
            return a.distance > b.distance;
        };
    } else if (category == "Carbon") {
        compare = [](const Residents&a, const Residents& b) {
            return a.carbon > b.carbon;
        };
    }
    bool swapped;
    for (int i = 0; i < size-1; i++) {
        swapped = false;
        for (int j = 0; j < size-i-1; j++) {
            if (compare(array[j], array[j+1])) {
                swap(array[j], array[j + 1]);
                swapped = true;
            }
        }
    }
    cout << "-------------------------------------------" << endl;
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