
#include "hospitalList.h"

void hospitalList::setHospitalDataString(string& name, string &stringData, const string& category) {
    mainList.find(name)->second.setString(stringData, category);
}

string hospitalList::initializeHospital(string &name) {
    if (mainList.find(name) != mainList.end()) {
        for (int j = 2; j < 1000; j++) {
            string newName = name + " (" + to_string(j) + ")";
            if (mainList.find(newName)==mainList.end()) {
                mainList[newName] = (hospital(newName, name));
                mainList[newName].setString(to_string(j), "number");
                return newName;
            }
        }
    }
    mainList[name] = (hospital(name,name));
    return name;
}

void hospitalList::initializeAverageCosts() {
    for (auto &i : mainList) {
        i.second.setString("", "average");
    }
}

void hospitalList::pushHospital(hospital newHospital) {
    mainList[newHospital.returnString("name")] = newHospital;
}
