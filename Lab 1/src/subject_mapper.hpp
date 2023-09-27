#ifndef SUBJECT_MAPPER_HPP

#define SUBJECT_MAPPER_HPP

#include "subject.hpp"
#include "mapper.hpp"

class SubjectMapper : public Mapper {
public:
    void select(Database db) override {
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), db.get_hstmt_address());
	    int ret = SQLExecDirect(db.get_hstmt(), (SQLCHAR*)"select * from subjects;", SQL_NTS);
        if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
            SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
            db.set_ret(-1);
            return;
        }

        SQLCHAR col_name[256];
        SQLCHAR col_data[256];
        SQLSMALLINT col_name_length;
        SQLSMALLINT num_cols;

        int rows = count_rows(db);
        if (rows < 0) {
            printf("Error count rows\n");
            SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
            db.set_ret(-2);
            return;
        } else if (rows == 0) {
            printf("Table is empty\n");
            SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
            db.set_ret(0);
            return;
        }

        ret = SQLNumResultCols(db.get_hstmt(), &num_cols);
        if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
            SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
            db.set_ret(-3);
            return;
        }
        for (int i = 1; i <= num_cols; i++) {
            ret = SQLColAttribute(db.get_hstmt(), i, SQL_DESC_NAME, col_name, sizeof(col_name), &col_name_length, NULL);
            if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
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
        SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
        db.set_ret(0);
    }

    int count_rows(Database db) { // +checking
        int ret = SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), db.get_hstmt_address());
        if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
            SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
            return -1;
        }
        ret = SQLExecDirect(db.get_hstmt(), (SQLCHAR*)"select count(*) from subjects", SQL_NTS);
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

    void insert(Database db) override {
        int ret = SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), db.get_hstmt_address());
        if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
            SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
            db.set_ret(-1);
            return;
        }
        const char* query = "insert into subjects (subject) values (?)";
        ret = SQLPrepare(db.get_hstmt(), (SQLCHAR*)query, SQL_NTS);
        if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
            SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
            db.set_ret(-2);
            return;
        }
        SQLCHAR val1[256];
        printf("Enter subject name:\n");
        scanf("%255s", val1);
        SQLBindParameter(db.get_hstmt(), 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sizeof(val1), 0, val1, 0, NULL);
        ret = SQLExecute(db.get_hstmt());
        if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
            SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
            db.set_ret(-3);
            return;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
        db.set_ret(0);
    }

    void update(Database db) override {
        int ret = SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), db.get_hstmt_address());
        if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
            SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
            db.set_ret(-1);
            return;
        }
        const char* query = "update subjects set subject = ? where subject = ?";
        ret = SQLPrepare(db.get_hstmt(), (SQLCHAR*)query, SQL_NTS);
        if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
            SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
            db.set_ret(-2);
            return;
        }
        SQLCHAR old_val[256], new_val[256];
        printf("Enter the name of the subject you want to change:\n");
        scanf("%255s", old_val);

        // search of the value - checking

        printf("Enter new name:\n");
        scanf("%255s", new_val);
        SQLBindParameter(db.get_hstmt(), 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sizeof(new_val), 0, new_val, 0, NULL);
        SQLBindParameter(db.get_hstmt(), 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sizeof(old_val), 0, old_val, 0, NULL);
        ret = SQLExecute(db.get_hstmt());
        if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
            SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
            db.set_ret(-3);
            return;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
        db.set_ret(0);
    }

    void del(Database db) override {
        int ret = SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), db.get_hstmt_address());
        if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
            SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
            db.set_ret(-1);
            return;
        }
        const char *query = "delete from subjects where subject = ?";
        char name[256];
        ret = SQLPrepare(db.get_hstmt(), (SQLCHAR*)query, SQL_NTS);
        if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
            SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
            db.set_ret(-2);
            return;
        }
        printf("Enter subject for deletion:\n");
        scanf("%255s", name);

        // search of the value - checking

        SQLBindParameter(db.get_hstmt(), 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sizeof(name), 0, name, 0, NULL);
        ret = SQLExecute(db.get_hstmt());
        if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
            SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
            db.set_ret(-3);
            return;
        }
        SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
        db.set_ret(0);
    }

    //void search(Database db) override {

    //}
};

#endif