//
// Created by Niko on 7/21/2022.
//

#include "Child.h"

using namespace std;

//Constructors
Child::Child() //Default Constructor
{
    this->firstName = "";
    this->lastName = "";
    this->age = 0;
}

Child::Child(string first, string last, int childAge) //3-Arg Constructor
{
    this->firstName = first;
    this->lastName = last;
    this->age = childAge;
}

Child::~Child()
{
    //Empty Destructor
}

//IO Operator Overloads
ostream &operator<<(ostream &os, const Child &c)
{
    os << c.firstName << c.lastName << c.age;
    return os;
}

istream &operator>>(istream &is, Child &c)
{
    is >> c.firstName >> c.lastName >> c.age;
    return is;
}

//Operator Overloads
bool Child::operator>(const Child &that) const
{
    //bool isGreaterThan;
    /*Tests if the lastName comes alphabetically sooner. If equal, function compares the first names. If
    the first names are equal, the function compares the ages.*/
    if(this->lastName > that.lastName)
        return true;

    if(this->lastName == that.lastName && this->firstName > that.firstName)
        return true;

    if(this->lastName == that.lastName && this->firstName == that.firstName && this->age > that.age)
        return true;

    return false;
}

bool Child::operator<(const Child &that) const
{
    if(this->lastName < that.lastName)
        return true;

    if(this->lastName == that.lastName && this->firstName < that.firstName)
        return true;

    if(this->lastName == that.lastName && this->firstName == that.firstName && this->age < that.age)
        return true;

    return false;
}

bool Child::operator==(const Child &that) const
{
    if(this->lastName != that.lastName && this->firstName != that.lastName && this->age != that.age)
        return false;
    else
        return true;
}
bool Child::operator!=(const Child &that) const
{
    if(this->lastName != that.lastName || this->firstName != that.lastName || this->age != that.age)
        return true;
    else
        return false;
}