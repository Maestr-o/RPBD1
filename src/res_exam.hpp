#ifndef RES_EXAM_HPP

#define RES_EXAM_HPP

#include <iostream>
using namespace std;

class ResExam {
   private:
    int id;
    int group_num;
    Auditory auditory;
    Subject subject;
    Grade grade;

   public:
    ResExam();

    int get_id();
    int get_group_num();
    Auditory get_auditory();
    Subject get_subject();
    Grade get_grade();
    Auditory *get_link_auditory();
    Subject *get_link_subject();
    Grade *get_link_grade();

    void set_id(int x);
    void set_group_num(int x);
    void set_auditory(Auditory x);
    void set_subject(Subject x);
    void set_grade(Grade x);

    bool operator==(const ResExam &other);
};

ResExam::ResExam() {
    id = -1;
    group_num = -1;
    subject = Subject();
    grade = Grade();
    auditory = Auditory();
}

int ResExam::get_id() {
    return id;
}

int ResExam::get_group_num() {
    return group_num;
}

Auditory ResExam::get_auditory() {
    return auditory;
}

Subject ResExam::get_subject() {
    return subject;
}

Grade ResExam::get_grade() {
    return grade;
}

Auditory *ResExam::get_link_auditory() {
    return &auditory;
}

Subject *ResExam::get_link_subject() {
    return &subject;
}

Grade *ResExam::get_link_grade() {
    return &grade;
}

void ResExam::set_id(int x) {
    id = x;
}

void ResExam::set_group_num(int x) {
    group_num = x;
}

void ResExam::set_auditory(Auditory x) {
    auditory = x;
}

void ResExam::set_subject(Subject x) {
    subject = x;
}

void ResExam::set_grade(Grade x) {
    grade = x;
}

bool ResExam::operator==(const ResExam &other) {
    return ((this->id == other.id) && (this->subject == other.subject) && (this->grade == other.grade) &&
            (this->auditory == other.auditory) && (this->group_num == other.group_num));
}

#endif