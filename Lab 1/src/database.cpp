#include "database.h"

database::database() {
    int ret = connect();
    if (ret == 0) cout << "Connection successful" << endl;
    else cout << "Connection error " << ret << endl;
}

int database::connect() {
	// Инициализация среды
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
    // Создание соединения
    SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
    // Установка параметров подключения
	return SQLConnect(hdbc, (SQLCHAR*)"mydsn", SQL_NTS, (SQLCHAR*)"us", SQL_NTS, (SQLCHAR*)"1234", SQL_NTS);
}

int database::init_tables() {
	int ret;
	SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	ret = SQLExecDirect(hstmt, (SQLCHAR*)"\
		create table if not exists enrollee(en_id serial primary key, address text, parents_address text);\
		alter table enrollee owner to us", SQL_NTS);
	SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		return 1;
	SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	ret = SQLExecDirect(hstmt, (SQLCHAR*)"\
		create table if not exists passport(en_id integer references enrollee(en_id), first_name text, last_name text, surname text, sex bool, cityzenship text, birth date, pass_serial integer, pass_num integer);\
		alter table passport owner to us", SQL_NTS);
	SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		return 2;
	SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	ret = SQLExecDirect(hstmt, (SQLCHAR*)"\
		create table if not exists education(en_id integer references enrollee(en_id), faculty text, speciality text, university text, year_of_ending integer, type_of_doc text, doc_num integer, foreign_lang text, gpa float, ege integer);\
		alter table education owner to us", SQL_NTS);
	SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		return 3;
	SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	ret = SQLExecDirect(hstmt, (SQLCHAR*)"\
		create table if not exists grades(grade_id serial primary key, grade integer not null);\
		alter table grades owner to us", SQL_NTS);
	SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		return 4;
	SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	ret = SQLExecDirect(hstmt, (SQLCHAR*)"\
		create table if not exists subjects(subject_id serial primary key, subject text not null);\
		alter table subjects owner to us", SQL_NTS);
	SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		return 5;
	SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	ret = SQLExecDirect(hstmt, (SQLCHAR*)"\
		create table if not exists res_diploma(res_dip_id serial primary key, grade_id integer references grades(grade_id), subject_id integer references subjects(subject_id));\
		alter table res_diploma owner to us", SQL_NTS);
	SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		return 6;
	SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	ret = SQLExecDirect(hstmt, (SQLCHAR*)"\
		create table if not exists edu_grades(en_id integer references enrollee(en_id), res_dip_id integer references res_diploma(res_dip_id));\
		alter table edu_grades owner to us", SQL_NTS);
	SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		return 7;
	SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	ret = SQLExecDirect(hstmt, (SQLCHAR*)"\
		create table if not exists auditories(auditory_id serial primary key, auditory integer not null);\
		alter table auditories owner to us", SQL_NTS);
	SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		return 8;
	SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	ret = SQLExecDirect(hstmt, (SQLCHAR*)"\
		create table if not exists res_exam(res_exam_id serial primary key, group_num integer, auditory_id integer references auditories(auditory_id), subject_id integer references subjects(subject_id), grade_id integer references grades(grade_id));\
		alter table res_exam owner to us", SQL_NTS);
	SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		return 9;
	SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	ret = SQLExecDirect(hstmt, (SQLCHAR*)"\
		create table if not exists exam_grades(en_id integer references enrollee(en_id), res_exam_id integer references res_exam(res_exam_id));\
		alter table exam_grades owner to us", SQL_NTS);
	SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		return 10;
	return 0;
}

void database::disconnect() {
	SQLDisconnect(hdbc);
	SQLFreeHandle(SQL_HANDLE_DBC, hdbc); // освобождение дескриптора соединения
	SQLFreeHandle(SQL_HANDLE_ENV, henv); // освобождение окружения
}
