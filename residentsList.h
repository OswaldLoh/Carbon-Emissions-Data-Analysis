#ifndef LINKED_LIST
#define LINKED_LIST

#include <iostream>

using namespace std;

const string FILE_A_PATH = "../Database/dataset1-cityA.csv";
const string FILE_B_PATH = "../Database/dataset2-cityB.csv";
const string FILE_C_PATH = "../Database/dataset3-cityC.csv";

// Each node in linked list follow this structure
struct Residents {
    string ID;
    int age;
    string mode;
    double distance;
    double carbon;
    double avg;
    Residents* nextAddress;     // Points the memory address for next node into "nextAddress"
};


class linkedList {
    private:
        Residents* headAddress;
    public:
        linkedList();
        Residents* getHeadAddress();
        void insertNode(string ID, int age, string mode, double distance, double carbon, double avg);
};

void loadCSV(string filepath, linkedList& List);

#endif


