#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include "residents.h"

using namespace std;

double calcEmission(double distance, double carbon, double avg) {
    return distance * carbon * avg;
}

string getAgeGroupLabel(int age) {
    if (age >= 6  && age <= 17) return "6-17   (Children & Teenagers)      ";
    if (age >= 18 && age <= 25) return "18-25  (University / Young Adults)  ";
    if (age >= 26 && age <= 45) return "26-45  (Working Adults Early Career)";
    if (age >= 46 && age <= 60) return "46-60  (Working Adults Late Career) ";
    return                              "61-100 (Senior Citizens / Retirees) ";
}

int getAgeGroupIndex(int age) {
    if (age >= 6  && age <= 17) return 0;
    if (age >= 18 && age <= 25) return 1;
    if (age >= 26 && age <= 45) return 2;
    if (age >= 46 && age <= 60) return 3;
    return 4;
}

int getModeIndex(const string& mode) {
    if (mode == "Car")         return 0;
    if (mode == "Bus")         return 1;
    if (mode == "Bicycle")     return 2;
    if (mode == "Walking")     return 3;
    if (mode == "School Bus") return 4;
    if (mode == "Carpool")     return 5;
    return -1;
}

const string MODE_LABELS[6] = {
    "Car", "Bus", "Bicycle", "Walking", "School Bus", "Carpool"
};

const string AGE_GROUP_LABELS[5] = {
    "6-17   (Children & Teenagers)      ",
    "18-25  (University / Young Adults)  ",
    "26-45  (Working Adults Early Career)",
    "46-60  (Working Adults Late Career) ",
    "61-100 (Senior Citizens / Retirees) "
};

void printSep(int width = 80) {
    for (int i = 0; i < width; i++) cout << "-";
    cout << "\n";
}

void printDoubleSep(int width = 80) {
    for (int i = 0; i < width; i++) cout << "=";
    cout << "\n";
}

void carbonByModeArray(Residents* array, int size, const string& cityName) {
    double modeEmission[6]  = {0};
    int    modeCount[6]     = {0};
    double totalEmission    = 0;

    for (int i = 0; i < size; i++) {
        double em = calcEmission(array[i].distance, array[i].carbon, array[i].avg);
        totalEmission += em;
        int mIdx = getModeIndex(array[i].mode);
        if (mIdx >= 0) {
            modeEmission[mIdx] += em;
            modeCount[mIdx]++;
        }
    }

    printDoubleSep();
    cout << "   CITY " << cityName << " - Carbon Emission Analysis (ARRAY)\n";
    printDoubleSep();
    cout << fixed << setprecision(2);
    cout << "   Total Residents   : " << size << "\n";
    cout << "   Total Emission    : " << totalEmission << " kg CO2/month\n";
    cout << "   Average per Resident: "
         << (size > 0 ? totalEmission / size : 0) << " kg CO2/month\n\n";

    cout << "   [5b] Carbon Emissions by Mode of Transport\n";
    printSep();
    cout << left
         << setw(14) << "Mode"
         << setw(12) << "Residents"
         << setw(22) << "Total Emission(kg CO2)"
         << setw(22) << "Avg per Resident"
         << setw(10) << "% of Total" << "\n";
    printSep();

    for (int m = 0; m < 6; m++) {
        if (modeCount[m] == 0) continue;
        double avg  = modeEmission[m] / modeCount[m];
        double pct  = (totalEmission > 0) ? (modeEmission[m] / totalEmission * 100.0) : 0;
        cout << left
             << setw(14) << MODE_LABELS[m]
             << setw(12) << modeCount[m]
             << setw(22) << modeEmission[m]
             << setw(22) << avg
             << setw(10) << pct << "%\n";
    }
    printSep();
    cout << left
         << setw(14) << "TOTAL"
         << setw(12) << size
         << setw(22) << totalEmission
         << setw(22) << (size > 0 ? totalEmission / size : 0)
         << setw(10) << "100.00%\n";
    printDoubleSep();
    cout << "\n";
}

