#ifndef SUBJECT_HPP

#define SUBJECT_HPP

#include <iostream>
#include "mapper.hpp"

class Subject : public Mapper {
private:
    int id;
    std::string name;
public:
    int get_id() {
        return id;
    }

    std::string get_name() {
        return name;
    }

    void set_id(int x) {
        id = x;
    }

    void set_name(std::string x) {
        name = x;
    }

    int select(Database db) override {
        int ret = db.exec_cont("select * from subjects;");
        if (!SQL_SUCCEEDED(ret)) return 0;
        SQLCHAR col_name[256];
        SQLCHAR col_data[256];
        SQLSMALLINT col_name_length;
        SQLSMALLINT num_cols;
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
            cout << col_data <<  endl;
        }
        return 1;
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