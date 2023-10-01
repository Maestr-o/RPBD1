#ifndef RES_EXAM_HPP

#define RES_EXAM_HPP

#include <iostream>
using namespace std;

class ResExam {
private:
    int id;
    int group_num;
    int auditory_id;
    int subject_id;
    int grade_id;
public:
    ResExam();

    int get_id();
    int get_group_num();
    int get_auditory_id();
    int get_subject_id();
    int get_grade_id();

    void set_id(int x);
    void set_group_num(int x);
    void set_auditory_id(int x);
    void set_subject_id(int x);
    void set_grade_id(int x);
};

ResExam::ResExam() {
    id = -1;
    group_num = -1;
    auditory_id = -1;
    subject_id = -1;
    grade_id = -1;
}

int ResExam::get_id() {
    return id;
}

int ResExam::get_group_num() {
    return group_num;
}

int ResExam::get_auditory_id() {
    return auditory_id;
}

int ResExam::get_subject_id() {
    return subject_id;
}

int ResExam::get_grade_id() {
    return grade_id;
}

void ResExam::set_id(int x) {
    id = x;
}

void ResExam::set_group_num(int x) {
    group_num = x;
}

void ResExam::set_auditory_id(int x) {
    auditory_id = x;
}

void ResExam::set_subject_id(int x) {
    subject_id = x;
}

void ResExam::set_grade_id(int x) {
    grade_id = x;
}

#endif