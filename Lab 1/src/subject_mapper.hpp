#ifndef SUBJECT_MAPPER_HPP

#define SUBJECT_MAPPER_HPP

#include "subject.hpp"
#include "mapper.hpp"

class SubjectMapper : public Mapper {
public:
    int select(Database db) override {
        int ret = db.exec_cont("select * from subjects;");
        if (!SQL_SUCCEEDED(ret)) return 0;
        SQLCHAR col_name[256];
        SQLCHAR col_data[256];
        SQLSMALLINT col_name_length;
        SQLSMALLINT num_cols;

        int rows = count_rows(db);
        if (rows < 0) {
            printf("Error count rows\n");
            return -1;
        } else if (rows == 0) {
            printf("Table is empty\n");
            return 0;
        }

        ret = SQLNumResultCols(db.get_hstmt(), &num_cols);
        for (int i = 1; i <= num_cols; i++) {
            ret = SQLColAttribute(db.get_hstmt(), i, SQL_DESC_NAME, col_name, sizeof(col_name), &col_name_length, NULL);
            if (SQL_SUCCEEDED(ret)) {
                cout << col_name << "\t";
            }
        }
        cout << endl;
        while (SQLFetch(db.get_hstmt()) == SQL_SUCCESS) {
            SQLColAttribute(db.get_hstmt(), 1, SQL_DESC_NAME, col_name, sizeof(col_name), &col_name_length, NULL);
            SQLGetData(db.get_hstmt(), 1, SQL_C_CHAR, col_data, sizeof(col_data), NULL);
            cout << col_data << "\t\t";
            SQLColAttribute(db.get_hstmt(), 2, SQL_DESC_NAME, col_name, sizeof(col_name), &col_name_length, NULL);
            SQLGetData(db.get_hstmt(), 2, SQL_C_CHAR, col_data, sizeof(col_data), NULL);
            cout << col_data << endl;
        }
        return 1;
    }

    int count_rows(Database db) {
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), db.get_hstmt_address());
        int ret = SQLExecDirect(db.get_hstmt(), (SQLCHAR*)"select count(*) from subjects", SQL_NTS);
        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            ret = SQLFetch(db.get_hstmt());
            if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
                int row_count;
                SQLGetData(db.get_hstmt(), 1, SQL_C_LONG, &row_count, sizeof(row_count), NULL);
                SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
                return row_count;
            }
        }
        SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
        return -1;
    }

    // int insert(Database db) override {
        
    // }

    // int update(Database db) override {

    // }

    // int del(Database db) override {

    // }

    // int find(Database db) {

    //}
};

#endif