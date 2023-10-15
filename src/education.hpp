#ifndef EDUCATION_HPP

#define EDUCATION_HPP

#include <iostream>
using namespace std;

class Education
{
private:
    int id;
    string faculty;
    string speciality;
    string university;
    int year_of_ending;
    string type_of_doc;
    int doc_num;
    string foreign_lang;
    float gpa;
    int ege;

public:
    Education();

    int get_id();
    string get_faculty();
    string get_speciality();
    string get_university();
    int get_year_of_ending();
    string get_type_of_doc();
    int get_doc_num();
    string get_foreign_lang();
    float get_gpa();
    int get_ege();

    void set_id(int x);
    void set_faculty(string x);
    void set_speciality(string x);
    void set_university(string x);
    void set_year_of_ending(int x);
    void set_type_of_doc(string x);
    void set_doc_num(int x);
    void set_foreign_lang(string x);
    void set_gpa(float x);
    void set_ege(int x);
};

Education::Education()
{
    id = -1;
    faculty = "";
    speciality = "";
    university = "";
    year_of_ending = -1;
    type_of_doc = "";
    doc_num = -1;
    foreign_lang = "";
    gpa = -1;
    ege = -1;
}

int Education::get_id()
{
    return id;
}

string Education::get_faculty()
{
    return faculty;
}

string Education::get_speciality()
{
    return speciality;
}

string Education::get_university()
{
    return university;
}

int Education::get_year_of_ending()
{
    return year_of_ending;
}

string Education::get_type_of_doc()
{
    return type_of_doc;
}

int Education::get_doc_num()
{
    return doc_num;
}

string Education::get_foreign_lang()
{
    return foreign_lang;
}

float Education::get_gpa()
{
    return gpa;
}

int Education::get_ege()
{
    return ege;
}

void Education::set_id(int x)
{
    id = x;
}

void Education::set_faculty(string x)
{
    faculty = x;
}

void Education::set_speciality(string x)
{
    speciality = x;
}

void Education::set_university(string x)
{
    university = x;
}

void Education::set_year_of_ending(int x)
{
    year_of_ending = x;
}

void Education::set_type_of_doc(string x)
{
    type_of_doc = x;
}

void Education::set_doc_num(int x)
{
    doc_num = x;
}

void Education::set_foreign_lang(string x)
{
    foreign_lang = x;
}

void Education::set_gpa(float x)
{
    gpa = x;
}

void Education::set_ege(int x)
{
    ege = x;
}

#endif