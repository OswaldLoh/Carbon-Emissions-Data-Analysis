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
    for (int i = 0; i < size; i++) {
        cout << i+1 << ".        "  << array[i].distance << endl;
    }
}