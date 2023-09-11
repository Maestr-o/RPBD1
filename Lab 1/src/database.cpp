#include "database.h"

using namespace std;

database::database() {
    int ret = connect();
    if (ret == 0) cout << "Connection successful" << endl;
    else cout << "Error " << ret << endl;
}

int database::connect() {
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv); //выделение ресурсов для работы с ODBC
	if (retcode < 0)
		return 1;
	retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, SQL_NTS); // установка атрибутов окружения
	if (retcode < 0)
		return 2;
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
	if (retcode < 0)
		return 3;
	retcode = SQLConnect(hdbc, (SQLWCHAR*)DSN, SQL_NTS,
		(SQLWCHAR*)USER, SQL_NTS, (SQLWCHAR*)PASS, SQL_NTS); //подключение
	if (retcode < 0)
		return 4;
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt); // выделение дескриптора запроса
	if (retcode < 0)
		return 5;
	return 0;
}

int database::init_tables() {
    int ret = 0;
	ret = SQLExecDirect(hstmt, (SQLWCHAR*)L"\
		create table if not exists enrollee(en_id serial primary key, address text, parents_address text);\
		alter table enrollee owner to us", SQL_NTS);
	if (ret < 0)
		return 1;
	ret = SQLExecDirect(hstmt, (SQLWCHAR*)L"\
		create table if not exists passport(en_id integer references enrollee(en_id), first_name text, last_name text, surname text, sex bool, cityzenship text, birth date, pass_serial integer, pass_num integer);\
		alter table passport owner to us", SQL_NTS);
	if (ret < 0)
		return 2;
	ret = SQLExecDirect(hstmt, (SQLWCHAR*)L"\
		create table if not exists education(en_id integer references enrollee(en_id), faculty text, speciality text, university text, year_of_ending integer, type_of_doc text, doc_num integer, foreign_lang text, gpa float, ege integer);\
		alter table education owner to us", SQL_NTS);
	if (ret < 0)
		return 3;
	ret = SQLExecDirect(hstmt, (SQLWCHAR*)L"\
		create table if not exists grades(grade_id serial primary key, grade integer not null);\
		alter table grades owner to us", SQL_NTS);
	if (ret < 0)
		return 4;
	ret = SQLExecDirect(hstmt, (SQLWCHAR*)L"\
		create table if not exists subjects(subject_id serial primary key, subject text not null);\
		alter table subjects owner to us", SQL_NTS);
	if (ret < 0)
		return 5;
	ret = SQLExecDirect(hstmt, (SQLWCHAR*)L"\
		create table if not exists res_diploma(res_dip_id serial primary key, grade_id integer references grades(grade_id), subject_id integer references subjects(subject_id));\
		alter table res_diploma owner to us", SQL_NTS);
	if (ret < 0)
		return 6;
	ret = SQLExecDirect(hstmt, (SQLWCHAR*)L"\
		create table if not exists edu_grades(en_id integer references enrollee(en_id), res_dip_id integer references res_diploma(res_dip_id));\
		alter table edu_grades owner to us", SQL_NTS);
	if (ret < 0)
		return 7;
	ret = SQLExecDirect(hstmt, (SQLWCHAR*)L"\
		create table if not exists auditories(auditory_id serial primary key, auditory integer not null);\
		alter table auditories owner to us", SQL_NTS);
	if (ret < 0)
		return 8;
	ret = SQLExecDirect(hstmt, (SQLWCHAR*)L"\
		create table if not exists res_exam(res_exam_id serial primary key, group_num integer, auditory_id integer references auditories(auditory_id), subject_id integer references subjects(subject_id), grade_id integer references grades(grade_id));\
		alter table res_exam owner to us", SQL_NTS);
	if (ret < 0)
		return 9;
	ret = SQLExecDirect(hstmt, (SQLWCHAR*)L"\
		create table if not exists exam_grades(en_id integer references enrollee(en_id), res_exam_id integer references res_exam(res_exam_id));\
		alter table exam_grades owner to us", SQL_NTS);
	if (ret < 0)
		return 10;
	return 0;
}

void database::disconnect() {
	SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	SQLDisconnect(hdbc);
	SQLFreeHandle(SQL_HANDLE_DBC, hdbc); // освобождение дескриптора соединения
	SQLFreeHandle(SQL_HANDLE_ENV, henv); // освобождение окружения
}