#ifndef DATABASE_H

#include <iostream>
#include <odbcinst.h>
#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>

#define DATABASE_H
#define USER L"us"
#define PASS L"1234"
#define DSN L"psqldsn"

using namespace std;

class database {
public:
    SQLHENV     henv;     	// дескриптор окружения
    SQLHDBC     hdbc; 		// дескриптор соединения
    SQLHSTMT    hstmt; 	    // дескриптор оператора
    SQLRETURN   retcode; 	// код возврата

    int connect();
    int init_tables();
    void disconnect();

    database();
};

#endif