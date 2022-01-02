#include "Person.hpp"

using namespace std;

//int Person::personCount = 0;
unordered_map<unsigned int, int> Person::ID_tracker;

// default constructor
Person::Person()
{
    srand( time( NULL ) );  //  using the time to seed RNG (used to set ID number and age)
    setID_num();
    setAge();

    ID_num = getID_num();
    age = getAge();

    // Increase every time person is created
//    personCount++;

}

// implement the other constructor with two parameters
//Person::Person( unsigned int ID_num, unsigned int age )
//{
//    ID_num = 123; //place-holder--implement randomly-generated ID number
//    age = 25; //place-holder
//}

unsigned int Person::getAge() const
{
    return age;
}

// Generate a random age between 0 and 99
void Person::setAge()
{
    unsigned int maxAge = 99;
    unsigned int minAge = 0;

//    srand( time( NULL ) );  //  using the time seed
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

    // TODO: implement different seed?
//    srand( time( NULL ) );  //  using the time seed
    while(true) {
        tempID = (rand() % (maxID_num - minID_num + 1)) + minID_num;
        if (ID_tracker.count(tempID)) {
            cout << "ID " << tempID << " exists" << endl;
        } else {
            cout << "ID " << tempID << " is unique" << endl;
            ID_num = tempID;
            ID_tracker[ID_num] = 0;
            break;
        }
    }
}

// Prints the age and ID number of person object
void Person::showPersonalInfo() const
{
    cout << "ID number = " << this->ID_num << endl;
    cout << "age = " << this->age << endl;
}

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
    ss >> get_time(&tm, "%Y-%m-%d %H:%M:%S");
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

int Person:: analyseSensedData(string timeWindow, int sampleValue) const
{
    // TODO: read each sample in the data file (sensorA.dat) and check for the criticality conditions



}






