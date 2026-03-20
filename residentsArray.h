#include <iostream>
using namespace std;

// Array Size
const int FILE_A_SIZE = 200;        
const int FILE_B_SIZE = 178;
const int FILE_C_SIZE = 122;

// Filepath
const string FILE_A_PATH = "../Database/dataset1-cityA.csv";
const string FILE_B_PATH = "../Database/dataset2-cityB.csv";
const string FILE_C_PATH = "../Database/dataset3-cityC.csv";

// Defining struct for resident
struct Residents {                  
    string ID;
    int age;
    string mode;
    double distance;
    double carbon;
    double avg;
};

// Functions
int loadCSV(string path, Residents dataset[]);

