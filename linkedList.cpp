#include <iostream>
#include "residents.h"

using namespace std;

linkedList::linkedList() {
    headAddress = nullptr;
}

void linkedList::clear() {
    listResidents* current = headAddress;
    while (current != nullptr) {
        listResidents* next = current->nextAddress;
        delete current;
        current = next;
    }
    headAddress = nullptr;
}

int linkedList::getSize() {
    int size = 0;
    listResidents* current = headAddress;
    while (current != nullptr) {
        size++;
        current = current->nextAddress;
    }
    return size;
}

void linkedList::setHead(listResidents* newAddress) {
    headAddress = newAddress;
}

listResidents* linkedList::getHead() {
    return headAddress;
}

void linkedList::insertNode(string ID, int age, string mode, double distance, double carbon, double avg) {
    listResidents* newAddress = new listResidents;
    newAddress->ID = ID;
    newAddress->age = age;
    newAddress->mode = mode;
    newAddress->distance = distance;
    newAddress->carbon = carbon;
    newAddress->avg = avg;
    newAddress->nextAddress = nullptr;

    if (headAddress == nullptr) {
        headAddress = newAddress;
    } else {
        listResidents* current = headAddress;
        while (current->nextAddress != nullptr) {
            current = current->nextAddress;
        }
        current->nextAddress = newAddress;
    }
}
