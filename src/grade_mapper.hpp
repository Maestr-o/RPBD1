#ifndef GRADE_MAPPER_HPP

#define GRADE_MAPPER_HPP
#define CHECK_LAST_OPERATION if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {\
            SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());\
            db.set_ret(-1);\
            return;\
        }

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
        grades.clear();
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), db.get_hstmt_address());
        int ret = SQLExecDirect(db.get_hstmt(), (SQLCHAR*)"select * from grades;", SQL_NTS);
        CHECK_LAST_OPERATION

        int col_id, col_grade;
        SQLSMALLINT num_cols;

        ret = SQLNumResultCols(db.get_hstmt(), &num_cols);
        CHECK_LAST_OPERATION

        cout << endl;
        for (int i = 1; SQLFetch(db.get_hstmt()) == SQL_SUCCESS; i++) {
            Grade obj;
            SQLColAttribute(db.get_hstmt(), 1, SQL_C_LONG, (SQLPOINTER)col_id, sizeof(col_id), NULL, NULL);
            SQLGetData(db.get_hstmt(), 1, SQL_C_LONG, &col_id, sizeof(col_id), NULL);
            obj.set_id(col_id);
            SQLColAttribute(db.get_hstmt(), 2, SQL_C_LONG, (SQLPOINTER)col_grade, sizeof(col_grade), NULL, NULL);
            SQLGetData(db.get_hstmt(), 2, SQL_C_LONG, &col_grade, sizeof(col_grade), NULL);
            obj.set_grade(col_grade);
            grades.push_back(obj);
        }
        SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
        db.set_ret(0);
    }

    void insert(Database db, Grade obj) {
        int ret = SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), db.get_hstmt_address());
        CHECK_LAST_OPERATION
        const char* query = "insert into grades (grade) values (?) returning grade_id;";
        ret = SQLPrepare(db.get_hstmt(), (SQLCHAR*)query, SQL_NTS);
        CHECK_LAST_OPERATION

        int tmp = obj.get_grade();
        SQLBindParameter(db.get_hstmt(), 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 
            sizeof(int), 0, (SQLPOINTER)&tmp, 0, NULL);
        ret = SQLExecute(db.get_hstmt());
        CHECK_LAST_OPERATION
        int index;
        ret = SQLFetch(db.get_hstmt());
        CHECK_LAST_OPERATION

        SQLGetData(db.get_hstmt(), 1, SQL_C_LONG, &index, sizeof(index), NULL);
        SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
        db.set_ret(0);
        obj.set_id(index);
        grades.push_back(obj);
    }

    void update(Database db, Grade old_obj, Grade new_obj) {
        int ret = SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), db.get_hstmt_address());
        CHECK_LAST_OPERATION
        const char* query = "update grades set grade = ? where grade = ?;";
        ret = SQLPrepare(db.get_hstmt(), (SQLCHAR*)query, SQL_NTS);
        CHECK_LAST_OPERATION

        int new_grade = new_obj.get_grade();
        int old_grade = old_obj.get_grade();
        SQLBindParameter(db.get_hstmt(), 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 
            sizeof(int), 0, (SQLPOINTER)&new_grade, 0, NULL);
        SQLBindParameter(db.get_hstmt(), 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 
            sizeof(int), 0, (SQLPOINTER)&old_grade, 0, NULL);
        ret = SQLExecute(db.get_hstmt());
        CHECK_LAST_OPERATION

        SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
        db.set_ret(0);
    }

    void del(Database db, Grade obj) {
        int ret = SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), db.get_hstmt_address());
        CHECK_LAST_OPERATION
        const char *query = "delete from grades where grade = ?;";
        ret = SQLPrepare(db.get_hstmt(), (SQLCHAR*)query, SQL_NTS);
        CHECK_LAST_OPERATION
        
        int tmp = obj.get_grade();
        SQLBindParameter(db.get_hstmt(), 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, sizeof(int), 
            0, (SQLPOINTER)&tmp, 0, NULL);
        ret = SQLExecute(db.get_hstmt());
        CHECK_LAST_OPERATION

        SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
        grades.remove(obj);
        db.set_ret(0);
    }
};

#endif