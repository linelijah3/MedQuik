#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <chrono>
#include "hospital.cpp"
#include "hospitalList.cpp"
#include "sortingAlgos.cpp"
using namespace std;

int main() {
    hospitalList listOfHospitals;
    bool valid = false;
    int firstSelection, secondSelection;
    cout << "Welcome to Medical Assistance's Care Rec Tool\n"
            "---------------------------------------------\n"
            "1) Print Database\n"
            "2) Exit"<<endl;
    cout << "---------------------------------------------\n";
    while (!valid) {
        cout << "Please select an option:" << endl;
        cin >> firstSelection;
        if (to_string(firstSelection).compare("1")==0||to_string(firstSelection).compare("2")==0) {
            valid = true;
            break;
        }
        cout << "Invalid option."<<endl;
    }
    if (to_string(firstSelection).compare("2")==0) {
        return 0;
    }
    fstream file("hospitals.csv");

    //timing system from https://stackoverflow.com/questions/12231166/timing-algorithm-clock-vs-time-in-c
    auto t1 = std::chrono::high_resolution_clock::now();
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
    auto t2 = std::chrono::high_resolution_clock::now();
    //calculate time taken to initially create all hospital objects in seconds
    cout << "Initial database loaded in " <<chrono::duration_cast<std::chrono::microseconds>(t2-t1).count() <<" microseconds." <<endl;
    cout << "---------------------------------------------\n";
    cout << "Please type a state name (2 letters, all capitalized):\n";
    string stateName;
    cin >> stateName;
    //do something with searching + placing
    vector<hospital> stateList;
    bool foundState = false;
    while (!foundState) {
        t1 = std::chrono::high_resolution_clock::now();
        for (auto &i : listOfHospitals.mainList) {
            if (i.second.returnString("state") == stateName) {
                stateList.push_back(i.second);
                foundState = true;
            }
        }
        t2 = std::chrono::high_resolution_clock::now();
        if (!foundState) {
            cout << "Please type in a valid state name." << endl;
            cout << "Please type a state name (2 letters, all capitalized):\n";
            cin >> stateName;
        }
    }
    cout << "The state being searched is: " << stateName << endl;
    cout << "State-specific list loaded in " <<chrono::duration_cast<std::chrono::microseconds>(t2-t1).count() <<" microseconds." <<endl;
    cout << "---------------------------------------------\n";
    cout << "Which of these criteria is important to you?\n"
            "1) Cost of Care\n"
            "2) Patient Ratings\n"
            "3) Timeliness\n"
            "4) Safety\n"
            "---------------------------------------------"<<endl;
    cout << "Please select an option:" << endl;
    valid = false;
    while (!valid) {
        cin >> secondSelection;
        if (to_string(secondSelection).compare("1")==0||to_string(secondSelection).compare("2")==0||to_string(secondSelection).compare("3")==0||to_string(secondSelection).compare("4")==0) {
            valid = true;
            break;
        }
        cout << "Invalid option."<<endl;
    }
    t1 = std::chrono::high_resolution_clock::now();
    timsort(stateList, secondSelection);
    t2 = std::chrono::high_resolution_clock::now();
    cout << "Timsort took " << chrono::duration_cast<std::chrono::microseconds>(t2-t1).count() << " microseconds to sort the vector." << endl;
}