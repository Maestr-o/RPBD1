#ifndef SUBJECT_HPP

#define SUBJECT_HPP

class Subject {
private:
    int id;
    string name;
public:
    int get_id();
    std::string get_name();
    void set_id(int x);
    void set_name(std::string x);
};

int Subject::get_id() {
    return id;
}

std::string Subject::get_name() {
    return name;
}

void Subject::set_id(int x) {
    id = x;
}

void Subject::set_name(std::string x) {
    name = x;
}

#endif