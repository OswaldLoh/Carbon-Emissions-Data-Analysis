/*
    Searching Experiments (Question 7)
    - Linear Search: O(N) time, O(1) space — works on unsorted data
    - Binary Search: O(log N) time, O(N) space — arrays only, requires pre-sort
    Reuses: mergeArray() from sorting.cpp, structureSelect() from util.cpp
*/

#include <iostream>
#include <iomanip>
#include <chrono>
#include <cmath>
#include <limits>
#include <string>
#include "residents.h"

using namespace std;

// -- Experiment logging: stores timing results for comparison table --
struct SearchStats {
    string structure, algorithm, criteria;
    int matches, comparisons;
    long long timeUs;
};
SearchStats searchLog[20];
int logCount = 0;

// same age group boundaries as categorization.cpp so results are consistent
const int AGE_MIN[] = {6, 18, 26, 46, 61};
const int AGE_MAX[] = {17, 25, 45, 60, 100};
const string AGE_LABELS[] = {
    "6-17: Children & Teenagers",
    "18-25: University Students / Young Adults",
    "26-45: Working Adults (Early Career)",
    "46-60: Working Adults (Late Career)",
    "61-100: Senior Citizens / Retirees"
};
const string MODES[] = {"Car", "Bus", "Bicycle", "Walking", "School Bus", "Carpool"};

// --- Shared input validator (avoids repeating the same while loop in every menu) ---
int getInput(int min, int max) {
    int val;
    while (true) {
        cout << ">>>   ";
        cin >> val;
        if (!cin.fail() && val >= min && val <= max) return val;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid. Try again." << endl;
    }
}

// checks if a resident matches the search criteria
bool isMatch(int criteria, int age, string mode, double dist,
             int minAge, int maxAge, string targetMode, double threshold) {
    if (criteria == 1) return (age >= minAge && age <= maxAge);
    if (criteria == 2) return (mode == targetMode);
    if (criteria == 3) return (dist > threshold);
    // criteria 4: combined age group + distance filter
    if (criteria == 4) return (age >= minAge && age <= maxAge && dist > threshold);
    return false;
}

// readable label for what was searched
string criteriaLabel(int criteria, int minAge, int maxAge,
                     string targetMode, double threshold) {
    if (criteria == 1) return "Age " + to_string(minAge) + "-" + to_string(maxAge);
    if (criteria == 2) return "Mode: " + targetMode;
    if (criteria == 3) return "Distance > " + to_string((int)threshold) + " km";
    return "Age " + to_string(minAge) + "-" + to_string(maxAge)
           + " AND Dist > " + to_string((int)threshold) + "km";
}

// --- Table printing helpers ---
void printHeader(string city, string algo, string structure, string criteria) {
    cout << "\n" << string(70, '=') << endl;
    cout << "  City " << city << " | " << algo << " | " << structure << endl;
    cout << "  Criteria: " << criteria << endl;
    cout << string(70, '=') << endl;
    cout << left << setw(6) << "No." << setw(8) << "ID" << setw(6) << "Age"
         << setw(12) << "Transport" << setw(10) << "Dist(km)"
         << setw(10) << "CO2/km" << setw(8) << "Days"
         << setw(10) << "Emission" << endl;
    cout << string(70, '-') << endl;
}

// emission = distance * carbonFactor * avgDaysPerMonth (same formula as categorization.cpp)
void printRow(int num, string id, int age, string mode,
              double dist, double carbon, double avg) {
    cout << left << setw(6) << num << setw(8) << id << setw(6) << age
         << setw(12) << mode
         << setw(10) << fixed << setprecision(2) << dist
         << setw(10) << carbon
         << setw(8) << setprecision(0) << avg
         << setw(10) << setprecision(2) << (dist * carbon * avg) << endl;
}

// Prints match count, total comparisons, and execution time below each result table
void printFooter(int matches, int comps, long long us) {
    cout << string(70, '-') << endl;
    cout << "  Matches: " << matches << "  |  Comparisons: " << comps
         << "  |  Time: " << us << " us" << endl;
    cout << string(70, '=') << endl;
}


