#ifndef EXAM_GRADES_HPP

#define EXAM_GRADES_HPP

#include <iostream>
using namespace std;

class ExamGrades
{
private:
    int id;
    int res_exam_id;

public:
    ExamGrades();

    int get_id();
    int get_res_exam_id();

    void set_id(int x);
    void set_res_exam_id(int x);
};

ExamGrades::ExamGrades()
{
    id = -1;
    res_exam_id = -1;
}

int ExamGrades::get_id()
{
    return id;
}

int ExamGrades::get_res_exam_id()
{
    return res_exam_id;
}

void ExamGrades::set_id(int x)
{
    id = x;
}

void ExamGrades::set_res_exam_id(int x)
{
    res_exam_id = x;
}

#endif