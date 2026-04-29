#include <iostream>
#include <limits>
#include <functional>
#include <iomanip>
#include "residents.h"
#include <chrono>

using namespace std;

template <typename type>
function<bool(const type&, const type&)> comparator(string category, string state) {
    if (state == "Sorted") {
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
    } else if (state == "Reverse") {
        if (category == "Age") {
            return [](const type& a, const type& b) {
                return b.age > a.age;
            };
        } else if (category == "Distance") {
            return [](const type& a, const type& b) {
                return b.distance > a.distance;
            };
        }
        return [](const type& a, const type& b) {
            return b.carbon > a.carbon;
        };
    }
}


void sorting(string structure, string algo, Container city, string category, string state) {
    int execTime;
    size_t dataMemory = 0;
    size_t auxiliaryMemory = 0;
    string timeCom, spaceCom;
    
    if (state == "Sorted") {
        sortBubbleArray(city.array, city.size, category, state);
        sortBubbleList(city.list,category, state);
    } else if (state == "Reverse") {
        
    }

    if (structure == "Array") {
        dataMemory = city.size * sizeof(Residents);
        if (algo == "Bubble") {
            execTime = measureTime([&]() { sortBubbleArray(city.array, city.size, category, state); });
            auxiliaryMemory = sizeof(Residents); 
            printArray(city.array, city.size);
            spaceCom = "O(1)";
            timeCom = "O(n)";
        } else if (algo == "Insert") {
            execTime = measureTime([&]() { sortInsertArray(city.array, city.size, category, state); });
            auxiliaryMemory = sizeof(Residents); 
            printArray(city.array, city.size);
            spaceCom = "O(1)";
            timeCom = "O(n)";
        } else if (algo == "Merge") {
            execTime = measureTime([&]() { mergeArray(city.array, 0, city.size - 1, category, state); });
            auxiliaryMemory = city.size * sizeof(Residents); 
            printArray(city.array, city.size);
            spaceCom = "O(n)";
            timeCom = "O(n log n)";
        }
    } else if (structure == "LinkedList") {
        dataMemory = city.list.getSize() * sizeof(listResidents);
        if (algo == "Bubble") {
            execTime = measureTime([&]() { sortBubbleList(city.list, category, state); });
            auxiliaryMemory = sizeof(listResidents*) * 3; 
            printList(city.list.getHead());
            spaceCom = "O(1)";
            timeCom = "O(n)";
        } else if (algo == "Insert") {
            execTime = measureTime([&]() { sortInsertList(city.list, category, state); });
            auxiliaryMemory = sizeof(listResidents*) * 3;
            printList(city.list.getHead());
            spaceCom = "O(1)";
            timeCom = "O(n)";
        } else if (algo == "Merge") {
            listResidents* sortedHead;
            execTime = measureTime([&]() { sortedHead = mergeListSort(city.list.getHead(), category, state); });
            city.list.setHead(sortedHead);
            int logN = 0;
            int temp = city.list.getSize();
            while (temp > 1) { temp /= 2; logN++; }
            auxiliaryMemory = logN * (sizeof(listResidents*) * 3);
            printList(city.list.getHead());
            spaceCom = "O(log n)";
            timeCom = "O(n log n)";
        }
    }

    fileOutput(city,category,structure);
    cout << "\n========================================================" << endl;
    cout << "       " << algo << " Sort | " << structure << " | " << "City " << city.name << " | " << "Sort by " << category << endl;
    cout << "========================================================" << endl;
    cout << "--------------------< Memory Usage >--------------------" << endl;
    cout << left << setw(20) << "Input Space"               << ": " << dataMemory << " bytes" << endl;
    cout << left << setw(20) << "Auxiliary Space "<< ": " << auxiliaryMemory << " bytes" << endl;
    cout << left << setw(20) << "Total Memory"               << ": " << dataMemory + auxiliaryMemory << " bytes" << endl;
    cout << left << setw(20) << "Space Complexity" << ": " << spaceCom << endl;
    cout << "\n---------------------< Performance >--------------------" << endl;
    cout << left << setw(20) << "Execution Time " << ": " << execTime << " microseconds" << std::endl;
    cout << left << setw(20) << "Time Complexity" << ": " << timeCom << endl;

}


listResidents* split(listResidents* head) {
    listResidents* fast = head;
    listResidents* slow = head;
    while (fast != nullptr && fast->nextAddress != nullptr) {
        fast = fast->nextAddress->nextAddress;
        if (fast != nullptr) {
            slow = slow->nextAddress;
        }
    }
    listResidents* tempHead = slow->nextAddress;
    slow->nextAddress = nullptr;
    return tempHead;
}

listResidents* merge(listResidents* first, listResidents* second, const string& category, string state) {
    auto compare = comparator<listResidents>(category, state);

    if (first == nullptr) return second;
    if (second == nullptr) return first;

    listResidents dummy;
    listResidents* tail = &dummy;

    while (first != nullptr && second != nullptr) {
        if (compare(*second, *first)) {
            tail->nextAddress = first;
            first = first->nextAddress;
        } else {
            tail->nextAddress = second;
            second = second->nextAddress;
        }
        tail = tail->nextAddress;
    }

    tail->nextAddress = (first != nullptr) ? first : second;

    return dummy.nextAddress;
}

listResidents* mergeListSort(listResidents* head, const string& category, string state) {
    if (head == nullptr || head->nextAddress == nullptr) {
        return head;
    }
    listResidents* second = split(head);
    head = mergeListSort(head, category, state);
    second = mergeListSort(second, category, state);
    return merge(head, second, category);
}



void mergeArray(Residents* array, int indexL, int indexR, string category, string state) {
    if (indexL < indexR) {
        int indexM = indexL + (indexR - indexL) / 2;
        mergeArray(array, indexL, indexM, category, state);
        mergeArray(array, indexM+1, indexR, category, state); 
        mergeSort(array, indexL, indexM, indexR, category, state); 
    }
}

void mergeSort(Residents* array, int indexL, int indexM, int indexR, string category, string state) {
    auto compare = comparator<Residents>(category,state);
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

void sortInsertList(linkedList& list, string category, string state) {
    listResidents* head = list.getHead();
    int size = list.getSize();
    auto compare = comparator<listResidents>(category,state);
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

void sortInsertArray(Residents* array, int size, string category, string state) {
    auto compare = comparator<Residents>(category, state);
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

void sortBubbleList(linkedList& list, string category, string state) {
    listResidents* head = list.getHead();
    int size = list.getSize();
    int i = 0;

    auto compare = comparator<listResidents>(category, state);

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

void sortBubbleArray(Residents *array, int size, string category, string state) {
    auto compare = comparator<Residents>(category, state);
    bool swapped;
    for (int i = 0; i < size-1; i++) {
        swapped = false;
        for (int j = 0; j < size-i-1; j++) {
            if (compare(array[j], array[j+1])) {
                swap(array[j], array[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}



