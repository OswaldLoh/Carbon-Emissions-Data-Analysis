#include <iostream>
#include <fstream>
#include <sstream>
#include "residents.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <string>
#include <filesystem>

using namespace filesystem;
using namespace std;

int loadCSVArray(string path, Residents array[]) {
    ifstream file(path);
    string line;
    getline(file,line);

    int index = 0;
    while (getline(file,line)) {       // Parsing lines into array
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
    return index;
}

string getTimestamp() {
    auto now = chrono::system_clock::now();
    time_t current_time = chrono::system_clock::to_time_t(now);
    stringstream timestamp;
    timestamp << put_time(localtime(&current_time), "%Y%m%d_%H%M%S");
    return timestamp.str();
}

void fileOutput(Array city, string category, string structure) {
    
    string directory = "Output";
    string timestamp = getTimestamp();
    string filename = "City" + city.name + "_sortBy" + category + "_" + timestamp + ".csv";
    path fullPath = path(directory) / filename;
    ofstream outFile(fullPath.string());

    outFile << "ResidentID,Age,ModeOfTransport,DailyDistance (km),CarbonEmissionFactor(kg CO?/km) ,Average Day per Month\n";
    if (structure == "Array") {
        for (int i=0; i < city.size; i++) {
            outFile << city.array[i].ID << ","
                    << city.array[i].age << ","
                    << city.array[i].mode << ","
                    << city.array[i].distance << ","
                    << city.array[i].carbon << ","
                    << city.array[i].avg << endl;
        }
    } else {
        listResidents* current = city.list.getHead();
        while (current != nullptr) {
            outFile << current->ID << ","
                    << current->age << ","
                    << current->mode << ","
                    << current->distance << ","
                    << current->carbon << ","
                    << current->avg << endl;
            current = current->nextAddress;
        }
    }
    outFile.close();
}

