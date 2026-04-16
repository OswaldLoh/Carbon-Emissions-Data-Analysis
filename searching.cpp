/*
    Searching Experiments (Question 7)

    Algorithms:
    - Linear Search: O(N) — scans every element, works on unsorted data
    - Binary Search: O(log N) — halves search space each step, needs sorted data

    Why Binary Search cannot work on Linked Lists:
      Binary Search requires O(1) random access to jump to the middle element.
      In a linked list, reaching the midpoint requires O(N/2) pointer traversal.
      This must be repeated at every level, giving O(N log N) total — which is
      worse than just doing Linear Search at O(N). So it's only used on arrays.

    Reuses: merge() from sorting.cpp, structureSelect() from util.cpp,
            same age group definitions as categorization.cpp
*/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
#include <iostream>
#include <iomanip>
#include <chrono>
#include <cmath>
#include <limits>
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
    // criteria 4: combined condition — age group AND distance threshold
    // this shows advanced application of searching with multiple filters
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
    cout << "\n" << string(80, '=') << endl;
    cout << "  City " << city << " | " << algo << " | " << structure << endl;
    cout << "  Criteria: " << criteria << endl;
    cout << string(80, '=') << endl;
    cout << left << setw(6) << "No." << setw(8) << "ID" << setw(6) << "Age"
         << setw(12) << "Transport" << setw(10) << "Dist(km)"
         << setw(10) << "CO2/km" << setw(8) << "Days"
         << setw(10) << "Emission" << endl;
    cout << string(80, '-') << endl;
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

void printFooter(int matches, int comps, long long us) {
    cout << string(80, '-') << endl;
    cout << "  Matches: " << matches << "  |  Comparisons: " << comps
         << "  |  Time: " << us << " us" << endl;
    cout << string(80, '=') << endl;
}


