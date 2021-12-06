#include<string>

using namespace std;

class Person
{
public: // all members below are public members -- meaning that are all visible from objects

    // function members
    // constructors help creating an object from a class definition
    Person(); //the default constructor (without any arguments)
    Person(unsigned int ID_num, unsigned int age ); //the other constructor (which takes two parameters: ID and age)

    // accessor -- method that gives you read-only access to the current values of age
    float getAge() const; //the last const means the implementation of the method is in-line (for now assume a memory-efficient way of including functional definition)
    void setAge();

    //Display age and ID number of person
    string showPersonalInfo() const;

private:
    // data members that can only be directly accessed by this class and its direct children classes
    unsigned int ID_num;
    unsigned int age;
}; //all structure or class declarations must finish with a semicolon