void carbonByAgeGroupArray(Residents* array, int size, const string& cityName) {
    double groupEmission[5] = {0};
    int    groupCount[5]    = {0};

    for (int i = 0; i < size; i++) {
        double em = calcEmission(array[i].distance, array[i].carbon, array[i].avg);
        int g = getAgeGroupIndex(array[i].age);
        groupEmission[g] += em;
        groupCount[g]++;
    }

    cout << "   [5c] City " << cityName << " - Emissions by Age Group (ARRAY)\n";
    printSep(90);
    cout << left
         << setw(38) << "Age Group"
         << setw(12) << "Residents"
         << setw(22) << "Total Emission(kg CO2)"
         << setw(22) << "Avg per Resident" << "\n";
    printSep(90);

    for (int g = 0; g < 5; g++) {
        double avg = (groupCount[g] > 0) ? groupEmission[g] / groupCount[g] : 0;
        cout << left
             << setw(38) << AGE_GROUP_LABELS[g]
             << setw(12) << groupCount[g]
             << setw(22) << groupEmission[g]
             << setw(22) << avg << "\n";
    }
    printSep(90);
    cout << "\n";
}

void carbonByModeList(linkedList& list, const string& cityName) {
    double modeEmission[6]  = {0};
    int    modeCount[6]     = {0};
    double totalEmission    = 0;
    int    totalCount       = 0;

    listResidents* curr = list.getHead();
    while (curr != nullptr) {
        double em = calcEmission(curr->distance, curr->carbon, curr->avg);
        totalEmission += em;
        totalCount++;
        int mIdx = getModeIndex(curr->mode);
        if (mIdx >= 0) {
            modeEmission[mIdx] += em;
            modeCount[mIdx]++;
        }
        curr = curr->nextAddress;
    }

    printDoubleSep();
    cout << "   CITY " << cityName << " - Carbon Emission Analysis (LINKED LIST)\n";
    printDoubleSep();
    cout << fixed << setprecision(2);
    cout << "   Total Residents   : " << totalCount << "\n";
    cout << "   Total Emission    : " << totalEmission << " kg CO2/month\n";
    cout << "   Average per Resident: "
         << (totalCount > 0 ? totalEmission / totalCount : 0) << " kg CO2/month\n\n";

    cout << "   [5b] Carbon Emissions by Mode of Transport\n";
    printSep();
    cout << left
         << setw(14) << "Mode"
         << setw(12) << "Residents"
         << setw(22) << "Total Emission(kg CO2)"
         << setw(22) << "Avg per Resident"
         << setw(10) << "% of Total" << "\n";
    printSep();

    for (int m = 0; m < 6; m++) {
        if (modeCount[m] == 0) continue;
        double avg = modeEmission[m] / modeCount[m];
        double pct = (totalEmission > 0) ? (modeEmission[m] / totalEmission * 100.0) : 0;
        cout << left
             << setw(14) << MODE_LABELS[m]
             << setw(12) << modeCount[m]
             << setw(22) << modeEmission[m]
             << setw(22) << avg
             << setw(10) << pct << "%\n";
    }
    printSep();
    cout << left
         << setw(14) << "TOTAL"
         << setw(12) << totalCount
         << setw(22) << totalEmission
         << setw(22) << (totalCount > 0 ? totalEmission / totalCount : 0)
         << setw(10) << "100.00%\n";
    printDoubleSep();
    cout << "\n";
}

