#include <iostream>
#include <limits>
#include <functional>
#include <iomanip>
#include "residents.h"

using namespace std;


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

void sorting(string structure, string algo, Array city, string category) {
    if (structure == "Array") {
        if (algo == "Bubble") {
            sortBubbleArray(city.array, city.size, category);
            printArray(city.array, city.size);
        } else if (algo == "Insert") {
            sortInsertArray(city.array, city.size, category);   
            printArray(city.array, city.size);
        } else if (algo == "Merge") {
            merge(city.array,0,city.size-1,category);
            printArray(city.array, city.size);
        }
    } else if (structure == "LinkedList") {   
        if (algo == "Bubble") {
            sortBubbleList(city.list,category);
            printList(city.list.getHead());
        } else if (algo == "Insert") {
            sortInsertList(city.list,category);
            printList(city.list.getHead());
        } else if (algo == "Merge") {

        }
    }
}

void sortInsertList(linkedList& list, string category) {
    listResidents*head = list.getHead();
    int size = list.getSize();
    auto compare = comparator<listResidents>(category);
    if (!head || !head->nextAddress) return;
    listResidents* sorted = nullptr;
    listResidents* current = head;

    while (current != nullptr) {
        listResidents* next = current->nextAddress;

        if (sorted == nullptr || compare(*sorted, *current)) {
            current->nextAddress = sorted;
            sorted = current;
        } else {
            listResidents* cNode = sorted;
            while (cNode->nextAddress != nullptr && !compare(*cNode->nextAddress,*current)) {
                cNode = cNode->nextAddress;
            }
            current->nextAddress = cNode->nextAddress;
            cNode->nextAddress = current;
        }  
        current = next;
    }
    list.setHead(sorted);
}

void merge(Residents* array, int indexL, int indexR, string category) {
    if (indexL < indexR) {
        int indexM = indexL + (indexR - indexL) / 2;
        merge(array, indexL, indexM, category);
        merge(array, indexM+1, indexR, category);  
        mergeSort(array, indexL, indexM, indexR, category); 
    }
}

void mergeSort(Residents* array, int indexL, int indexM, int indexR, string category) {
    auto compare = comparator<Residents>(category);
    int leftSize = indexM - indexL + 1;
    int rightSize = indexR - indexM;

    Residents leftArray[leftSize],rightArray[rightSize];
    for (int i=0; i < leftSize; i++) {
        leftArray[i] = array[indexL + i];
    }
    for (int j=0; j < rightSize; j++) {
        rightArray[j] = array[indexM + 1 + j];
    }
    int i = 0, j = 0, k = indexL;
    while(i < leftSize && j < rightSize) {
        if (!compare(leftArray[i], rightArray[j])) {
            array[k++] = leftArray[i++];
        } else {
            array[k++] = rightArray[j++];
        }
    }
    while(i < leftSize) {
        array[k++] = leftArray[i++];
    }
    while(j < rightSize) {
        array[k++] = rightArray[j++];
    }
}

void sortInsertArray(Residents* array, int size, string category) {
    auto compare = comparator<Residents>(category);
    bool swapped = false;
    for (int i=1; i<size; i++) {
        Residents key = array[i];
        int j = i - 1;

        while (j>=0 && compare(array[j],key)) {
            array[j+1] = array[j];
            j = j - 1;
        }
        array[j+1] = key;
    }
}

void sortBubbleList(linkedList& list, string category) {
    listResidents* head = list.getHead();
    int size = list.getSize();
    int i = 0;

    auto compare = comparator<listResidents>(category);

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
}


