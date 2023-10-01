#ifndef RES_DIPLOMA_HPP

#define RES_DIPLOMA_HPP

#include <iostream>
using namespace std;

class ResDiploma {
private:
    int id;
    int grade_id;
    int subject_id;
public:
    ResDiploma();

    int get_id();
    int get_grade_id();
    int get_subject_id();

    void set_id(int x);
    void set_grade_id(int x);
    void set_subject_id(int x);
};

ResDiploma::ResDiploma() {
    id = -1;
    grade_id = -1;
    subject_id = -1;
}

int ResDiploma::get_id() {
    return id;
}

int ResDiploma::get_grade_id() {
    return grade_id;
}

int ResDiploma::get_subject_id() {
    return subject_id;
}

void ResDiploma::set_id(int x) {
    id = x;
}

void ResDiploma::set_grade_id(int x) {
    grade_id = x;
}

void ResDiploma::set_subject_id(int x) {
    subject_id = x;
}

#endif