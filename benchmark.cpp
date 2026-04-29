#include <iostream>
#include <iomanip>
#include <limits>
#include <numeric>
#include "residents.h"
#include <string>

using namespace std;


// ─────────────────────────────────────────────────────────────────────────────
//  Helper: restore dataset to a requested state before each run
//  State options match the rest of the codebase:
//    "Sorted"   → best-case   (pre-sort ascending so algorithm sees sorted data)
//    "Reverse"  → worst-case  (pre-sort descending)
//    "Unsorted" → average-case (reload fresh from CSV, no pre-sort)
// ─────────────────────────────────────────────────────────────────────────────
static void reloadArrayState(Residents* array, int size, const string& path, const string& state) {
    loadCSVArray(path, array);             // always start from raw CSV
    if (state == "Sorted") {
        sortBubbleArray(array, size, "Age", "Sorted");
    } else if (state == "Reverse") {
        sortBubbleArray(array, size, "Age", "Reverse");
    }
    // "Unsorted" -> raw CSV order, nothing extra needed
}

static void reloadListState(linkedList& list, const string& path, const string& state) {
    list.clear();
    loadCSVList(path, list);               // always start from raw CSV
    if (state == "Sorted") {
        // Use merge sort for pre-sorting: only redirects pointers (no repeated swaps),
        // keeping node memory layout cache-friendly for the benchmark algorithm.
        listResidents* sorted = mergeListSort(list.getHead(), "Age", "Sorted");
        list.setHead(sorted);
    } else if (state == "Reverse") {
        listResidents* sorted = mergeListSort(list.getHead(), "Age", "Reverse");
        list.setHead(sorted);
    }
}

static string benchAlgoSelect() {
    int sel;
    bool valid = false;
    cout << "\n  Select sorting algorithm:" << endl;
    cout << "  1. Bubble Sort" << endl;
    cout << "  2. Insertion Sort" << endl;
    cout << "  3. Merge Sort" << endl;
    while (!valid) {
        cout << ">>> ";
        cin >> sel;
        if (cin.fail() || sel < 1 || sel > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Invalid input. Please try again." << endl;
        } else {
            valid = true;
        }
    }
    switch (sel) {
        case 1: return "Bubble";
        case 2: return "Insert";
        default: return "Merge";
    }
}

static string benchStructureSelect() {
    int sel;
    bool valid = false;
    cout << "\n  Select data structure:" << endl;
    cout << "  1. Array" << endl;
    cout << "  2. Linked List" << endl;
    while (!valid) {
        cout << ">>> ";
        cin >> sel;
        if (cin.fail() || sel < 1 || sel > 2) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Invalid input. Please try again." << endl;
        } else {
            valid = true;
        }
    }
    return (sel == 1) ? "Array" : "LinkedList";
}

static string benchCaseSelect() {
    int sel;
    bool valid = false;
    cout << "\n  Select benchmark case:" << endl;
    cout << "  1. Best Case   (Sorted)" << endl;
    cout << "  2. Average Case (Unsorted)" << endl;
    cout << "  3. Worst Case  (Reverse)" << endl;
    while (!valid) {
        cout << ">>> ";
        cin >> sel;
        if (cin.fail() || sel < 1 || sel > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Invalid input. Please try again." << endl;
        } else {
            valid = true;
        }
    }
    switch (sel) {
        case 1: return "Sorted";
        case 2: return "Unsorted";
        default: return "Reverse";
    }
}

// Simple city descriptor used only inside benchmark
struct BenchCity { string name; string path; int size; };

static BenchCity benchCitySelect() {
    int sel;
    bool valid = false;
    cout << "\n  Select city:" << endl;
    cout << "  1. City A (" << FILE_A_SIZE << " records)" << endl;
    cout << "  2. City B (" << FILE_B_SIZE << " records)" << endl;
    cout << "  3. City C (" << FILE_C_SIZE << " records)" << endl;
    while (!valid) {
        cout << ">>> ";
        cin >> sel;
        if (cin.fail() || sel < 1 || sel > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  Invalid input. Please try again." << endl;
        } else {
            valid = true;
        }
    }
    switch (sel) {
        case 1: return {"A", FILE_A_PATH, FILE_A_SIZE};
        case 2: return {"B", FILE_B_PATH, FILE_B_SIZE};
        default: return {"C", FILE_C_PATH, FILE_C_SIZE};
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  Main benchmark entry point
//  Fixed: sort by Age, 100 runs
// ─────────────────────────────────────────────────────────────────────────────
void runBenchmark() {
    const int RUNS        = 100;
    const string CATEGORY = "Age";      // fixed

    cout << "\n==========================================" << endl;
    cout << "       SORTING BENCHMARK MODE             " << endl;
    cout << "   Sort by Age  |  100 runs              " << endl;
    cout << "==========================================" << endl;

    BenchCity city = benchCitySelect();
    string algo      = benchAlgoSelect();
    string structure = benchStructureSelect();
    string state     = benchCaseSelect();

    string benchState = (state == "Reverse") ? "Sorted" : state;

    string caseLabel;
    if      (state == "Sorted")   caseLabel = "Best Case (Sorted input)";
    else if (state == "Reverse")  caseLabel = "Worst Case (Reverse input)";
    else                          caseLabel = "Average Case (Unsorted input)";

    cout << "\n------------------------------------------" << endl;
    cout << left << setw(6) << "#" << setw(20) << "Execution Time" << endl;
    cout << "------------------------------------------" << endl;

    Residents* arrayA = new Residents[city.size];
    linkedList listA;
    long long totalTime = 0;

    for (int run = 1; run <= RUNS; run++) {
        if (structure == "Array") {
            reloadArrayState(arrayA, city.size, city.path, state);
        } else {
            reloadListState(listA, city.path, state);
        }

        int elapsed = 0;

        if (structure == "Array") {
            if (algo == "Bubble") {
                elapsed = measureTime([&]() {
                    sortBubbleArray(arrayA, city.size, CATEGORY, benchState);
                });
            } else if (algo == "Insert") {
                elapsed = measureTime([&]() {
                    sortInsertArray(arrayA, city.size, CATEGORY, benchState);
                });
            } else {
                elapsed = measureTime([&]() {
                    mergeArray(arrayA, 0, city.size - 1, CATEGORY, benchState);
                });
            }
        } else {
            if (algo == "Bubble") {
                elapsed = measureTime([&]() {
                    sortBubbleList(listA, CATEGORY, benchState);
                });
            } else if (algo == "Insert") {
                elapsed = measureTime([&]() {
                    sortInsertList(listA, CATEGORY, benchState);
                });
            } else {
                elapsed = measureTime([&]() {
                    listResidents* sorted = mergeListSort(listA.getHead(), CATEGORY, benchState);
                    listA.setHead(sorted);
                });
            }
        }

        totalTime += elapsed;
        cout << left << setw(6) << run << (to_string(elapsed) + " us") << endl;
    }

    double average = static_cast<double>(totalTime) / RUNS;
    cout << "------------------------------------------" << endl;
    cout << left << setw(6) << "AVG" << fixed << setprecision(2) << average << " us" << endl;
    cout << "------------------------------------------" << endl;
    cout << "  Config  : " << algo << " Sort | " << structure
         << " | City " << city.name << " | Sort by " << CATEGORY << endl;
    cout << "  Case    : " << caseLabel << endl;
    cout << "  Total   : " << totalTime << " us  |  Runs : " << RUNS << endl;
    cout << "  Average : " << fixed << setprecision(2) << average << " microseconds" << endl;
    cout << "==========================================\n" << endl;

    listA.clear();
    delete[] arrayA;
}