// Linear Search — Array | O(N) time, O(1) space | works on unsorted data
void linearSearchArray(Residents* arr, int size, int criteria,
                       int minAge, int maxAge, string targetMode,
                       double threshold, string cityName) {

    string label = criteriaLabel(criteria, minAge, maxAge, targetMode, threshold);
    printHeader(cityName, "Linear Search", "Array", label);

    int matches = 0, comps = 0;
    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < size; i++) {
        comps++;
        if (isMatch(criteria, arr[i].age, arr[i].mode, arr[i].distance,
                    minAge, maxAge, targetMode, threshold)) {
            matches++;
            printRow(matches, arr[i].ID, arr[i].age, arr[i].mode,
                     arr[i].distance, arr[i].carbon, arr[i].avg);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(end - start).count();
    printFooter(matches, comps, dur);

    if (logCount < 20)
        searchLog[logCount++] = {"Array", "Linear", label, matches, comps, dur};
}


// Linear Search — Linked List | O(N) time, O(1) space | traverses nextAddress pointers
void linearSearchList(linkedList& list, int criteria,
                      int minAge, int maxAge, string targetMode,
                      double threshold, string cityName) {

    string label = criteriaLabel(criteria, minAge, maxAge, targetMode, threshold);
    printHeader(cityName, "Linear Search", "Linked List", label);

    int matches = 0, comps = 0;
    auto start = chrono::high_resolution_clock::now();

    // traverse all nodes from head to end
    listResidents* curr = list.getHead();
    while (curr != nullptr) {
        comps++;
        if (isMatch(criteria, curr->age, curr->mode, curr->distance,
                    minAge, maxAge, targetMode, threshold)) {
            matches++;
            printRow(matches, curr->ID, curr->age, curr->mode,
                     curr->distance, curr->carbon, curr->avg);
        }
        curr = curr->nextAddress;
    }

    auto end = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(end - start).count();
    printFooter(matches, comps, dur);

    if (logCount < 20)
        searchLog[logCount++] = {"Linked List", "Linear", label, matches, comps, dur};
}


// Binary Search — Array (Age) | O(log N) search + O(N log N) pre-sort | O(N) space
// Sorts a temp copy by age, then finds lower and upper bounds via binary search
void binarySearchArrayAge(Residents* arr, int size,
                          int minAge, int maxAge, string cityName) {

    string label = "Age " + to_string(minAge) + "-" + to_string(maxAge);

    // copy original array so pre-sort does not disturb data for subsequent searches
    Residents* temp = new Residents[size];
    for (int i = 0; i < size; i++) temp[i] = arr[i];

    // sort the copy by age (original array is preserved)
    cout << "\n  [Pre-sorting by Age using Merge Sort...]" << endl;
    auto sortStart = chrono::high_resolution_clock::now();
    mergeArray(temp, 0, size - 1, "Age");
    auto sortEnd = chrono::high_resolution_clock::now();
    long long sortTime = chrono::duration_cast<chrono::microseconds>(sortEnd - sortStart).count();
    cout << "  Sort completed in " << sortTime << " us" << endl;

    printHeader(cityName, "Binary Search", "Array (Sorted)", label);

    int matches = 0, comps = 0;
    auto start = chrono::high_resolution_clock::now();

    // find lower bound: first index where age >= minAge
    int lo = 0, hi = size - 1, lower = size;
    while (lo <= hi) {
        comps++;
        int mid = lo + (hi - lo) / 2;  // avoids integer overflow vs (lo+hi)/2
        if (temp[mid].age >= minAge) { lower = mid; hi = mid - 1; }
        else lo = mid + 1;
    }

    // find upper bound: last index where age <= maxAge
    lo = 0; hi = size - 1;
    int upper = -1;
    while (lo <= hi) {
        comps++;
        int mid = lo + (hi - lo) / 2;
        if (temp[mid].age <= maxAge) { upper = mid; lo = mid + 1; }
        else hi = mid - 1;
    }

    // print all residents within the located range
    for (int i = lower; i <= upper && lower <= upper; i++) {
        matches++;
        printRow(matches, temp[i].ID, temp[i].age, temp[i].mode,
                 temp[i].distance, temp[i].carbon, temp[i].avg);
    }

    auto end = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(end - start).count();
    printFooter(matches, comps, dur);
    cout << "  Sort cost: " << sortTime << " us | Binary search: ~"
         << comps << " comparisons (log2(" << size << ")="
         << (int)log2(size)+1 << ")" << endl;

    delete[] temp;  // free the temporary copy

    if (logCount < 20)
        searchLog[logCount++] = {"Array(Sorted)", "Binary", label, matches, comps, dur};
}


// Binary Search — Array (Distance) | O(log N) search + O(N log N) pre-sort | O(N) space
// Sorts a temp copy by distance, then finds the first index exceeding the threshold
void binarySearchArrayDist(Residents* arr, int size,
                           double threshold, string cityName) {

    string label = "Distance > " + to_string((int)threshold) + " km";

    // copy original array so pre-sort does not disturb data for subsequent searches
    Residents* temp = new Residents[size];
    for (int i = 0; i < size; i++) temp[i] = arr[i];

    cout << "\n  [Pre-sorting by Distance using Merge Sort...]" << endl;
    auto sortStart = chrono::high_resolution_clock::now();
    mergeArray(temp, 0, size - 1, "Distance");
    auto sortEnd = chrono::high_resolution_clock::now();
    long long sortTime = chrono::duration_cast<chrono::microseconds>(sortEnd - sortStart).count();
    cout << "  Sort completed in " << sortTime << " us" << endl;

    printHeader(cityName, "Binary Search", "Array (Sorted)", label);

    int matches = 0, comps = 0;
    auto start = chrono::high_resolution_clock::now();

    // find first index where distance exceeds the threshold (lower bound)
    int lo = 0, hi = size - 1, boundary = size;
    while (lo <= hi) {
        comps++;
        int mid = lo + (hi - lo) / 2;
        if (temp[mid].distance > threshold) { boundary = mid; hi = mid - 1; }
        else lo = mid + 1;
    }

    // all elements from boundary to end exceed the threshold
    for (int i = boundary; i < size; i++) {
        matches++;
        printRow(matches, temp[i].ID, temp[i].age, temp[i].mode,
                 temp[i].distance, temp[i].carbon, temp[i].avg);
    }

    auto end = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(end - start).count();
    printFooter(matches, comps, dur);

    cout << "  Sort cost: " << sortTime << " us" << endl;
    cout << "  Linear Search would need: " << size << " comparisons" << endl;
    cout << "  Binary Search used:       " << comps
         << " comparisons (log2(" << size << ") = "
         << (int)log2(size)+1 << ")" << endl;
    cout << "  Binary Search is ~" << (comps > 0 ? size/comps : 0)
         << "x fewer comparisons than Linear" << endl;

    delete[] temp;  // free the temporary copy

    if (logCount < 20)
        searchLog[logCount++] = {"Array(Sorted)", "Binary", label, matches, comps, dur};
}


// Prints side-by-side performance summary of all logged search experiments
void printComparisonSummary(string cityName, int size) {
    cout << "\n" << string(80, '=') << endl;
    cout << "  PERFORMANCE COMPARISON | City " << cityName
         << " | " << size << " records" << endl;
    cout << string(80, '=') << endl;
    cout << left << setw(14) << "Structure" << setw(10) << "Algorithm"
         << setw(26) << "Criteria" << setw(10) << "Matches"
         << setw(12) << "Comparisons" << setw(8) << "Time(us)" << endl;
    cout << string(80, '-') << endl;
    for (int i = 0; i < logCount; i++) {
        cout << left << setw(14) << searchLog[i].structure
             << setw(10) << searchLog[i].algorithm
             << setw(26) << searchLog[i].criteria
             << setw(10) << searchLog[i].matches
             << setw(12) << searchLog[i].comparisons
             << setw(8)  << searchLog[i].timeUs << endl;
    }

    // --- Memory Usage Analysis ---
    cout << string(80, '-') << endl;
    cout << "  MEMORY USAGE (both structures loaded simultaneously):" << endl;

    int arrBytes  = size * (int)sizeof(Residents);
    int listBytes = size * (int)sizeof(listResidents);
    int ptrBytes  = size * (int)sizeof(listResidents*);
    int combined  = arrBytes + listBytes;

    cout << "  Array      : " << size << " x " << sizeof(Residents)
         << " bytes = " << arrBytes << " bytes" << endl;
    cout << "               Contiguous layout, no pointer per element" << endl;
    cout << "  Linked List: " << size << " x " << sizeof(listResidents)
         << " bytes = " << listBytes << " bytes" << endl;
    cout << "               " << ptrBytes << " bytes used for next pointers alone" << endl;
    cout << "  Combined total in RAM: " << combined << " bytes" << endl;
    cout << "  Note: Binary Search adds a temp O(N) copy ("
         << arrBytes << " bytes) during sort." << endl;

    cout << string(80, '-') << endl;
    cout << "  KEY INSIGHTS:" << endl;
    cout << "  1. Binary Search O(log N) is faster than Linear O(N)," << endl;
    cout << "     but requires the data to be sorted first." << endl;
    cout << "  2. Sorting costs O(N log N) — for one-off queries," << endl;
    cout << "     Linear Search (no sort needed) can be faster overall." << endl;
    cout << "  3. Binary Search on Linked Lists costs O(N log N):" << endl;
    cout << "     no midpoint access -> no advantage over Linear O(N)." << endl;
    cout << "  4. Array Linear Search is faster than Linked List Linear" << endl;
    cout << "     due to better cache locality (contiguous memory)." << endl;
    cout << "  5. Optimal: sort once, then Binary Search for repeat queries." << endl;
    cout << string(80, '=') << endl;
}


// Search menu — user selects criteria, algorithm, and structure; logs each run for comparison
void searchMenu(Container& city) {
    logCount = 0;  // reset experiment log
    bool again = true;

    while (again) {
        cout << "\nSearch by:" << endl;
        cout << "1. Age Group" << endl;
        cout << "2. Mode of Transport" << endl;
        cout << "3. Daily Distance Threshold" << endl;
        cout << "4. Combined: Age Group + Distance (advanced)" << endl;
        int criteria = getInput(1, 4);

        // binary search requires a sortable numeric field (not string/combined criteria)
        cout << "\nAlgorithm:" << endl;
        cout << "1. Linear Search (unsorted data)" << endl;
        bool canBinary = (criteria == 1 || criteria == 3);
        if (canBinary)
            cout << "2. Binary Search (sorts first, Array only)" << endl;
        else
            cout << "  (Binary Search unavailable: not applicable to "
                 << (criteria == 2 ? "categorical string fields" : "combined multi-field criteria")
                 << ")" << endl;
        int algo = getInput(1, canBinary ? 2 : 1);

        // select data structure
        string structure = structureSelect();

        // gather the specific search parameters based on criteria
        int minAge = 0, maxAge = 0;
        string targetMode = "";
        double threshold = 0;

        if (criteria == 1 || criteria == 4) {
            // criteria 1 and 4 both need age group selection
            cout << "\nAge Group:" << endl;
            for (int i = 0; i < 5; i++)
                cout << i+1 << ". " << AGE_LABELS[i] << endl;
            int sel = getInput(1, 5);
            minAge = AGE_MIN[sel-1];
            maxAge = AGE_MAX[sel-1];
        }
        if (criteria == 2) {
            cout << "\nTransport Mode:" << endl;
            for (int i = 0; i < 6; i++)
                cout << i+1 << ". " << MODES[i] << endl;
            targetMode = MODES[getInput(1, 6) - 1];
        }
        if (criteria == 3 || criteria == 4) {
            // criteria 3 and 4 both need distance threshold
            cout << "\nDistance threshold (finds residents > this value in km):" << endl;
            double val;
            cout << ">>>   ";
            cin >> val;
            threshold = val;
        }

        if (algo == 1) {
            if (structure == "Array")
                linearSearchArray(city.array, city.size, criteria,
                                  minAge, maxAge, targetMode, threshold, city.name);
            else
                linearSearchList(city.list, criteria,
                                 minAge, maxAge, targetMode, threshold, city.name);
        } else {
            // Binary search — only works on array
            if (structure != "Array") {
                cout << "\n  Binary Search cannot work on Linked Lists." << endl;
                cout << "  (No O(1) random access to midpoint)" << endl;
                cout << "  Running Linear Search instead.\n" << endl;
                linearSearchList(city.list, criteria,
                                 minAge, maxAge, targetMode, threshold, city.name);
            } else if (criteria == 1)
                binarySearchArrayAge(city.array, city.size, minAge, maxAge, city.name);
            else
                binarySearchArrayDist(city.array, city.size, threshold, city.name);
        }

        cout << "\nRun another search on City " << city.name
             << "? (1=Yes, 0=No to return to main menu): ";
        int cont; cin >> cont;
        if (cont != 1) again = false;
    }

    // show side-by-side comparison of all experiments from this session
    if (logCount > 0)
        printComparisonSummary(city.name, city.size);
}
