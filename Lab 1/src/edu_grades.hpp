#ifndef EDU_GRADES_HPP

#define EDU_GRADES_HPP

#include <iostream>
using namespace std;

class EduGrades {
private:
    int id;
    int res_dip_id;
public:
    EduGrades();

    int get_id();
    int get_res_dip_id();

    void set_id(int x);
    void set_res_dip_id(int x);
};

EduGrades::EduGrades() {
    id = -1;
    res_dip_id = -1;
}

int EduGrades::get_id() {
    return id;
}

int EduGrades::get_res_dip_id() {
    return res_dip_id;
}

void EduGrades::set_id(int x) {
    id = x;
}

void EduGrades::set_res_dip_id(int x) {
    res_dip_id = x;
}

#endif