void carbonByAgeGroupList(linkedList& list, const string& cityName) {
    double groupEmission[5] = {0};
    int    groupCount[5]    = {0};

    listResidents* curr = list.getHead();
    while (curr != nullptr) {
        double em = calcEmission(curr->distance, curr->carbon, curr->avg);
        int g = getAgeGroupIndex(curr->age);
        groupEmission[g] += em;
        groupCount[g]++;
        curr = curr->nextAddress;
    }

    cout << "   [5c] City " << cityName << " - Emissions by Age Group (LINKED LIST)\n";
    printSep(90);
    cout << left
         << setw(38) << "Age Group"
         << setw(12) << "Residents"
         << setw(22) << "Total Emission(kg CO2)"
         << setw(22) << "Avg per Resident" << "\n";
    printSep(90);

    for (int g = 0; g < 5; g++) {
        double avg = (groupCount[g] > 0) ? groupEmission[g] / groupCount[g] : 0;
        cout << left
             << setw(38) << AGE_GROUP_LABELS[g]
             << setw(12) << groupCount[g]
             << setw(22) << groupEmission[g]
             << setw(22) << avg << "\n";
    }
    printSep(90);
    cout << "\n";
}

void crossCityComparison(Array* cities, int numCities, const string& structure) {
    double cityTotal[3]     = {0};
    int    cityCount[3]     = {0};
    double cityMode[3][6]   = {{0}};
    double cityAge[3][5]    = {{0}};
    int    cityAgeCount[3][5] = {{0}};

    for (int c = 0; c < numCities; c++) {
        if (structure == "Array") {
            Residents* arr = cities[c].array;
            int sz         = cities[c].size;
            cityCount[c]   = sz;
            for (int i = 0; i < sz; i++) {
                double em = calcEmission(arr[i].distance, arr[i].carbon, arr[i].avg);
                cityTotal[c] += em;
                int m = getModeIndex(arr[i].mode);
                if (m >= 0) cityMode[c][m] += em;
                int g = getAgeGroupIndex(arr[i].age);
                cityAge[c][g]      += em;
                cityAgeCount[c][g]++;
            }
        } else {
            listResidents* curr = cities[c].list.getHead();
            while (curr != nullptr) {
                double em = calcEmission(curr->distance, curr->carbon, curr->avg);
                cityTotal[c] += em;
                cityCount[c]++;
                int m = getModeIndex(curr->mode);
                if (m >= 0) cityMode[c][m] += em;
                int g = getAgeGroupIndex(curr->age);
                cityAge[c][g]      += em;
                cityAgeCount[c][g]++;
                curr = curr->nextAddress;
            }
        }
    }

    cout << "\n";
    printDoubleSep(90);
    cout << "   [5c] CROSS-CITY COMPARISON - Total Emissions (" << structure << ")\n";
    printDoubleSep(90);
    cout << left
         << setw(12) << "City"
         << setw(14) << "Residents"
         << setw(26) << "Total Emission (kg CO2)"
         << setw(26) << "Avg per Resident" << "\n";
    printSep(90);

    double grandTotal = 0;
    int    grandCount = 0;
    for (int c = 0; c < numCities; c++) {
        string label = "City " + cities[c].name;
        double avg   = (cityCount[c] > 0) ? cityTotal[c] / cityCount[c] : 0;
        cout << left
             << setw(12) << label
             << setw(14) << cityCount[c]
             << setw(26) << cityTotal[c]
             << setw(26) << avg << "\n";
        grandTotal += cityTotal[c];
        grandCount += cityCount[c];
    }
    printSep(90);
    cout << left
         << setw(12) << "ALL CITIES"
         << setw(14) << grandCount
         << setw(26) << grandTotal
         << setw(26) << (grandCount > 0 ? grandTotal / grandCount : 0) << "\n";
    printDoubleSep(90);

    cout << "\n";
    printDoubleSep(90);
    cout << "   [5c] CROSS-CITY Emissions by Mode of Transport (" << structure << ")\n";
    printDoubleSep(90);
    cout << left
         << setw(14) << "Mode"
         << setw(24) << "City A (kg CO2)"
         << setw(24) << "City B (kg CO2)"
         << setw(24) << "City C (kg CO2)" << "\n";
    printSep(90);

    for (int m = 0; m < 6; m++) {
        if (cityMode[0][m] == 0 && cityMode[1][m] == 0 && cityMode[2][m] == 0)
            continue;
        cout << left
             << setw(14) << MODE_LABELS[m]
             << setw(24) << cityMode[0][m]
             << setw(24) << cityMode[1][m]
             << setw(24) << cityMode[2][m] << "\n";
    }
    printDoubleSep(90);

    cout << "\n";
    printDoubleSep(90);
    cout << "   [5c] CROSS-CITY Emissions by Age Group (" << structure << ")\n";
    printDoubleSep(90);
    cout << left
         << setw(38) << "Age Group"
         << setw(17) << "City A (kg CO2)"
         << setw(17) << "City B (kg CO2)"
         << setw(17) << "City C (kg CO2)" << "\n";
    printSep(90);

    for (int g = 0; g < 5; g++) {
        cout << left
             << setw(38) << AGE_GROUP_LABELS[g]
             << setw(17) << cityAge[0][g]
             << setw(17) << cityAge[1][g]
             << setw(17) << cityAge[2][g] << "\n";
    }
    printDoubleSep(90);
    cout << "\n";
}

