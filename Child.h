//
// Created by Niko on 7/21/2022.
//

#ifndef ACTUAL_PROGRAM_3_CHILD_H
#define ACTUAL_PROGRAM_3_CHILD_H

#pragma once
#include <iostream>
#include <string>

using namespace std;

class Child
{
    //IO Operator overloads
    friend ostream &operator<<(ostream &os, const Child &c);
    friend istream &operator>>(istream &is, Child &c);

public:
    //Constructors
    Child(); //Default Constructor
    Child(string first, string last, int childAge); //3-Arg Constructor
    ~Child(); //Destructor

    //Operator Overloads
    bool operator>(const Child &that) const;
    bool operator<(const Child &that) const;
    bool operator==(const Child &that) const;
    bool operator!=(const Child &that) const;

private:
    string firstName; //Child's first name
    string lastName; //Child's last name
    int age; //Child's age

};


#endif //ACTUAL_PROGRAM_3_CHILD_H
