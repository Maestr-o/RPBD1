#ifndef ENROLLEE_HPP

#define ENROLLEE_HPP

#include <iostream>
#include <list>
#include "passport.hpp"
#include "education.hpp"
#include "res_diploma.hpp"

using namespace std;

class Enrollee
{
private:
    int id;
    string address;
    string parents_address;
    Passport passport;
    Education education;
    list<ResDiploma> diploma;

public:
    Enrollee();

    int get_id();
    string get_address();
    string get_parents_address();
    Passport get_passport();
    Education get_education();
    list<ResDiploma> get_diploma();
    Passport *get_link_passport();
    Education *get_link_education();

    void set_id(int x);
    void set_address(string x);
    void set_parents_address(string x);
    void set_passport(Passport x);
    void set_education(Education x);
    void set_diploma(list<ResDiploma> x);

    bool operator==(const Enrollee &other);
};

Enrollee::Enrollee()
{
    id = -1;
    address = "";
    parents_address = "";
}

int Enrollee::get_id()
{
    return id;
}

string Enrollee::get_address()
{
    return address;
}

string Enrollee::get_parents_address()
{
    return parents_address;
}

list<ResDiploma> Enrollee::get_diploma()
{
    return diploma;
}

Passport *Enrollee::get_link_passport()
{
    return &passport;
}

Education *Enrollee::get_link_education()
{
    return &education;
}

Passport Enrollee::get_passport()
{
    return passport;
}

Education Enrollee::get_education()
{
    return education;
}

void Enrollee::set_id(int x)
{
    id = x;
}

void Enrollee::set_address(string x)
{
    address = x;
}

void Enrollee::set_parents_address(string x)
{
    parents_address = x;
}

void Enrollee::set_passport(Passport x)
{
    passport = x;
}

void Enrollee::set_education(Education x)
{
    education = x;
}

void Enrollee::set_diploma(list<ResDiploma> x)
{
    diploma = x;
}

bool Enrollee::operator==(const Enrollee &other)
{
    return (this->address == other.address && this->parents_address == other.parents_address &&
            this->id == other.id);
}

#endif