#ifndef AUDITORY_MAPPER_HPP

#define AUDITORY_MAPPER_HPP

#include <list>

#include "auditory.hpp"
#include "database.hpp"

using namespace std;

class AuditoryMapper {
   public:
    Database db;
    list<Auditory> auditories;

    AuditoryMapper(Database *d) {
        db = *d;
    }

    void get_all() {
        auditories.clear();
        SQLHSTMT hstmt;
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);
        SQLExecDirect(hstmt, (SQLCHAR *)"select * from auditories;", SQL_NTS);
        int col_id, col_aud;
        SQLSMALLINT num_cols;

        SQLNumResultCols(hstmt, &num_cols);
        cout << endl;
        for (int i = 1; SQLFetch(hstmt) == SQL_SUCCESS; i++) {
            Auditory obj;
            SQLGetData(hstmt, 1, SQL_C_LONG, &col_id, sizeof(col_id), NULL);
            obj.set_id(col_id);
            SQLGetData(hstmt, 2, SQL_C_LONG, &col_aud, sizeof(col_aud), NULL);
            obj.set_auditory(col_aud);
            auditories.push_back(obj);
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    }

    void insert(Database db, Auditory obj) {
        SQLHSTMT hstmt;
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);
        const char *query = "insert into auditories (auditory) values (?) returning auditory_id;";
        SQLPrepare(hstmt, (SQLCHAR *)query, SQL_NTS);

        int tmp = obj.get_auditory();
        SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, sizeof(int), 0, (SQLPOINTER)&tmp,
                         0, NULL);
        SQLExecute(hstmt);

        int index;
        SQLFetch(hstmt);

        SQLGetData(hstmt, 1, SQL_C_LONG, &index, sizeof(index), NULL);
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        obj.set_id(index);
        auditories.push_back(obj);
    }

    void update(Database db, Auditory old_obj, Auditory new_obj) {
        SQLHSTMT hstmt;
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);
        const char *query = "update auditories set auditory = ? where auditory = ?;";
        SQLPrepare(hstmt, (SQLCHAR *)query, SQL_NTS);

        int new_grade = new_obj.get_auditory();
        int old_grade = old_obj.get_auditory();
        SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, sizeof(int), 0,
                         (SQLPOINTER)&new_grade, 0, NULL);
        SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, sizeof(int), 0,
                         (SQLPOINTER)&old_grade, 0, NULL);
        SQLExecute(hstmt);

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    }

    void del(Database db, Auditory obj) {
        SQLHSTMT hstmt;
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);
        const char *query = "delete from auditories where auditory = ?;";
        SQLPrepare(hstmt, (SQLCHAR *)query, SQL_NTS);

        int tmp = obj.get_auditory();
        SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, sizeof(int), 0, (SQLPOINTER)&tmp,
                         0, NULL);
        SQLExecute(hstmt);

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        auditories.remove(obj);
    }
};

#endif