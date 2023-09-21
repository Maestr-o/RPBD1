#ifndef DATABASE_H

#include <iostream>
#include <odbcinst.h>
#include <sqlext.h>

#define DATABASE_H

using namespace std;

class database {
public:
    SQLHENV     henv;     	// дескриптор окружения
    SQLHDBC     hdbc; 		// дескриптор соединения
    SQLHSTMT    hstmt; 	    // дескриптор оператора

    int connect();
    int init_tables();
    void disconnect();

    database();
};

#endif