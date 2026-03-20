#include <iostream>
#include <fstream>
#include <sstream>
#include "residents.h"

using namespace std;

void loadCSVList(string filepath, linkedList& List) {
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
        List.insertNode(tempData[0],stoi(tempData[1]),tempData[2],stod(tempData[3]),stod(tempData[4]),stod(tempData[5]));
    }
}