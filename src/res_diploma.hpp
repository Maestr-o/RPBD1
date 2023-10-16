#ifndef RES_DIPLOMA_HPP

#define RES_DIPLOMA_HPP

#include <iostream>
using namespace std;

class ResDiploma
{
private:
    int id;
    Grade grade;
    Subject subject;

public:
    ResDiploma();

    int get_id();
    Grade get_grade();
    Subject get_subject();

    void set_id(int x);
    void set_grade(Grade x);
    void set_subject(Subject x);

    bool operator==(const ResDiploma &other);
};

ResDiploma::ResDiploma()
{
    id = -1;
    grade = Grade();
    subject = Subject();
}

int ResDiploma::get_id()
{
    return id;
}

Grade ResDiploma::get_grade()
{
    return grade;
}

Subject ResDiploma::get_subject()
{
    return subject;
}

void ResDiploma::set_id(int x)
{
    id = x;
}

void ResDiploma::set_grade(Grade x)
{
    grade = x;
}

void ResDiploma::set_subject(Subject x)
{
    subject = x;
}

bool ResDiploma::operator==(const ResDiploma &other)
{
    return ((this->id == other.id) && (this->subject == other.subject) && (this->grade == other.grade));
}

#endif