#ifndef HEADER
#define HEADER

#include <iostream>
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
        int getSize();
        listResidents* getHead();
        void setHead(listResidents* newAddress);
        void insertNode(string ID, int age, string mode, double distance, double carbon, double avg);
};

// Container for all cities and their respective linked list and arrays
struct Array {
    string name;
    linkedList list;
    Residents* array;
    int size;
};

// Functions

void loadCSVList(string filepath, linkedList& List);
int loadCSVArray(string path, Residents array[]);
string algoSelect();
string structureSelect();
string sortBy();
Array citySelection(Array* arrays, int size);
void sorting(string structure, string algo, Array city, string category);
void sortBubbleArray(Residents *array, int size, string category);
void categorizeArray(Residents array[], int size);
void categorizeList(linkedList& list);
void sortBubbleList(linkedList& list, string category);
void printArray(Residents* array, int size);
void printList(listResidents* head);

#endif


