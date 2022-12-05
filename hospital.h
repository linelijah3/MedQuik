#pragma once
#include <string>
#include <vector>
using namespace std;
class hospital {
private:
    string name, city,state,facilityType, oldName;
    int number, ratingOverall, timelinessRating, safetyRating, heartAttackCost, heartFailureCost, pneumoniaCost, hipkneeCost;
    double averageCost;
public:
    hospital();
    hospital(string& name, string& oldName);
    void setString(string stringData, const string& category);
    string returnString(const string& category);
    int returnInt(const string& category);
    double returnAverage();
};