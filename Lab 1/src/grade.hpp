#ifndef GRADE_HPP

#define GRADE_HPP

class Grade {
private:
    int id;
    int grade;
public:
    int get_id();
    int get_grade();
    void set_id(int x);
    void set_grade(int x);
    bool operator==(const Grade& other);
};

int Grade::get_id() {
    return id;
}

int Grade::get_grade() {
    return grade;
}

void Grade::set_id(int x) {
    id = x;
}

void Grade::set_grade(int x) {
    grade = x;
}

bool Grade::operator==(const Grade& other) {
    return (this->grade == other.grade);
}

#endif