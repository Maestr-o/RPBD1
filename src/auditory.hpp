#ifndef AUDITORY_HPP

#define AUDITORY_HPP

class Auditory
{
private:
    int id;
    int auditory;

public:
    Auditory();

    int get_id();
    int get_auditory();

    void set_id(int x);
    void set_auditory(int x);

    bool operator==(const Auditory &other);
};

Auditory::Auditory()
{
    id = -1;
    auditory = -1;
}

int Auditory::get_id()
{
    return id;
}

int Auditory::get_auditory()
{
    return auditory;
}

void Auditory::set_id(int x)
{
    id = x;
}

void Auditory::set_auditory(int x)
{
    auditory = x;
}

bool Auditory::operator==(const Auditory &other)
{
    return (this->auditory == other.auditory);
}

#endif