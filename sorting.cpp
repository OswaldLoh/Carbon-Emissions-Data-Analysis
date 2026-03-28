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
            sortBubbleList(city.list,category);
        } else if (algo == "Insert") {

        } else if (algo == "Merge") {

        }
    }
}

template <typename type>
function<bool(const type&, const type&)> comparator(string category) {
    if (category == "Age") {
        return [](const type& a, const type& b) {
            return a.age > b.age;
        };
    } else if (category == "Distance") {
        return [](const type& a, const type& b) {
            return a.distance > b.distance;
        };
    }
    return [](const type& a, const type& b) {
        return a.carbon > b.carbon;
    };
}

void sortBubbleList(linkedList& list, string category) {
    listResidents* head = list.getHead();
    int size = list.getSize();
    int i = 0;

    auto compare = comparator<listResidents>(category);
    if (category == "Age") {
        compare = [](const listResidents& a, const listResidents& b) {
            return a.age > b.age;
        };
    } else if (category == "Distance") {
        compare = [](const listResidents&a, const listResidents& b) {
            return a.distance > b.distance;
        };
    } else if (category == "Carbon") {
        compare = [](const listResidents&a, const listResidents& b) {
            return a.carbon > b.carbon;
        };
    }

    while (i < size) {
        bool swapped = false;
        listResidents* currNode = head;
        listResidents* prevNode = head;
  
        // [99,5,10,9,7,21]
        while (currNode->nextAddress != nullptr) {
            listResidents* temp = currNode->nextAddress;
            if (compare(*currNode,*temp)) {
                swapped = true;
                if (currNode == head) {
                    currNode->nextAddress = temp->nextAddress; // cur.nextAddress lets go of 5 and point to 10
                    temp->nextAddress = currNode; // temp (5) next address lets go of 10 and points to 99
                    prevNode = temp;              // prevNode is now temp (5)
                    head = prevNode;
                    list.setHead(head);          
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
    printList(head);
}

void sortBubbleArray(Residents *array, int size, string category) {
    auto compare = comparator<Residents>(category);
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
    printArray(array,size);
}


