#ifndef MAPPER_HPP

#define MAPPER_HPP

#include "database.hpp"

class Mapper {
public:
    virtual void select(Database db) = 0;
    virtual void insert(Database db) = 0;
    virtual void update(Database db) = 0;
    virtual void del(Database db) = 0;
	//virtual void search(Database db) = 0;
};

#endif