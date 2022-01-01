#include<string>
#include<iostream>
#include<unordered_map> // to store/check existing ID numbers
#include<ctime> // to seed random number generator
#include<fstream>


using namespace std;

class Person
{
public: // all members below are public members -- meaning that are all visible from objects

    static int personCount;
    static unordered_map<unsigned int, int> ID_tracker;

    // function members
    Person(); //the default constructor (without any arguments)
    Person(unsigned int ID_num, unsigned int age ); //the other constructor (which takes two parameters: ID and age)

    // accessor -- method that gives you read-only access to the current values of age
    unsigned int getAge() const; //the last const means the implementation of the method is in-line (for now assume a memory-efficient way of including functional definition)
    void setAge();

    unsigned int getID_num() const;
    void setID_num();

    //Display age and ID number of person
    void showPersonalInfo() const;

    int getTimeWindow(string date) const;
    int analyseSensedData() const;


private:
    // data members that can only be directly accessed by this class and its direct children classes
    unsigned int ID_num;
    unsigned int age;
}; //all structure or class declarations must finish with a semicolon