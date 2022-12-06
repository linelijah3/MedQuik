#include <iostream>
using namespace std;

void pushRandomizedHospital(hospitalList& list){
    for (int i = 0; i < 3500; i++){
        string name = to_string(i) + " Center", city = to_string(rand() % 1000 + 1), state = "", facilityType = "";
        int number, ratingOverall, timelinessRating, safetyRating, heartAttackCost, heartFailureCost, pneumoniaCost, hipkneeCost;
        double averageCost;
    
        int random = rand() % 51;
        // randomize state
        if (random == 0)
            state += "AL";
        else if (random == 1)
            state += "AK";
        else if (random == 2)
            state += "AZ";
        else if (random == 3)
            state += "AR";
        else if (random == 4)
            state += "CA";
        else if (random == 5)
            state += "CO";
        else if (random == 6)
            state += "CT";
        else if (random == 7)
            state += "DE";
        else if (random == 8)
            state += "FL";
        else if (random == 9)
            state += "GA";
        else if (random == 10)
            state += "HI";
        else if (random == 11)
            state += "ID";
        else if (random == 12)
            state += "IL";
        else if (random == 13)
            state += "IN";
        else if (random == 14)
            state += "IA";
        else if (random == 15)
            state += "KS";
        else if (random == 16)
            state += "KY";
        else if (random == 17)
            state += "LA";
        else if (random == 18)
            state += "ME";
        else if (random == 19)
            state += "MD";
        else if (random == 20)
            state += "MA";
        else if (random == 21)
            state += "MI";
        else if (random == 22)
            state += "MN";
        else if (random == 23)
            state += "MS";
        else if (random == 24)
            state += "MO";
        else if (random == 25)
            state += "MT";
        else if (random == 26)
            state += "NE";
        else if (random == 27)
            state += "NV";
        else if (random == 28)
            state += "NH";
        else if (random == 29)
            state += "NJ";
        else if (random == 30)
            state += "NM";
        else if (random == 31)
            state += "NY";
        else if (random == 32)
            state += "NC";
        else if (random == 33)
            state += "ND";
        else if (random == 34)
            state += "OH";
        else if (random == 35)
            state += "OK";
        else if (random == 36)
            state += "OR";
        else if (random == 37)
            state += "PA";
        else if (random == 38)
            state += "RI";
        else if (random == 39)
            state += "SC";
        else if (random == 40)
            state += "SD";
        else if (random == 41)
            state += "TN";
        else if (random == 42)
            state += "TX";
        else if (random == 43)
            state += "UT";
        else if (random == 44)
            state += "VT";
        else if (random == 45)
            state += "VA";
        else if (random == 46)
            state += "WA";
        else if (random == 47)
            state += "WV";
        else if (random == 48)
            state += "WI";
        else if (random == 49)
            state += "WY";
        else if (random == 50)
            state += "DC";
        else
            cout << "state error" << endl;
    
        random = rand() % 4;
        // randomize facility type
        if (random == 0)
            facilityType += "Government";
        else if (random == 1)
            facilityType += "Private";
        else if (random == 2)
            facilityType += "Proprietary";
        else if (random == 3)
            facilityType += "Unknown";
        else
            cout << "facility error" << endl;
        
        random = rand() % 6;
        // randomize overall rating
        if (random == 0)
            ratingOverall = -1;
        else if (random == 1)
            ratingOverall = 1;
        else if (random == 2)
            ratingOverall = 2;
        else if (random == 3)
            ratingOverall = 3;
        else if (random == 4)
            ratingOverall = 4;
        else if (random == 5)
            ratingOverall = 5;

        random = rand() % 6;
        // randomize timeliness rating
        if (random == 0)
            timelinessRating = -1;
        else if (random == 1)
            timelinessRating = 1;
        else if (random == 2)
            timelinessRating = 2;
        else if (random == 3)
            timelinessRating = 3;
        else if (random == 4)
            timelinessRating = 4;
        else if (random == 5)
            timelinessRating = 5;

        random = rand() % 6;
        // randomize safety rating
        if (random == 0)
            safetyRating = -1;
        else if (random == 1)
            safetyRating = 1;
        else if (random == 2)
            safetyRating = 2;
        else if (random == 3)
            safetyRating = 3;
        else if (random == 4)
            safetyRating = 4;
        else if (random == 5)
            safetyRating = 5;

        heartAttackCost = rand() % 30000;
        heartFailureCost = rand() % 30000;
        pneumoniaCost = rand() % 30000;
        hipkneeCost = rand() % 30000;
        averageCost = (1.0 * (heartAttackCost + heartFailureCost + pneumoniaCost + hipkneeCost)) / 4;

        list.mainList[name] = (hospital(name, city, state, facilityType, ratingOverall, timelinessRating, safetyRating, heartAttackCost, heartFailureCost, pneumoniaCost, hipkneeCost, averageCost));    }
}