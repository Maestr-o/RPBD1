#ifndef ENROLLEE_HPP

#define ENROLLEE_HPP

#include <iostream>
// include other objects
#include "passport.hpp"
#include "education.hpp"

using namespace std;

class Enrollee {
private:
    int id;
    string address;
    string parents_address;
    // include other objects
    Passport passport;
    Education education;
public:
    Enrollee();

    int get_id();
    string get_address();
    string get_parents_address();
    Passport get_passport();

    void set_id(int x);
    void set_address(string x);
    void set_parents_address(string x);
    void set_passport(Passport x);

    bool operator==(const Enrollee& other);
};

Enrollee::Enrollee() {
    id = -1;
    address = "";
    parents_address = "";
}

int Enrollee::get_id() {
    return id;
}

string Enrollee::get_address() {
    return address;
}

string Enrollee::get_parents_address() {
    return parents_address;
}

Passport Enrollee::get_passport() {
    return passport;
}

void Enrollee::set_id(int x) {
    id = x;
}

void Enrollee::set_address(string x) {
    address = x;
}

void Enrollee::set_parents_address(string x) {
    parents_address = x;
}

void Enrollee::set_passport(Passport x) {
    passport = x;
}

bool Enrollee::operator==(const Enrollee& other) {
    return (this->address == other.address && this->parents_address == other.parents_address && 
        this->id == other.id);
}

#endif