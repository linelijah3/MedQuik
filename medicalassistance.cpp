#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <chrono>
#include "hospitalList.h"
#include "sortingAlgos.cpp"
using namespace std;

int main() {
    hospitalList listOfHospitals;
    bool valid = false;
    string firstSelection, secondSelection;
    cout << "Welcome to Medical Assistance's Care Rec Tool\n"
            "---------------------------------------------\n"
            "1) Print Database\n"
            "2) Exit"<<endl;
    cout << "---------------------------------------------\n";
    while (!valid) {
        cout << "Please select an option:" << endl;
        cin >> firstSelection;
        if (firstSelection.compare("1")==0||firstSelection.compare("2")==0) {
            valid = true;
            break;
        }
        cout << "Invalid option."<<endl;
    }
    if (firstSelection.compare("2")==0) {
        return 0;
    }
    fstream file("hospitals.csv");

    //timing system from https://stackoverflow.com/questions/12231166/timing-algorithm-clock-vs-time-in-c
    auto startTime = std::chrono::high_resolution_clock::now();
    string data, placeholder;
    getline(file, placeholder);
    while (getline(file, data)) {
        stringstream categories(data);
        string name, data2;
        //name
        getline(categories, name, ',');
        name = name.substr(1, name.size()-2);
        name = listOfHospitals.initializeHospital(name);
        //city
        getline(categories, data2, ',');
        data2 = data2.substr(1, data2.size()-2);
        listOfHospitals.setHospitalDataString(name, data2, "city");
        //state
        getline(categories, data2, ',');
        data2 = data2.substr(1, data2.size()-2);
        listOfHospitals.setHospitalDataString(name, data2, "state");
        //facility type
        getline(categories, data2, ',');
        data2 = data2.substr(1, data2.size()-2);
        listOfHospitals.setHospitalDataString(name, data2, "facility");
        //overall rating
        getline(categories, data2, ',');
        data2 = data2.substr(1, data2.size()-2);
        listOfHospitals.setHospitalDataString(name, data2, "overallrating");
        //other ratings data (unused)
        getline(categories, data2, ',');
        getline(categories, data2, ',');
        data2 = data2.substr(1, data2.size()-2);
        listOfHospitals.setHospitalDataString(name, data2, "safety");
        getline(categories, data2, ',');
        getline(categories, data2, ',');
        getline(categories, data2, ',');
        getline(categories, data2, ',');
        data2 = data2.substr(1, data2.size()-2);
        listOfHospitals.setHospitalDataString(name, data2, "timeliness");
        getline(categories, data2, ',');
        //heart attack data
        getline(categories, data2, ',');
        data2 = data2.substr(1, data2.size()-2);
        listOfHospitals.setHospitalDataString(name, data2, "heartattack");
        getline(categories, data2, ',');
        getline(categories, data2, ',');
        //heart failure data
        getline(categories, data2, ',');
        data2 = data2.substr(1, data2.size()-2);
        listOfHospitals.setHospitalDataString(name, data2, "heartfailure");
        getline(categories, data2, ',');
        getline(categories, data2, ',');
        //pneumonia data
        getline(categories, data2, ',');
        data2 = data2.substr(1, data2.size()-2);
        listOfHospitals.setHospitalDataString(name, data2, "pneumonia");
        getline(categories, data2, ',');
        getline(categories, data2, ',');
        //hip/knee data
        getline(categories, data2, ',');
        data2 = data2.substr(1, data2.size()-2);
        listOfHospitals.setHospitalDataString(name, data2, "hipknee");
    }
    listOfHospitals.initializeAverageCosts();
    auto endTime = std::chrono::high_resolution_clock::now();
    //calculate time taken to initially create all hospital objects in seconds
    cout << "Initial database loaded in " <<chrono::duration_cast<std::chrono::microseconds>(endTime-startTime).count() <<" microseconds." <<endl;
    bool stateSearch = true;
    while (stateSearch) {
        cout << "---------------------------------------------\n";
        cout << "Please type a state name (2 letters, all capitalized):\n";
        string stateName;
        cin >> stateName;
        //do something with searching + placing
        vector<hospital> heapSortList;
        vector<hospital> mergeSortList;
        bool foundState = false;
        while (!foundState) {
            startTime = std::chrono::high_resolution_clock::now();
            for (auto &i: listOfHospitals.mainList) {
                if (i.second.returnString("state") == stateName) {
                    heapSortList.push_back(i.second);
                    mergeSortList.push_back(i.second);
                    foundState = true;
                }
            }
            endTime = std::chrono::high_resolution_clock::now();
            if (!foundState) {
                cout << "Please type in a valid state name." << endl;
                cout << "Please type a state name (2 letters, all capitalized):\n";
                cin >> stateName;
            }
        }
        cout << "The state being searched is: " << stateName << endl;
        cout << "State-specific lists loaded in " << chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count()
             << " microseconds." << endl;
        cout << "---------------------------------------------\n";
        cout << "Which of these criteria is important to you?\n"
                "1) Cost of Care\n"
                "2) Patient Ratings\n"
                "3) Timeliness\n"
                "4) Safety\n"
                "---------------------------------------------" << endl;
        valid = false;
        while (!valid) {
            cout << "Please select an option:" << endl;
            cin >> secondSelection;
            if (secondSelection.compare("1") == 0 || secondSelection.compare("2") == 0 ||
                secondSelection.compare("3") == 0 || secondSelection.compare("4") == 0) {
                valid = true;
                break;
            }
            cout << "Invalid option." << endl;
        }
        startTime = std::chrono::high_resolution_clock::now();
        heapSort(heapSortList, stoi(secondSelection), 0, heapSortList.size());
        endTime = std::chrono::high_resolution_clock::now();
        auto heapSortTime = chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        startTime = std::chrono::high_resolution_clock::now();
        mergesort(mergeSortList, stoi(secondSelection), 0, mergeSortList.size()-1);
        endTime = std::chrono::high_resolution_clock::now();
        auto mergeSortTime = chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
        cout << "Heap sort took " << heapSortTime << " microseconds to sort the vector." << endl;
        cout << "Merge Sort took " << mergeSortTime << " microseconds to sort the vector." << endl;
        cout << "The first 10 hospitals from the sorted list are:" << endl;
        for (int i = 0; i < 10; i++) {
            cout << i + 1 << ": " << heapSortList[i].returnString("name") << endl;
        }
        cout << "Please note that hospitals with a greater value in the selected criteria are located at the end of the sorted list."<<endl;
        bool hospitalSearch = true;
        while (hospitalSearch) {
            if (!stateSearch) {
                stateSearch = true;
                break;
            }
            valid = false;
            while (!valid) {
                cout << "Choose a hospital to look at from the sorted list:" << endl;
                cin >> secondSelection;
                for (int i = 0; i < heapSortList.size(); i++) {
                    if (secondSelection.compare("" + to_string(i)) == 0) {
                        valid = true;
                        break;
                    }
                }
                if (!valid) {
                    cout << "Invalid number." << endl;
                }
            }
            cout << "Name of hospital: " << heapSortList[stoi(secondSelection)].returnString("name") << endl;
            cout << "State hospital is located in: " << heapSortList[stoi(secondSelection)].returnString("state") << endl;
            cout << "City hospital is located in: " << heapSortList[stoi(secondSelection)].returnString("city") << endl;
            cout << "Facility type of hospital: " << heapSortList[stoi(secondSelection)].returnString("facility") << endl;
            cout << "Overall rating of hospital: " << heapSortList[stoi(secondSelection)].returnInt("overallrating") << endl;
            cout << "Timeliness rating of hospital: " << heapSortList[stoi(secondSelection)].returnInt("timeliness") << endl;
            cout << "Safety rating of hospital: " << heapSortList[stoi(secondSelection)].returnInt("safety") << endl;
            cout << "Hospital's cost of care for heart attacks: " << heapSortList[stoi(secondSelection)].returnInt("heartattack") << endl;
            cout << "Hospital's cost of care for heart failure: " << heapSortList[stoi(secondSelection)].returnInt("heartfailure") << endl;
            cout << "Hospital's cost of care for pneumonia: " << heapSortList[stoi(secondSelection)].returnInt("pneumonia") << endl;
            cout << "Hospital's cost of care for hip/knee conditions: " << heapSortList[stoi(secondSelection)].returnInt("hipknee") << endl;
            cout << "Hospital's average cost of care: " << heapSortList[stoi(secondSelection)].returnAverage() << endl;
            cout << "---------------------------------------------" << endl;
            valid = false;
            while (!valid) {
                cout << "Would you like to search for another hospital (1), search a state (2), or exit the program (3)?" << endl;
                cin >> secondSelection;
                if (secondSelection.compare("1")==0) {
                    break;
                } else if (secondSelection.compare("2")==0) {
                    stateSearch = false;
                    break;
                } else if (secondSelection.compare("3")==0) {
                    return 0;
                }
                if (!valid) {
                    cout << "Invalid selection." << endl;
                }
            }
        }
    }
}