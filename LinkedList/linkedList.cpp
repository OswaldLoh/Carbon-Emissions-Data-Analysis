#include <iostream>
#include "../residentsList.h"

using namespace std;

linkedList::linkedList() {
    headAddress = nullptr;
}

Residents* linkedList::getHeadAddress() {
    return headAddress;
}

void linkedList::insertNode(string ID, int age, string mode, double distance, double carbon, double avg) {
    Residents* newAddress = new Residents;
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
        Residents* current = headAddress;
        while (current->nextAddress != nullptr) {
            current = current->nextAddress;
        }
        current->nextAddress = newAddress;
    }
}
