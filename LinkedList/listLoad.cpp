#include <iostream>
#include <fstream>
#include <sstream>
#include "../residentsList.h"

using namespace std;

void loadCSV(string filepath, linkedList List) {
    Residents* head = List.getHeadAddress();
    ifstream file(filepath);
    string line;
    getline(file,line);

    int index = 0;
    while (getline(file,line)) {       // Parsing  lines into array
        stringstream lstream(line); 
        string tempData[6];

        for (int i = 0; i<6; i++) {
            getline(lstream,tempData[i],',');
        }
    }
}