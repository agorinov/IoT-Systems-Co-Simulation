#include "Person.hpp"

using namespace std;

// default constructor
Person::Person( )
{
    setAge();
    setID_num();

    ID_num = getID_num();
    age = getAge();

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

    age = (rand() % (maxAge - minAge + 1)) + minAge;
}

unsigned int Person::getID_num() const
{
    return ID_num;
}

void Person::setID_num()
{
    unsigned int maxID_num = 999;
    unsigned int minID_num = 101;

    ID_num = (rand() % (maxID_num - minID_num + 1)) + minID_num; //TODO: create unique ID number for each person
}

string Person::showPersonalInfo() const
{
    cout << "ID number = " << this->ID_num << endl;
    cout << "age = " << this->age << endl;
}






