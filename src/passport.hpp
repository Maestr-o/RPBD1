#ifndef PASSPORT_HPP

#define PASSPORT_HPP

#include <iostream>
using namespace std;

class Passport
{
private:
    int id;
    string first_name;
    string last_name;
    string surname;
    int sex;
    string cityzenship;
    string birth;
    int pass_serial;
    int pass_num;

public:
    Passport();

    int get_id();
    string get_first_name();
    string get_last_name();
    string get_surname();
    int get_sex();
    string get_cityzenship();
    string get_birth();
    int get_pass_serial();
    int get_pass_num();

    void set_id(int x);
    void set_first_name(string x);
    void set_last_name(string x);
    void set_surname(string x);
    void set_sex(int x);
    void set_cityzenship(string x);
    void set_birth(string x);
    void set_pass_serial(int x);
    void set_pass_num(int x);
};

Passport::Passport()
{
    id = -1;
    first_name = "";
    last_name = "";
    surname = "";
    sex = -1;
    cityzenship = "";
    birth = "";
    pass_serial = -1;
    pass_num = -1;
}

int Passport::get_id()
{
    return id;
}

string Passport::get_first_name()
{
    return first_name;
}

string Passport::get_last_name()
{
    return last_name;
}

string Passport::get_surname()
{
    return surname;
}

int Passport::get_sex()
{
    return sex;
}

string Passport::get_cityzenship()
{
    return cityzenship;
}

string Passport::get_birth()
{
    return birth;
}

int Passport::get_pass_serial()
{
    return pass_serial;
}

int Passport::get_pass_num()
{
    return pass_num;
}

void Passport::set_id(int x)
{
    id = x;
}

void Passport::set_first_name(string x)
{
    first_name = x;
}

void Passport::set_last_name(string x)
{
    last_name = x;
}

void Passport::set_surname(string x)
{
    surname = x;
}

void Passport::set_sex(int x)
{
    sex = x;
}

void Passport::set_cityzenship(string x)
{
    cityzenship = x;
}

void Passport::set_birth(string x)
{
    birth = x;
}

void Passport::set_pass_serial(int x)
{
    pass_serial = x;
}

void Passport::set_pass_num(int x)
{
    pass_num = x;
}

#endif