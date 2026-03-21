#include <iostream>
#include <limits>
#include "residents.h"

using namespace std;

int sortBubbleArray(Residents array[], int size) {
    string category = sortBy();
    bool swapped;
    if (category == "Age") {
        for (int i = 0; i < size-1; i++) {
            swapped = false;
            for (int j = 0; j < size-i-1; j++) {
                if (array[j].age > array[j+1].age) {
                    swap(array[j], array[j + 1]);
                    swapped = true;
                }
            }
        }
        for (int i = 0; i < size; i++) {
            cout << array[i].ID + "       " << array[i].carbon;
        }
    }

    return 0;
}