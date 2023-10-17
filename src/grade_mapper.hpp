#ifndef GRADE_MAPPER_HPP

#define GRADE_MAPPER_HPP

#include <list>

#include "database.hpp"
#include "grade.hpp"

using namespace std;

class GradeMapper {
   public:
    Database db;
    list<Grade> grades;

    GradeMapper(Database *d) {
        db = *d;
    }

    void get_all() {
        SQLHSTMT hstmt;
        grades.clear();

        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);
        SQLExecDirect(hstmt, (SQLCHAR *)"select * from grades;", SQL_NTS);
        int col_id, col_grade;
        SQLSMALLINT num_cols;
        SQLNumResultCols(hstmt, &num_cols);
        cout << endl;
        for (int i = 1; SQLFetch(hstmt) == SQL_SUCCESS; i++) {
            Grade obj;
            SQLColAttribute(hstmt, 1, SQL_C_LONG, (SQLPOINTER)col_id, sizeof(col_id), NULL, NULL);
            SQLGetData(hstmt, 1, SQL_C_LONG, &col_id, sizeof(col_id), NULL);
            obj.set_id(col_id);
            SQLColAttribute(hstmt, 2, SQL_C_LONG, (SQLPOINTER)col_grade, sizeof(col_grade), NULL, NULL);
            SQLGetData(hstmt, 2, SQL_C_LONG, &col_grade, sizeof(col_grade), NULL);
            obj.set_grade(col_grade);
            grades.push_back(obj);
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    }

    void insert(Database db, Grade obj) {
        SQLHSTMT hstmt;
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);

        const char *query = "insert into grades (grade) values (?) returning grade_id;";
        SQLPrepare(hstmt, (SQLCHAR *)query, SQL_NTS);
        int tmp = obj.get_grade();
        SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, sizeof(int), 0, (SQLPOINTER)&tmp,
                         0, NULL);
        SQLExecute(hstmt);

        int index;
        SQLFetch(hstmt);
        SQLGetData(hstmt, 1, SQL_C_LONG, &index, sizeof(index), NULL);
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        obj.set_id(index);
        grades.push_back(obj);
    }

    void update(Database db, Grade old_obj, Grade new_obj) {
        SQLHSTMT hstmt;
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);

        const char *query = "update grades set grade = ? where grade = ?;";
        SQLPrepare(hstmt, (SQLCHAR *)query, SQL_NTS);
        int new_grade = new_obj.get_grade();
        int old_grade = old_obj.get_grade();
        SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, sizeof(int), 0,
                         (SQLPOINTER)&new_grade, 0, NULL);
        SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, sizeof(int), 0,
                         (SQLPOINTER)&old_grade, 0, NULL);
        SQLExecute(hstmt);
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    }

    void del(Database db, Grade obj) {
        SQLHSTMT hstmt;
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);

        const char *query = "delete from grades where grade = ?;";
        SQLPrepare(hstmt, (SQLCHAR *)query, SQL_NTS);
        int tmp = obj.get_grade();
        SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, sizeof(int), 0, (SQLPOINTER)&tmp,
                         0, NULL);
        SQLExecute(hstmt);
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        grades.remove(obj);
    }
};

#endif