#include "Person.hpp"

using namespace std;

int Person::personCount = 0;
unordered_map<unsigned int, int> Person::ID_tracker;

// default constructor
Person::Person()
{
    srand( time( NULL ) );  //  using the time seed
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

void Person::setID_num()
{
    unsigned int maxID_num = 5;
    unsigned int minID_num = 1;
    unsigned int t;

    // TODO: implement different random seed?
//    srand( time( NULL ) );  //  using the time seed
    while(true) {
        t = (rand() % (maxID_num - minID_num + 1)) + minID_num;
        if (ID_tracker.count(t)) {
            cout << "ID " << t << " exists" << endl;
        } else {
            cout << "ID " << t << " is unique" << endl;
            ID_num = t;
            ID_tracker[ID_num] = 0;
            break;
        }
    }
}

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
}






