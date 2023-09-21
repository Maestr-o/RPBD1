#ifndef DATABASE_HPP

#include <iostream>
#include <odbcinst.h>
#include <sqlext.h>

#define DATABASE_HPP

using namespace std;

class Database {
private:
    SQLHENV     henv;     	// дескриптор окружения
    SQLHDBC     hdbc; 		// дескриптор соединения
    SQLHSTMT    hstmt; 	    // дескриптор оператора
public:
    Database();
    SQLHENV get_henv();
    SQLHDBC get_hdbc();
    SQLHSTMT get_hstmt();
    void set_henv(SQLHENV x);
    void set_hdbc(SQLHDBC x);
    void set_hstmt(SQLHSTMT x);
    int connect();
    int init_tables();
    void disconnect();
    int exec(const char *cmd);
    int exec_cont(const char* cmd);
    int check_exec(int ret);
};

#endif