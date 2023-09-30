#ifndef SUBJECT_MAPPER_HPP

#define SUBJECT_MAPPER_HPP
#define CHECK_LAST_OPERATION if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {\
            SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());\
            db.set_ret(-1);\
            return;\
        }

#include <list>
#include "subject.hpp"

using namespace std;

class SubjectMapper {
public:
    Database db;
    list<Subject> subjects;

    SubjectMapper(Database *d) {
        db = *d;
    }

    void get_all() {
        subjects.clear();
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), db.get_hstmt_address());
        int ret = SQLExecDirect(db.get_hstmt(), (SQLCHAR*)"select * from subjects;", SQL_NTS);
        CHECK_LAST_OPERATION

        SQLCHAR col_name[256];
        SQLCHAR col_data[256];
        int col_id;
        SQLSMALLINT col_name_length;
        SQLSMALLINT num_cols;

        ret = SQLNumResultCols(db.get_hstmt(), &num_cols);
        CHECK_LAST_OPERATION

        cout << endl;
        for (int i = 1; SQLFetch(db.get_hstmt()) == SQL_SUCCESS; i++) {
            Subject obj;
            SQLColAttribute(db.get_hstmt(), 1, SQL_C_LONG, (SQLPOINTER)col_id, sizeof(col_id), NULL, NULL);
            SQLGetData(db.get_hstmt(), 1, SQL_C_LONG, &col_id, sizeof(col_id), NULL);
            obj.set_id(col_id);
            SQLColAttribute(db.get_hstmt(), 2, SQL_DESC_NAME, col_name, sizeof(col_name), &col_name_length, NULL);
            SQLGetData(db.get_hstmt(), 2, SQL_C_CHAR, col_data, sizeof(col_data), NULL);
            obj.set_name(sqlchar_to_string(col_data, strlen((char *)col_data)));
            subjects.push_back(obj);
        }
        SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
        db.set_ret(0);
    }

    void insert(Database db, Subject obj) {
        int ret = SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), db.get_hstmt_address());
        CHECK_LAST_OPERATION
        const char* query = "insert into subjects (subject) values (?) returning subject_id;";
        ret = SQLPrepare(db.get_hstmt(), (SQLCHAR*)query, SQL_NTS);
        CHECK_LAST_OPERATION

        SQLBindParameter(db.get_hstmt(), 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 
            sizeof(string_to_sqlchar(obj.get_name())), 0, string_to_sqlchar(obj.get_name()), 0, NULL);
        cout << string_to_sqlchar(obj.get_name()); //
        ret = SQLExecute(db.get_hstmt());
        CHECK_LAST_OPERATION
        int index;
        ret = SQLFetch(db.get_hstmt());
        CHECK_LAST_OPERATION

        SQLGetData(db.get_hstmt(), 1, SQL_C_SLONG, &index, sizeof(index), NULL);
        SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
        db.set_ret(0);
        obj.set_id(index);
        subjects.push_back(obj);
    }

    void update(Database db, Subject old_obj, Subject new_obj) {
        int ret = SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), db.get_hstmt_address());
        CHECK_LAST_OPERATION
        const char* query = "update subjects set subject = ? where subject = ?;";
        ret = SQLPrepare(db.get_hstmt(), (SQLCHAR*)query, SQL_NTS);
        CHECK_LAST_OPERATION

        SQLBindParameter(db.get_hstmt(), 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 
            sizeof(string_to_sqlchar(new_obj.get_name())), 0, string_to_sqlchar(new_obj.get_name()), 0, NULL);
        SQLBindParameter(db.get_hstmt(), 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 
            sizeof(string_to_sqlchar(old_obj.get_name())), 0, string_to_sqlchar(old_obj.get_name()), 0, NULL);
        ret = SQLExecute(db.get_hstmt());
        CHECK_LAST_OPERATION

        SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
        db.set_ret(0);
    }

    void del(Database db, Subject obj) {
        int ret = SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), db.get_hstmt_address());
        CHECK_LAST_OPERATION
        const char *query = "delete from subjects where subject = ?;";
        ret = SQLPrepare(db.get_hstmt(), (SQLCHAR*)query, SQL_NTS);
        CHECK_LAST_OPERATION
        
        SQLBindParameter(db.get_hstmt(), 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sizeof(string_to_sqlchar(obj.get_name())), 0, string_to_sqlchar(obj.get_name()), 0, NULL);
        ret = SQLExecute(db.get_hstmt());
        CHECK_LAST_OPERATION

        SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
        subjects.remove(obj);
        db.set_ret(0);
    }

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