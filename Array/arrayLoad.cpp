#include <iostream>
#include <fstream>
#include <sstream>
#include "../residentsArray.h"

using namespace std;

int loadCSV(string path, Residents array[]) {
    ifstream file(path);
    string line;
    getline(file,line);

    int index = 0;
    while (getline(file,line)) {       // Parsing  lines into array
        stringstream lstream(line); 
        string tempData[6];

        for (int i = 0; i<6; i++) {
            getline(lstream,tempData[i],',');
        }
        array[index].ID = tempData[0];
        array[index].age = stoi(tempData[1]);
        array[index].mode = tempData[2];
        array[index].distance = stod(tempData[3]);
        array[index].carbon = stod(tempData[4]);
        array[index].avg = stod(tempData[5]);
        index++;
    };
    return 0;
}

