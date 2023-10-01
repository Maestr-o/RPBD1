#ifndef ENROLLEE_MAPPER_HPP

#define ENROLLEE_MAPPER_HPP
#define CHECK_LAST_OPERATION if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {\
            SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());\
            db.set_ret(-1);\
            return;\
        }

#include <list>
#include "database.hpp"
#include "enrollee.hpp"

using namespace std;

class EnrolleeMapper {
public:
    Database db;
    list<Enrollee> applicants;

    EnrolleeMapper(Database *d) {
        db = *d;
    }

    void get_all() {
        applicants.clear();
        
    }

    // void insert(Database db, Enrollee obj) {
        
    // }

    // void update(Database db, Enrollee old_obj, Enrollee new_obj) {
        
    // }

    // void del(Database db, Enrollee obj) {
        
    // }

    string sqlchar_to_string(SQLCHAR* sqlchar_data, int data_size) {
        return string(reinterpret_cast<char*>(sqlchar_data), data_size);
    }

    SQLCHAR* string_to_sqlchar(const std::string& input) {
        SQLCHAR* result = new SQLCHAR[input.size() + 1];
        strcpy(reinterpret_cast<char*>(result), input.c_str());
        return result;
    }
};

#endif