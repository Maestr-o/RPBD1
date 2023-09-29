#ifndef DATABASE_HPP

#include <iostream>
#include <windows.h>
#include <odbcinst.h>
#include <sqlext.h>
#include <string.h>

#define DATABASE_HPP

using namespace std;

class Database {
private:
    SQLHENV henv;
    SQLHDBC hdbc;
    SQLHSTMT hstmt;
    SQLRETURN ret;
public:
    Database();
    
    SQLHENV get_henv();
    SQLHDBC get_hdbc();
    SQLHSTMT get_hstmt();
    SQLHSTMT* get_hstmt_address();
    SQLRETURN get_ret();
    void set_henv(SQLHENV x);
    void set_hdbc(SQLHDBC x);
    void set_hstmt(SQLHSTMT x);
    void set_ret(SQLRETURN x);

    int connect();
    int init_tables();
    void disconnect();
    int exec(const char *cmd);
    int check_exec(int ret);
};

#endif