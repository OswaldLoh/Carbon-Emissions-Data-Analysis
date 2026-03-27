#include <iostream>
#include <iomanip>
#include "residents.h"

using namespace std;

// Structure to store stats for each age group
struct AgeGroupStats {
    int count = 0;
    double totalEmission = 0;

    int car = 0;
    int bus = 0;
    int bicycle = 0;
    int walking = 0;
    int schoolBus = 0;
    int carpool = 0;
};

// Function to find most preferred transport
string findMaxMode(AgeGroupStats g) {
    if (g.count == 0) {
        return "None";
    }
    int max = g.car;
    string mode = "Car";

    if (g.bus > max) { 
        max = g.bus; mode = "Bus"; 
    }
    if (g.bicycle > max) { 
        max = g.bicycle; mode = "Bicycle"; 
    }
    if (g.walking > max) { 
        max = g.walking; mode = "Walking"; 
    }
    if (g.schoolBus > max) { 
        max = g.schoolBus; mode = "School Bus"; 
    }
    if (g.carpool > max) { 
        max = g.carpool; mode = "Carpool"; 
    }

    return mode;
}

// ==========================
// ARRAY VERSION
// ==========================
void categorizeArray(Residents array[], int size) {

    AgeGroupStats group[5];

    // Loop through all residents
    for (int i = 0; i < size; i++) {

        int age = array[i].age;
        int index;

        // Determine age group index
        if (age >= 6 && age <= 17) index = 0;
        else if (age <= 25) index = 1;
        else if (age <= 45) index = 2;
        else if (age <= 60) index = 3;
        else index = 4;

        // Calculate emission
        double emission = array[i].distance 
                        * array[i].carbon 
                        * array[i].avg;

        // Update stats
        group[index].count++;
        group[index].totalEmission += emission;

        // Count transport mode
        if (array[i].mode == "Car") group[index].car++;
        else if (array[i].mode == "Bus") group[index].bus++;
        else if (array[i].mode == "Bicycle") group[index].bicycle++;
        else if (array[i].mode == "Walking") group[index].walking++;
        else if (array[i].mode == "School Bus") group[index].schoolBus++;
        else if (array[i].mode == "Carpool") group[index].carpool++;
    }

    // Labels for printing
    string labels[5] = {
        "6-17: Children & Teenagers",
        "18-25: University Students / Young Adults",
        "26-45: Working Adults (Early Career)",
        "46-60: Working Adults (Late Career)",
        "61-100: Senior Citizens / Retirees"
    };

    // Print results
    cout << "\n======== AGE GROUP ANALYSIS (ARRAY) ========\n";
    cout << left << setw(50) << "Age Group"
         << setw(20) << "Total Emission"
         << setw(20) << "Avg Emission"
         << setw(20) << "Preferred Mode" << endl;

    for (int i = 0; i < 5; i++) {
        double avg = 0;
        if (group[i].count > 0) {
            avg = group[i].totalEmission / group[i].count;
        }

        cout << left << setw(50) << labels[i]
             << setw(20) << group[i].totalEmission
             << setw(20) << avg
             << setw(20) << findMaxMode(group[i]) << endl;
    }
}


// ==========================
// LINKED LIST VERSION
// ==========================
void categorizeList(linkedList& list) {

    AgeGroupStats group[5];
    listResidents* current = list.getHead();

    while (current != nullptr) {

        int age = current->age;
        int index;

        if (age >= 6 && age <= 17) index = 0;
        else if (age <= 25) index = 1;
        else if (age <= 45) index = 2;
        else if (age <= 60) index = 3;
        else index = 4;

        double emission = current->distance 
                        * current->carbon 
                        * current->avg;

        group[index].count++;
        group[index].totalEmission += emission;

        if (current->mode == "Car") group[index].car++;
        else if (current->mode == "Bus") group[index].bus++;
        else if (current->mode == "Bicycle") group[index].bicycle++;
        else if (current->mode == "Walking") group[index].walking++;
        else if (current->mode == "School Bus") group[index].schoolBus++;
        else if (current->mode == "Carpool") group[index].carpool++;

        current = current->nextAddress;
    }

    string labels[5] = {
        "6-17: Children & Teenagers",
        "18-25: University Students / Young Adults",
        "26-45: Working Adults (Early Career)",
        "46-60: Working Adults (Late Career)",
        "61-100: Senior Citizens / Retirees"
    };

    cout << "\n======== AGE GROUP ANALYSIS (LINKED LIST) ========\n";
    cout << left << setw(50) << "Age Group"
         << setw(20) << "Total Emission"
         << setw(20) << "Avg Emission"
         << setw(20) << "Preferred Mode" << endl;

    for (int i = 0; i < 5; i++) {
        double avg = 0;
        if (group[i].count > 0) {
            avg = group[i].totalEmission / group[i].count;
        }

        cout << left << setw(50) << labels[i]
             << setw(20) << group[i].totalEmission
             << setw(20) << avg
             << setw(20) << findMaxMode(group[i]) << endl;
    }
}