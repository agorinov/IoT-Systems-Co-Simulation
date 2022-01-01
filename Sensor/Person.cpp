#include "Person.hpp"

using namespace std;

int Person::personCount = 0;
unordered_map<unsigned int, int> Person::ID_tracker;
string outputDirectory = "C:\\Users\\andre\\OneDrive - Newcastle University\\Stage 2 2021-2022\\EEE2007 - Computer Systems and Microprocessors\\projects\\IoT Desktop\\Sensor\\Analysis.txt";

// default constructor
Person::Person()
{
    srand( time( NULL ) );  //  using the time to seed RNG (used to set ID number and age)
    setID_num();
    setAge();

    ID_num = getID_num();
    age = getAge();

    // Increase every time person is created
    personCount++;

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

int Person::getTimeWindow(string date) const
{
    // TODO: return the time window with current time stamp; see the data (*.dat) file for example
}

int Person::analyseSensedData() const
{
    // TODO: read each sample in the data file (sensorA.dat) and check for the criticality conditions

    ofstream analysisFile;
    analysisFile.open(outputDirectory, ios_base::app);

    if(!analysisFile.is_open()) {
        cerr << "Analysis file could not be opened -- exiting." << endl;
        exit(EXIT_FAILURE);
    }

    analysisFile << "---------------------------------------------------------------------------------------------" << endl;
    analysisFile << "Person " << "NUMBER_PLACEHOLDER ";
    analysisFile << "ID " << ID_num << " (Age AGE_RANGE_PLACEHOLDER)" << endl;
    analysisFile << "---------------------------------------------------------------------------------------------" << endl;

    analysisFile.close();

}






