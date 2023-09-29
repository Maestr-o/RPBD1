#ifndef SUBJECT_HPP

#define SUBJECT_HPP

class Subject {
private:
    int id;
    string name;
public:
    int get_id();
    string get_name();
    void set_id(int x);
    void set_name(string x);
    bool operator==(const Subject& other);
};

int Subject::get_id() {
    return id;
}

string Subject::get_name() {
    return name;
}

void Subject::set_id(int x) {
    id = x;
}

void Subject::set_name(string x) {
    name = x;
}

bool Subject::operator==(const Subject& other) {
    return (this->name == other.name);
}

#endif