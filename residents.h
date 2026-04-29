#ifndef HEADER
#define HEADER

#include <iostream>
#include <chrono>
#include <functional>

using namespace std;

// Array Size
const int FILE_A_SIZE = 200;        
const int FILE_B_SIZE = 178;
const int FILE_C_SIZE = 122;

// Filepath
const string FILE_A_PATH = "Database/dataset1-cityA.csv";
const string FILE_B_PATH = "Database/dataset2-cityB.csv";
const string FILE_C_PATH = "Database/dataset3-cityC.csv";


// Each element in array
struct Residents {                  
    string ID;
    int age;
    string mode;
    double distance;
    double carbon;
    double avg;
};

// Each node in linked list follow this structure
struct listResidents {
    string ID;
    int age;
    string mode;
    double distance;
    double carbon;
    double avg;
    listResidents* nextAddress;     // Points the memory address for next node into "nextAddress"
};

// Class declaration for Linked List
class linkedList {
    private:
        listResidents* headAddress;
    public:
        linkedList();               // Constructor
        void clear();               // Frees all nodes and resets the list
        int getSize();
        listResidents* getHead();
        void setHead(listResidents* newAddress);
        void insertNode(string ID, int age, string mode, double distance, double carbon, double avg);

};

// Container for all cities and their respective linked list and arrays
struct Container {
    string name;
    linkedList list;
    Residents* array;
    int size;
};

// Functions


// File Handling
void loadCSVList(string filepath, linkedList& List);
int loadCSVArray(string path, Residents array[]);
void fileOutput(Container city, string category, string structure);

// Menu Selections
string stateSelect();
string algoSelect();
string structureSelect();
string sortBy();
Container citySelection(Container* arrays, int size);

// Printing Functions
void printArray(Residents* array, int size);
void printList(listResidents* head);

// Time functions
int measureTime(std::function<void()> func);
string getTimestamp();

// Sorting Functions
void sorting(string structure, string algo, Container city, string category, string state);
void sortBubbleArray(Residents *array, int size, string category, string state);
void sortBubbleList(linkedList& list, string category, string state);
void sortInsertArray(Residents* array, int size, string category, string state);
void sortInsertList(linkedList& list, string category, string state);
void mergeArray(Residents* array, int indexL, int indexR, string category, string state);
void mergeSort(Residents* array, int indexL, int indexM, int indexR, string category, string state);
listResidents* merge(listResidents* first, listResidents* second, const string& category);
listResidents* split(listResidents* head);
listResidents* mergeListSort(listResidents* head, const string& category, string state);

// Categorization
void categorizeArray(Residents array[], int size);
void categorizeList(linkedList& list);

// Searching functions
void searchMenu(Container& city);
void linearSearchArray(Residents* arr, int size, int criteria, int minAge, int maxAge, string targetMode, double threshold, string cityName);
void linearSearchList(linkedList& list, int criteria, int minAge, int maxAge, string targetMode, double threshold, string cityName);
void binarySearchArrayAge(Residents* arr, int size, int minAge, int maxAge, string cityName);
void binarySearchArrayDist(Residents* arr, int size, double threshold, string cityName);

// Carbon Analysis functions
void carbonAnalysis(Container* cities, int numCities);
void carbonByModeArray(Residents* array, int size, const string& cityName);
void carbonByModeList(linkedList& list, const string& cityName);
void carbonByAgeGroupArray(Residents* array, int size, const string& cityName);
void carbonByAgeGroupList(linkedList& list, const string& cityName);
void crossCityComparison(Container* cities, int numCities, const string& structure);

#endif


