#ifndef SUBJECT_MAPPER_HPP

#define SUBJECT_MAPPER_HPP

#include <list>

#include "database.hpp"
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
        SQLHSTMT hstmt;
        subjects.clear();
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);
        SQLExecDirect(hstmt, (SQLCHAR *)"select * from subjects;", SQL_NTS);

        SQLCHAR col_data[256];
        int col_id;
        SQLSMALLINT num_cols;
        SQLNumResultCols(hstmt, &num_cols);
        cout << endl;
        for (int i = 1; SQLFetch(hstmt) == SQL_SUCCESS; i++) {
            Subject obj;
            SQLGetData(hstmt, 1, SQL_C_LONG, &col_id, sizeof(col_id), NULL);
            obj.set_id(col_id);
            SQLGetData(hstmt, 2, SQL_C_CHAR, col_data, sizeof(col_data), NULL);
            obj.set_name(sqlchar_to_string(col_data, strlen((char *)col_data)));
            subjects.push_back(obj);
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    }

    void insert(Database db, Subject obj) {
        SQLHSTMT hstmt;
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);

        const char *query = "insert into subjects (subject) values (?) returning subject_id;";
        SQLPrepare(hstmt, (SQLCHAR *)query, SQL_NTS);
        SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                         sizeof(string_to_sqlchar(obj.get_name())), 0, string_to_sqlchar(obj.get_name()), 0,
                         NULL);
        SQLExecute(hstmt);

        int index;
        SQLFetch(hstmt);
        SQLGetData(hstmt, 1, SQL_C_SLONG, &index, sizeof(index), NULL);
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        obj.set_id(index);

        subjects.push_back(obj);
    }

    void update(Database db, Subject old_obj, Subject new_obj) {
        SQLHSTMT hstmt;
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);

        const char *query = "update subjects set subject = ? where subject = ?;";
        SQLPrepare(hstmt, (SQLCHAR *)query, SQL_NTS);
        SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                         sizeof(string_to_sqlchar(new_obj.get_name())), 0,
                         string_to_sqlchar(new_obj.get_name()), 0, NULL);
        SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                         sizeof(string_to_sqlchar(old_obj.get_name())), 0,
                         string_to_sqlchar(old_obj.get_name()), 0, NULL);
        SQLExecute(hstmt);

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    }

    void del(Database db, Subject obj) {
        SQLHSTMT hstmt;
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);
        const char *query = "delete from subjects where subject = ?;";
        SQLPrepare(hstmt, (SQLCHAR *)query, SQL_NTS);
        SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
                         sizeof(string_to_sqlchar(obj.get_name())), 0, string_to_sqlchar(obj.get_name()), 0,
                         NULL);
        SQLExecute(hstmt);

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        subjects.remove(obj);
    }

    string sqlchar_to_string(SQLCHAR *sqlchar_data, int data_size) {
        return string(reinterpret_cast<char *>(sqlchar_data), data_size);
    }

    SQLCHAR *string_to_sqlchar(const std::string &input) {
        SQLCHAR *result = new SQLCHAR[input.size() + 1];
        strcpy(reinterpret_cast<char *>(result), input.c_str());
        return result;
    }
};

#endif