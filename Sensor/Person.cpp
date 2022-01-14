#include "Person.hpp"

using namespace std;

//int Person::personCount = 0;
unordered_map<unsigned int, int> Person::ID_tracker; // stores existing ID numbers

// default constructor
Person::Person()
{
    srand( time( NULL ) );  //  using the time to seed RNG (used to set ID number and age)
    setID_num();
    setAge();

    ID_num = getID_num();
    age = getAge();


}

// implement the other constructor with two parameters
Person::Person( unsigned int ID_num, unsigned int age )
{
    this->ID_num = ID_num;
    this->age = age;
}

unsigned int Person::getAge() const
{
    return age;
}

// Generate a random age between 0 and 99
void Person::setAge()
{
    unsigned int maxAge = 99;
    unsigned int minAge = 0;

    age = (rand() % (maxAge - minAge + 1)) + minAge;
}

unsigned int Person::getID_num() const
{
    return ID_num;
}

// Generate a random, unique ID number between 101 and 999
void Person::setID_num()
{
    unsigned int maxID_num = 999;
    unsigned int minID_num = 101;
    unsigned int tempID;

    while(true) {
        tempID = (rand() % (maxID_num - minID_num + 1)) + minID_num;
        if (ID_tracker.count(tempID)) { //checks if new ID is contained within ID_tracker
//            cout << "ID " << tempID << " exists" << endl;
        } else {
//            cout << "ID " << tempID << " is unique" << endl;
            ID_num = tempID;
            ID_tracker[ID_num] = 0;
            break;
        }
    }
}

// Print the ID number and age range of person for use in analysis file
string Person::showPersonalInfo() const
{
    return "ID: " + to_string(ID_num) + " (Age " + getAgeRange() + " years)";
}

// Determine age range for use in analysis file and critical sensed values
string Person::getAgeRange() const
{
    if(age >= 0 and age <= 6){
        return "0-6";
    } else if(age >= 7 and age <= 16){
        return "7-16";
    } else if(age >= 17 and age <= 38){
        return "17-38";
    } else if(age >= 39 and age <= 55){
        return "39-55";
    } else if(age > 55){
        return "55+";
    } else return "N/A";
}

// Parse timestamp and return corresponding time window as string
string Person::getTimeWindow(string date) const
{
    tm tm = {}; // struct containing time/date components

    stringstream ss(date);
    ss >> get_time(&tm, "%Y-%m-%d.%X");
//    cout << "hours: " << tm.tm_hour << " minutes: " << tm.tm_min << endl;

    if(tm.tm_hour >= 0 and tm.tm_hour < 7){
        return "Night";
    } else if (tm.tm_hour >= 7 and tm.tm_hour < 10){
        return "Morning";
    } else if (tm.tm_hour >= 10 and tm.tm_hour < 18){
        return "Daytime";
    } else if (tm.tm_hour >= 18 and tm.tm_hour <= 23){
        return "Evening";
    } else return "Error";

}
// Check for criticality conditions
int Person:: analyseSensedData(const string& timeWindow, float sampleValue) const
{

    int criticalValue = 0;

//    cout << "time window: " << timeWindow << endl;
//    cout << "sample value: " << sampleValue << endl;

    string ageRange = getAgeRange();
    if(timeWindow == "Night") {
        if (ageRange == "0-6") {
            if (sampleValue < 20 or sampleValue > 30.2) {
                criticalValue = 1;
            }
        } else if (ageRange == "7-16") {
            if (sampleValue < 22 or sampleValue > 35.9) {
                criticalValue = 1;
            }
        } else if (ageRange == "17-38") {
            if (sampleValue < 22.7 or sampleValue > 37.3) {
                criticalValue = 1;
            }
        } else if (ageRange == "39-55") {
            if (sampleValue < 25.7 or sampleValue > 38.3) {
                criticalValue = 1;
            }
        } else if (ageRange == "55+") {
            if (sampleValue < 20 or sampleValue > 35) {
                criticalValue = 1;
            }
        }
    } else if(timeWindow == "Morning"){
        if (ageRange == "0-6") {
            if (sampleValue < 30 or sampleValue > 52) {
                criticalValue = 1;
            }
        } else if (ageRange == "7-16") {
            if (sampleValue < 30 or sampleValue > 55) {
                criticalValue = 1;
            }
        } else if (ageRange == "17-38") {
            if (sampleValue < 32 or sampleValue > 57.8) {
                criticalValue = 1;
            }
        } else if (ageRange == "39-55") {
            if (sampleValue < 32 or sampleValue > 57.8) {
                criticalValue = 1;
            }
        } else if (ageRange == "55+") {
            if (sampleValue < 30 or sampleValue > 50) {
                criticalValue = 1;
            }
        }
    } else if(timeWindow == "Daytime"){
        if (ageRange == "0-6") {
            if (sampleValue < 20 or sampleValue > 40) {
                criticalValue = 1;
            }
        } else if (ageRange == "7-16") {
            if (sampleValue < 20 or sampleValue > 39) {
                criticalValue = 1;
            }
        } else if (ageRange == "17-38") {
            if (sampleValue <= 22.7 or sampleValue >= 41) {
                criticalValue = 1;
            }
        } else if (ageRange == "39-55") {
            if (sampleValue < 22.7 or sampleValue > 41) {
                criticalValue = 1;
            }
        } else if (ageRange == "55+") {
            if (sampleValue < 25.7 or sampleValue > 37) {
                criticalValue = 1;
            }
        }
    } else if(timeWindow == "Evening"){
        if (ageRange == "0-6") {
            if (sampleValue < 25 or sampleValue > 52) {
                criticalValue = 1;
            }
        } else if (ageRange == "7-16") {
            if (sampleValue < 25 or sampleValue > 55) {
                criticalValue = 1;
            }
        } else if (ageRange == "17-38") {
            if (sampleValue < 25 or sampleValue > 57.8) {
                criticalValue = 1;
            }
        } else if (ageRange == "39-55") {
            if (sampleValue < 25 or sampleValue > 57.8) {
                criticalValue = 1;
            }
        } else if (ageRange == "55+") {
            if (sampleValue < 25 or sampleValue > 40) {
                criticalValue = 1;
            }
        }
    }

    return criticalValue;
}


float Person:: calculateCriticalSamplesPercent( int numberOfCriticalValues, int numberOfTotalValues) const
{
    float result = -1; // no saples

    if (numberOfTotalValues > 0){
        result = 100*(float)numberOfCriticalValues/(float)numberOfTotalValues;
    }

    return result;
}






