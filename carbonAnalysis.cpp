#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include "residents.h"

using namespace std;

double calcEmission(double distance, double carbon, double avg) {
    return distance * carbon * avg;
}

int getAgeGroupIndex(int age) {
    if (age >= 6  && age <= 17) return 0;
    if (age >= 18 && age <= 25) return 1;
    if (age >= 26 && age <= 45) return 2;
    if (age >= 46 && age <= 60) return 3;
    return 4;
}

int getModeIndex(const string& mode) {
    if (mode == "Car")        return 0;
    if (mode == "Bus")        return 1;
    if (mode == "Bicycle")    return 2;
    if (mode == "Walking")    return 3;
    if (mode == "School Bus") return 4;
    if (mode == "Carpool")    return 5;
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

void printSepC(int width = 80) {
    for (int i = 0; i < width; i++) cout << "-";
    cout << "\n";
}

void printDoubleSepC(int width = 80) {
    for (int i = 0; i < width; i++) cout << "=";
    cout << "\n";
}

void displayTotalEmission(const string& cityName, const string& structure,
                          double totalEmission, int totalCount) {
    printDoubleSepC();
    cout << "  CITY " << cityName << " - Total Carbon Emission ("
         << structure << ")\n";
    printDoubleSepC();
    cout << fixed << setprecision(2);
    cout << "  Total Residents      : " << totalCount << "\n";
    cout << "  Total Emission       : " << totalEmission << " kg CO2/month\n";
    double avg = 0;
    if (totalCount > 0) avg = totalEmission / totalCount;
    cout << "  Average per Resident : " << avg << " kg CO2/month\n";
    printDoubleSepC();
    cout << "\n";
}

void displayModeTable(const string& cityName, const string& structure,
                      double modeEmission[], int modeCount[],
                      double totalEmission, int totalCount) {
    printDoubleSepC();
    cout << "  CITY " << cityName << " - Emissions by Mode of Transport ("
         << structure << ")\n";
    printDoubleSepC();
    cout << fixed << setprecision(2);
    cout << left
         << setw(14) << "Mode"
         << setw(12) << "Residents"
         << setw(24) << "Total Emission(kg CO2)"
         << setw(22) << "Avg per Resident"
         << setw(10) << "% of Total" << "\n";
    printSepC();

    for (int m = 0; m < 6; m++) {
        if (modeCount[m] == 0) continue;
        double avg = modeEmission[m] / modeCount[m];
        double pct = 0;
        if (totalEmission > 0) pct = modeEmission[m] / totalEmission * 100.0;
        cout << left
             << setw(14) << MODE_LABELS[m]
             << setw(12) << modeCount[m]
             << setw(24) << modeEmission[m]
             << setw(22) << avg
             << setw(9)  << pct << "%\n";
    }
    printSepC();
    double overallAvg = 0;
    if (totalCount > 0) overallAvg = totalEmission / totalCount;
    cout << left
         << setw(14) << "TOTAL"
         << setw(12) << totalCount
         << setw(24) << totalEmission
         << setw(22) << overallAvg
         << setw(10) << "100.00%\n";
    printDoubleSepC();
    cout << "\n";
}

void displayAgeGroupTable(const string& cityName, const string& structure,
                          double groupEmission[], int groupCount[]) {
    printDoubleSepC(92);
    cout << "  CITY " << cityName << " - Emissions by Age Group ("
         << structure << ")\n";
    printDoubleSepC(92);
    cout << left
         << setw(38) << "Age Group"
         << setw(12) << "Residents"
         << setw(24) << "Total Emission(kg CO2)"
         << setw(22) << "Avg per Resident" << "\n";
    printSepC(92);

    for (int g = 0; g < 5; g++) {
        double avg = 0;
        if (groupCount[g] > 0) avg = groupEmission[g] / groupCount[g];
        cout << fixed << setprecision(2)
             << left
             << setw(38) << AGE_GROUP_LABELS[g]
             << setw(12) << groupCount[g]
             << setw(24) << groupEmission[g]
             << setw(22) << avg << "\n";
    }
    printDoubleSepC(92);
    cout << "\n";
}

void displayCrossCity(const string& structure,
                      double cityTotal[], int cityCount[],
                      double cityMode[][6], double cityAge[][5],
                      int numCities, int analysisType) {

    // [5a] Overall totals per city
    if (analysisType == 1 || analysisType == 4) {
        cout << "\n";
        printDoubleSepC(90);
        cout << "  CROSS-CITY COMPARISON - Total Emissions (" << structure << ")\n";
        printDoubleSepC(90);
        cout << left
             << setw(12) << "City"
             << setw(14) << "Residents"
             << setw(28) << "Total Emission (kg CO2)"
             << setw(24) << "Avg per Resident" << "\n";
        printSepC(90);

        double grandTotal = 0;
        int    grandCount = 0;
        for (int c = 0; c < numCities; c++) {
            double avg = 0;
            if (cityCount[c] > 0) avg = cityTotal[c] / cityCount[c];
            cout << fixed << setprecision(2)
                 << left
                 << setw(12) << ("City " + string(1, 'A' + c))
                 << setw(14) << cityCount[c]
                 << setw(28) << cityTotal[c]
                 << setw(24) << avg << "\n";
            grandTotal += cityTotal[c];
            grandCount += cityCount[c];
        }
        printSepC(90);
        double grandAvg = 0;
        if (grandCount > 0) grandAvg = grandTotal / grandCount;
        cout << left
             << setw(12) << "ALL CITIES"
             << setw(14) << grandCount
             << setw(28) << grandTotal
             << setw(24) << grandAvg << "\n";
        printDoubleSepC(90);
    }

    // [5b] By mode of transport
    if (analysisType == 2 || analysisType == 4) {
        cout << "\n";
        printDoubleSepC(90);
        cout << "  CROSS-CITY - Emissions by Mode of Transport (" << structure << ")\n";
        printDoubleSepC(90);
        cout << left
             << setw(14) << "Mode"
             << setw(24) << "City A (kg CO2)"
             << setw(24) << "City B (kg CO2)"
             << setw(24) << "City C (kg CO2)" << "\n";
        printSepC(90);

        for (int m = 0; m < 6; m++) {
            if (cityMode[0][m] == 0 && cityMode[1][m] == 0 && cityMode[2][m] == 0)
                continue;
            cout << left
                 << setw(14) << MODE_LABELS[m]
                 << setw(24) << cityMode[0][m]
                 << setw(24) << cityMode[1][m]
                 << setw(24) << cityMode[2][m] << "\n";
        }
        printDoubleSepC(90);
    }

    // [5c] By age group
    if (analysisType == 3 || analysisType == 4) {
        cout << "\n";
        printDoubleSepC(90);
        cout << "  CROSS-CITY - Emissions by Age Group (" << structure << ")\n";
        printDoubleSepC(90);
        cout << left
             << setw(38) << "Age Group"
             << setw(18) << "City A (kg CO2)"
             << setw(18) << "City B (kg CO2)"
             << setw(18) << "City C (kg CO2)" << "\n";
        printSepC(90);

        for (int g = 0; g < 5; g++) {
            cout << left
                 << setw(38) << AGE_GROUP_LABELS[g]
                 << setw(18) << cityAge[0][g]
                 << setw(18) << cityAge[1][g]
                 << setw(18) << cityAge[2][g] << "\n";
        }
        printDoubleSepC(90);
    }

    cout << "\n";
}

void collectStatsArray(Residents* array, int size,
                       double modeEmission[], int modeCount[],
                       double groupEmission[], int groupCount[],
                       double& totalEmission) {
    totalEmission = 0;
    for (int i = 0; i < size; i++) {
        double em = calcEmission(array[i].distance, array[i].carbon, array[i].avg);
        totalEmission += em;

        int m = getModeIndex(array[i].mode);
        if (m >= 0) { modeEmission[m] += em; modeCount[m]++; }

        int g = getAgeGroupIndex(array[i].age);
        groupEmission[g] += em;
        groupCount[g]++;
    }
}

void collectStatsList(linkedList& list,
                      double modeEmission[], int modeCount[],
                      double groupEmission[], int groupCount[],
                      double& totalEmission, int& totalCount) {
    totalEmission = 0;
    totalCount    = 0;
    listResidents* curr = list.getHead();
    while (curr != nullptr) {
        double em = calcEmission(curr->distance, curr->carbon, curr->avg);
        totalEmission += em;
        totalCount++;

        int m = getModeIndex(curr->mode);
        if (m >= 0) { modeEmission[m] += em; modeCount[m]++; }

        int g = getAgeGroupIndex(curr->age);
        groupEmission[g] += em;
        groupCount[g]++;

        curr = curr->nextAddress;
    }
}

int selectCityCarbon() {
    int sel;
    bool valid = false;
    cout << "\nCity Selection:\n";
    cout << "1. City A (Metropolitan)\n";
    cout << "2. City B (University Town)\n";
    cout << "3. City C (Suburban/Rural)\n";
    cout << "4. All Cities (Cross-City Comparison)\n";
    while (!valid) {
        cout << ">>>   ";
        cin >> sel;
        if (cin.fail() || sel < 1 || sel > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid option. Please try again.\n";
        } else {
            valid = true;
        }
    }
    return sel;
}

int selectAnalysisType() {
    int sel;
    bool valid = false;
    cout << "\nSelect Analysis Type:\n";
    cout << "1. Total Emission Summary\n";
    cout << "2. Emission by Mode of Transport\n";
    cout << "3. Emission by Age Group\n";
    cout << "4. All of the above\n";
    while (!valid) {
        cout << ">>>   ";
        cin >> sel;
        if (cin.fail() || sel < 1 || sel > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid option. Please try again.\n";
        } else {
            valid = true;
        }
    }
    return sel;
}

int selectStructureCarbon() {
    int sel;
    bool valid = false;
    cout << "\nSelect Data Structure:\n";
    cout << "1. Array\n";
    cout << "2. Linked List\n";
    cout << "3. Both (with performance comparison)\n";
    while (!valid) {
        cout << ">>>   ";
        cin >> sel;
        if (cin.fail() || sel < 1 || sel > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid option. Please try again.\n";
        } else {
            valid = true;
        }
    }
    return sel;
}

void runSingleCity(Container& city, int analysisType, int structureChoice) {

    string cityName = city.name;

    if (structureChoice == 1 || structureChoice == 3) {
        double modeEmission[6] = {0};
        int    modeCount[6]    = {0};
        double groupEmission[5]= {0};
        int    groupCount[5]   = {0};
        double totalEmission   = 0;

        collectStatsArray(city.array, city.size,
                          modeEmission, modeCount,
                          groupEmission, groupCount,
                          totalEmission);

        cout << "\n";
        printDoubleSepC(90);
        cout << "  *** ARRAY IMPLEMENTATION ***\n";
        printDoubleSepC(90);

        if (analysisType == 1 || analysisType == 4)
            displayTotalEmission(cityName, "Array", totalEmission, city.size);

        if (analysisType == 2 || analysisType == 4)
            displayModeTable(cityName, "Array",
                             modeEmission, modeCount, totalEmission, city.size);

        if (analysisType == 3 || analysisType == 4)
            displayAgeGroupTable(cityName, "Array", groupEmission, groupCount);
    }

    if (structureChoice == 2 || structureChoice == 3) {
        double modeEmission[6] = {0};
        int    modeCount[6]    = {0};
        double groupEmission[5]= {0};
        int    groupCount[5]   = {0};
        double totalEmission   = 0;
        int    totalCount      = 0;

        collectStatsList(city.list,
                         modeEmission, modeCount,
                         groupEmission, groupCount,
                         totalEmission, totalCount);

        cout << "\n";
        printDoubleSepC(90);
        cout << "  *** LINKED LIST IMPLEMENTATION ***\n";
        printDoubleSepC(90);

        if (analysisType == 1 || analysisType == 4)
            displayTotalEmission(cityName, "Linked List", totalEmission, totalCount);

        if (analysisType == 2 || analysisType == 4)
            displayModeTable(cityName, "Linked List",
                             modeEmission, modeCount, totalEmission, totalCount);

        if (analysisType == 3 || analysisType == 4)
            displayAgeGroupTable(cityName, "Linked List", groupEmission, groupCount);
    }

    if (structureChoice == 3) {
        cout << "\n";
        printDoubleSepC(90);
        cout << "  PERFORMANCE COMPARISON - City " << cityName << "\n";
        printDoubleSepC(90);

        int timeArray = measureTime([&]() {
            double t = 0;
            for (int i = 0; i < city.size; i++)
                t += calcEmission(city.array[i].distance,
                                  city.array[i].carbon,
                                  city.array[i].avg);
        });

        int timeList = measureTime([&]() {
            double t = 0;
            listResidents* curr = city.list.getHead();
            while (curr != nullptr) {
                t += calcEmission(curr->distance, curr->carbon, curr->avg);
                curr = curr->nextAddress;
            }
        });

        cout << fixed << setprecision(2);
        cout << left
             << setw(42) << "  Array traversal time:"
             << timeArray << " microseconds\n";
        cout << left
             << setw(42) << "  Linked List traversal time:"
             << timeList << " microseconds\n";
        cout << "\n  Note: Arrays use contiguous memory (cache-friendly),\n";
        cout << "  so sequential traversal is typically faster than\n";
        cout << "  Linked Lists whose nodes are scattered in heap memory.\n";
        printDoubleSepC(90);
        cout << "\n";
    }
}

void runCrossCity(Container* cities, int numCities, int structureChoice, int analysisType) {

    if (structureChoice == 1 || structureChoice == 3) {
        double cityTotal[3]   = {0};
        int    cityCount[3]   = {0};
        double cityMode[3][6] = {{0}};
        double cityAge[3][5]  = {{0}};

        for (int c = 0; c < numCities; c++) {
            double modeEm[6] = {0}; int modeCt[6] = {0};
            double ageEm[5]  = {0}; int ageCt[5]  = {0};
            double total = 0;

            collectStatsArray(cities[c].array, cities[c].size,
                              modeEm, modeCt, ageEm, ageCt, total);

            cityTotal[c] = total;
            cityCount[c] = cities[c].size;
            for (int m = 0; m < 6; m++) cityMode[c][m] = modeEm[m];
            for (int g = 0; g < 5; g++) cityAge[c][g]  = ageEm[g];
        }

        cout << "\n";
        printDoubleSepC(90);
        cout << "  *** ARRAY IMPLEMENTATION - Cross-City ***\n";
        printDoubleSepC(90);
        displayCrossCity("Array", cityTotal, cityCount,
                         cityMode, cityAge, numCities, analysisType);
    }

    if (structureChoice == 2 || structureChoice == 3) {
        double cityTotal[3]   = {0};
        int    cityCount[3]   = {0};
        double cityMode[3][6] = {{0}};
        double cityAge[3][5]  = {{0}};

        for (int c = 0; c < numCities; c++) {
            double modeEm[6] = {0}; int modeCt[6] = {0};
            double ageEm[5]  = {0}; int ageCt[5]  = {0};
            double total = 0;
            int    count = 0;

            collectStatsList(cities[c].list,
                             modeEm, modeCt, ageEm, ageCt, total, count);

            cityTotal[c] = total;
            cityCount[c] = count;
            for (int m = 0; m < 6; m++) cityMode[c][m] = modeEm[m];
            for (int g = 0; g < 5; g++) cityAge[c][g]  = ageEm[g];
        }

        cout << "\n";
        printDoubleSepC(90);
        cout << "  *** LINKED LIST IMPLEMENTATION - Cross-City ***\n";
        printDoubleSepC(90);
        displayCrossCity("Linked List", cityTotal, cityCount,
                         cityMode, cityAge, numCities, analysisType);
    }

    if (structureChoice == 3) {
        cout << "\n";
        printDoubleSepC(90);
        cout << "  PERFORMANCE COMPARISON - All Cities\n";
        printDoubleSepC(90);

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
             << setw(42) << "  Array traversal time (all cities):"
             << timeArray << " microseconds\n";
        cout << left
             << setw(42) << "  Linked List traversal time (all cities):"
             << timeList << " microseconds\n";
        cout << "\n  Note: Arrays use contiguous memory (cache-friendly),\n";
        cout << "  so sequential traversal is typically faster than\n";
        cout << "  Linked Lists whose nodes are scattered in heap memory.\n";
        printDoubleSepC(90);
        cout << "\n";
    }
}

void carbonAnalysis(Container* cities, int numCities) {

    cout << "\n";
    printDoubleSepC();
    cout << "  TASK 5: CARBON EMISSION ANALYSIS\n";
    printDoubleSepC();

    int cityChoice      = selectCityCarbon();
    int analysisType    = selectAnalysisType();
    int structureChoice = selectStructureCarbon();

    cout << fixed << setprecision(2);

    if (cityChoice == 4) {
        runCrossCity(cities, numCities, structureChoice, analysisType);
    } else {
        runSingleCity(cities[cityChoice - 1], analysisType, structureChoice);
    }
}