void carbonAnalysis(Array* cities, int numCities) {
    int choice;
    bool valid = false;

    cout << "\n";
    printDoubleSep();
    cout << "   CARBON EMISSION ANALYSIS\n";
    printDoubleSep();
    cout << "   Select data structure:\n";
    cout << "   1. Array\n";
    cout << "   2. Linked List\n";
    cout << "   3. Both (run Array then Linked List)\n";

    while (!valid) {
        cout << "   >>>   ";
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "   Invalid option. Please try again.\n";
        } else {
            valid = true;
        }
    }

    if (choice == 1 || choice == 3) {
        cout << "\n";
        printDoubleSep(90);
        cout << "   *** ARRAY IMPLEMENTATION ***\n";
        printDoubleSep(90);
        cout << fixed << setprecision(2);

        for (int c = 0; c < numCities; c++) {
            carbonByModeArray(cities[c].array, cities[c].size, cities[c].name);
        }

        for (int c = 0; c < numCities; c++) {
            carbonByAgeGroupArray(cities[c].array, cities[c].size, cities[c].name);
        }

        crossCityComparison(cities, numCities, "Array");
    }

    if (choice == 2 || choice == 3) {
        cout << "\n";
        printDoubleSep(90);
        cout << "   *** LINKED LIST IMPLEMENTATION ***\n";
        printDoubleSep(90);
        cout << fixed << setprecision(2);

        for (int c = 0; c < numCities; c++) {
            carbonByModeList(cities[c].list, cities[c].name);
        }

        for (int c = 0; c < numCities; c++) {
            carbonByAgeGroupList(cities[c].list, cities[c].name);
        }

        crossCityComparison(cities, numCities, "Linked List");
    }

    if (choice == 3) {
        cout << "\n";
        printDoubleSep(90);
        cout << "   PERFORMANCE COMPARISON (Array vs Linked List)\n";
        printDoubleSep(90);

        int timeArray = measureTime([&]() {
            for (int c = 0; c < numCities; c++) {
                double t = 0;
                for (int i = 0; i < cities[c].size; i++)
                    t += calcEmission(cities[c].array[i].distance,
                                      cities[c].array[i].carbon,
                                      cities[c].array[i].avg);
            }
        });

        int timeList = measureTime([&]() {
            for (int c = 0; c < numCities; c++) {
                double t = 0;
                listResidents* curr = cities[c].list.getHead();
                while (curr != nullptr) {
                    t += calcEmission(curr->distance, curr->carbon, curr->avg);
                    curr = curr->nextAddress;
                }
            }
        });

        cout << left
             << setw(40) << "   Array traversal time (all cities):"
             << timeArray << " microseconds\n";
        cout << left
             << setw(40) << "   Linked List traversal time (all cities):"
             << timeList << " microseconds\n";
        cout << "\n   Note: Array is faster due to contiguous memory (cache-friendly).\n";
        cout << "   Linked List nodes are scattered in heap memory,\n";
        cout << "   causing more cache misses during sequential traversal.\n";
        printDoubleSep(90);
        cout << "\n";
    }
}