// ==============================================================
//  LINEAR SEARCH — ARRAY
//  Time Complexity: O(N) — must check every element once
//  Space Complexity: O(1) — no extra memory needed
//  Works on unsorted data, which is the main advantage over binary search
// ==============================================================
void linearSearchArray(Residents* arr, int size, int criteria,
                       int minAge, int maxAge, string targetMode,
                       double threshold, string cityName) {

    string label = criteriaLabel(criteria, minAge, maxAge, targetMode, threshold);
    printHeader(cityName, "Linear Search", "Array", label);

    int matches = 0, comps = 0;
    auto start = chrono::high_resolution_clock::now();

    // iterate through every array element — O(N)
    for (int i = 0; i < size; i++) {
        comps++;  // count each comparison for performance analysis
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


// ==============================================================
//  LINEAR SEARCH — LINKED LIST
//  Time Complexity: O(N) — same as array, traverse every node
//  Space Complexity: O(1)
//  Key difference: array uses index arr[i] with O(1) random access,
//  linked list follows nextAddress pointers sequentially.
//  In practice, linked list is often slightly slower because nodes
//  are scattered in heap memory (poor cache locality), while array
//  elements sit next to each other (good cache locality).
// ==============================================================
void linearSearchList(linkedList& list, int criteria,
                      int minAge, int maxAge, string targetMode,
                      double threshold, string cityName) {

    string label = criteriaLabel(criteria, minAge, maxAge, targetMode, threshold);
    printHeader(cityName, "Linear Search", "Linked List", label);

    int matches = 0, comps = 0;
    auto start = chrono::high_resolution_clock::now();

    // follow the chain of nextAddress pointers from head to end
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


// ==============================================================
//  BINARY SEARCH — ARRAY (Age Group)
//  Time Complexity: O(log N) for the search + O(N log N) for pre-sort
//  Space Complexity: O(N) due to merge sort's temporary arrays
//
//  How it works:
//  1. Sort the array by age using merge sort (reuses sorting.cpp)
//  2. Binary search for the FIRST index where age >= minAge (lower bound)
//  3. Binary search for the LAST index where age <= maxAge (upper bound)
//  4. Everything between lower and upper bound is a match
//
//  For N=200, binary search needs ~8 comparisons (log2(200))
//  vs 200 comparisons for linear search — massive improvement
// ==============================================================
void binarySearchArrayAge(Residents* arr, int size,
                          int minAge, int maxAge, string cityName) {

    string label = "Age " + to_string(minAge) + "-" + to_string(maxAge);

    // step 1: sort by age first — reusing mergeArray() from sorting.cpp
    cout << "\n  [Pre-sorting by Age using Merge Sort...]" << endl;
    auto sortStart = chrono::high_resolution_clock::now();
    mergeArray(arr, 0, size - 1, "Age");
    auto sortEnd = chrono::high_resolution_clock::now();
    long long sortTime = chrono::duration_cast<chrono::microseconds>(sortEnd - sortStart).count();
    cout << "  Sort completed in " << sortTime << " us" << endl;

    printHeader(cityName, "Binary Search", "Array (Sorted)", label);

    int matches = 0, comps = 0;
    auto start = chrono::high_resolution_clock::now();

    // step 2: find lower bound — first index where age >= minAge
    int lo = 0, hi = size - 1, lower = size;
    while (lo <= hi) {
        comps++;
        int mid = lo + (hi - lo) / 2;  // avoids integer overflow vs (lo+hi)/2
        if (arr[mid].age >= minAge) { lower = mid; hi = mid - 1; }
        else lo = mid + 1;
    }

    // step 3: find upper bound — last index where age <= maxAge
    lo = 0; hi = size - 1;
    int upper = -1;
    while (lo <= hi) {
        comps++;
        int mid = lo + (hi - lo) / 2;
        if (arr[mid].age <= maxAge) { upper = mid; lo = mid + 1; }
        else hi = mid - 1;
    }

    // step 4: print all residents in the found range
    for (int i = lower; i <= upper && lower <= upper; i++) {
        matches++;
        printRow(matches, arr[i].ID, arr[i].age, arr[i].mode,
                 arr[i].distance, arr[i].carbon, arr[i].avg);
    }

    auto end = chrono::high_resolution_clock::now();
    long long dur = chrono::duration_cast<chrono::microseconds>(end - start).count();
    printFooter(matches, comps, dur);
    cout << "  Sort cost: " << sortTime << " us | Binary search: ~"
         << comps << " comparisons (log2(" << size << ")="
         << (int)log2(size)+1 << ")" << endl;

    if (logCount < 10)
        searchLog[logCount++] = {"Array(Sorted)", "Binary", label, matches, comps, dur};
}


// ==============================================================
//  BINARY SEARCH — ARRAY (Distance Threshold)
//  Same concept as age binary search, but finds a single boundary:
//  the first index where distance > threshold.
//  Everything from that index to the end of the sorted array matches.
// ==============================================================
void binarySearchArrayDist(Residents* arr, int size,
                           double threshold, string cityName) {

    string label = "Distance > " + to_string((int)threshold) + " km";

    cout << "\n  [Pre-sorting by Distance using Merge Sort...]" << endl;
    auto sortStart = chrono::high_resolution_clock::now();
    mergeArray(arr, 0, size - 1, "Distance");
    auto sortEnd = chrono::high_resolution_clock::now();
    long long sortTime = chrono::duration_cast<chrono::microseconds>(sortEnd - sortStart).count();
    cout << "  Sort completed in " << sortTime << " us" << endl;

    printHeader(cityName, "Binary Search", "Array (Sorted)", label);

    int matches = 0, comps = 0;
    auto start = chrono::high_resolution_clock::now();

    // find the first index where distance > threshold
    int lo = 0, hi = size - 1, boundary = size;
    while (lo <= hi) {
        comps++;
        int mid = lo + (hi - lo) / 2;
        if (arr[mid].distance > threshold) { boundary = mid; hi = mid - 1; }
        else lo = mid + 1;
    }

    // everything from boundary onwards exceeds the threshold
    for (int i = boundary; i < size; i++) {
        matches++;
        printRow(matches, arr[i].ID, arr[i].age, arr[i].mode,
                 arr[i].distance, arr[i].carbon, arr[i].avg);
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

    if (logCount < 20)
        searchLog[logCount++] = {"Array(Sorted)", "Binary", label, matches, comps, dur};
}


// ==============================================================
//  Performance comparison table — printed after all experiments
//  Shows side-by-side how each algorithm/structure performed
// ==============================================================
void printComparisonSummary(string cityName, int size) {
    cout << "\n" << string(90, '=') << endl;
    cout << "  PERFORMANCE COMPARISON | City " << cityName
         << " | " << size << " records" << endl;
    cout << string(90, '=') << endl;
    cout << left << setw(16) << "Structure" << setw(12) << "Algorithm"
         << setw(28) << "Criteria" << setw(10) << "Matches"
         << setw(14) << "Comparisons" << setw(10) << "Time(us)" << endl;
    cout << string(90, '-') << endl;
    for (int i = 0; i < logCount; i++) {
        cout << left << setw(16) << searchLog[i].structure
             << setw(12) << searchLog[i].algorithm
             << setw(28) << searchLog[i].criteria
             << setw(10) << searchLog[i].matches
             << setw(14) << searchLog[i].comparisons
             << setw(10) << searchLog[i].timeUs << endl;
    }

    // --- Memory Usage Analysis ---
    cout << string(90, '-') << endl;
    cout << "  MEMORY USAGE ANALYSIS:" << endl;
    cout << "  Array: " << size << " x " << sizeof(Residents)
         << " bytes = " << size * sizeof(Residents) << " bytes total" << endl;
    cout << "    -> Stored contiguously in memory (good cache locality)" << endl;
    cout << "    -> No extra overhead per element" << endl;
    cout << "  Linked List: " << size << " x " << sizeof(listResidents)
         << " bytes = " << size * sizeof(listResidents) << " bytes total" << endl;
    cout << "    -> Each node has an extra pointer (" << sizeof(listResidents*)
         << " bytes) for nextAddress" << endl;
    cout << "    -> Nodes scattered in heap memory (poor cache locality)" << endl;
    cout << "    -> Extra overhead: " << size * sizeof(listResidents*)
         << " bytes just for pointers" << endl;

    // --- Key Insights ---
    cout << string(90, '-') << endl;
    cout << "  KEY INSIGHTS:" << endl;
    cout << "  1. Binary Search (O(log N)) is much faster than Linear (O(N))" << endl;
    cout << "     but ONLY works if data is already sorted." << endl;
    cout << "  2. Sorting costs O(N log N), so for a ONE-TIME search on" << endl;
    cout << "     small datasets, Linear Search may actually be faster" << endl;
    cout << "     overall (no sort overhead needed)." << endl;
    cout << "  3. Binary Search CANNOT work on Linked Lists because" << endl;
    cout << "     reaching the midpoint needs O(N/2) pointer traversal," << endl;
    cout << "     making total cost O(N log N) — worse than Linear O(N)." << endl;
    cout << "  4. Array Linear Search is often faster than Linked List" << endl;
    cout << "     Linear Search (same O(N)) because arrays have better" << endl;
    cout << "     cache locality — CPU prefetches adjacent elements." << endl;
    cout << "  5. For repeated searches on the same data, sorting once" << endl;
    cout << "     then using Binary Search is the best strategy." << endl;
    cout << string(90, '=') << endl;
}


// ==============================================================
//  SEARCH MENU — called from main.cpp case 4
//  Lets user pick criteria, algorithm, and data structure,
//  then runs the search and logs results for comparison
// ==============================================================
void searchMenu(Array& city) {
    logCount = 0;  // reset experiment log
    bool again = true;

    while (again) {
        // pick what to search by
        cout << "\nSearch by:" << endl;
        cout << "1. Age Group" << endl;
        cout << "2. Mode of Transport" << endl;
        cout << "3. Daily Distance Threshold" << endl;
        cout << "4. Combined: Age Group + Distance (advanced)" << endl;
        int criteria = getInput(1, 4);

        // pick search algorithm
        // binary search only works for single numeric field, not combined or string
        cout << "\nAlgorithm:" << endl;
        cout << "1. Linear Search (unsorted data)" << endl;
        bool canBinary = (criteria == 1 || criteria == 3);
        if (canBinary)
            cout << "2. Binary Search (sorts first, Array only)" << endl;
        int algo = getInput(1, canBinary ? 2 : 1);

        // pick data structure — reuses structureSelect() from util.cpp
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

        // execute the selected search
        if (algo == 1) {
            // Linear search works on both array and linked list
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

        cout << "\nRun another experiment? (1=Yes, 0=No): ";
        int cont; cin >> cont;
        if (cont != 1) again = false;
    }

    // show side-by-side comparison of all experiments from this session
    if (logCount > 0)
        printComparisonSummary(city.name, city.size);
}
