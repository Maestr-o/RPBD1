#ifndef MAPPER_HPP

#define MAPPER_HPP

#include "database.hpp"

class Mapper {
public:
    virtual int select(Database db) = 0;
    // virtual int insert(Database db) = 0;
    // virtual int update(Database db) = 0;
    // virtual int del(Database db) = 0;
	// virtual int find(Database db) = 0;
};

#endif