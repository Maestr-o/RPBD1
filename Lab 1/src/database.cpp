#include "database.hpp"

Database::Database() {
    ret = connect();
}

SQLHENV Database::get_henv() {
	return henv;
}

SQLHDBC Database::get_hdbc() {
	return hdbc;
}

SQLHSTMT Database::get_hstmt() {
	return hstmt;
}

SQLHSTMT* Database::get_hstmt_address() {
	return &hstmt;
}

SQLRETURN Database::get_ret() {
	return ret;
}

void Database::set_henv(SQLHENV x) {
	henv = x;
}

void Database::set_hdbc(SQLHDBC x) {
	hdbc = x;
}

void Database::set_hstmt(SQLHSTMT x) {
	hstmt = x;
}

int Database::connect() {
	SQLCHAR* dsn = (SQLCHAR*)"psqldsn";
	SQLCHAR* user = (SQLCHAR*)"us";
	SQLCHAR* pass = (SQLCHAR*)"1234";
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
    SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
	return SQLConnect(hdbc, dsn, SQL_NTS, user, SQL_NTS, pass, SQL_NTS);
}

int Database::init_tables() {
	if (!check_exec(exec("create table if not exists enrollee(en_id serial primary key, address text, parents_address text);\
		alter table enrollee owner to us")))
		return 1;
	if (!check_exec(exec("create table if not exists passport(en_id integer references enrollee(en_id), first_name text, last_name text, surname text, sex bool, cityzenship text, birth date, pass_serial integer, pass_num integer);\
		alter table passport owner to us")))
		return 2;
	if (!check_exec(exec("create table if not exists education(en_id integer references enrollee(en_id), faculty text, speciality text, university text, year_of_ending integer, type_of_doc text, doc_num integer, foreign_lang text, gpa float, ege integer);\
		alter table education owner to us")))
		return 3;
	if (!check_exec(exec("create table if not exists grades(grade_id serial primary key, grade integer not null);\
		alter table grades owner to us")))
		return 4;
	if (!check_exec(exec("create table if not exists subjects(subject_id serial primary key, subject text not null);\
		alter table subjects owner to us")))
		return 5;
	if (!check_exec(exec("create table if not exists res_diploma(res_dip_id serial primary key, grade_id integer references grades(grade_id), subject_id integer references subjects(subject_id));\
		alter table res_diploma owner to us")))
		return 6;
	if (!check_exec(exec("create table if not exists edu_grades(en_id integer references enrollee(en_id), res_dip_id integer references res_diploma(res_dip_id));\
		alter table edu_grades owner to us")))
		return 7;
	if (!check_exec(exec("create table if not exists auditories(auditory_id serial primary key, auditory integer not null);\
		alter table auditories owner to us")))
		return 8;
	if (!check_exec(exec("create table if not exists res_exam(res_exam_id serial primary key, group_num integer, auditory_id integer references auditories(auditory_id), subject_id integer references subjects(subject_id), grade_id integer references grades(grade_id));\
		alter table res_exam owner to us")))
		return 9;
	if (!check_exec(exec("create table if not exists exam_grades(en_id integer references enrollee(en_id), res_exam_id integer references res_exam(res_exam_id));\
		alter table exam_grades owner to us")))
		return 10;
	return 0;
}

void Database::disconnect() {
	SQLDisconnect(hdbc);
	SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
	SQLFreeHandle(SQL_HANDLE_ENV, henv);
}

int Database::exec(const char* cmd) {
	int ret;
	SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	ret = SQLExecDirect(hstmt, (SQLCHAR*)cmd, SQL_NTS);
	SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
	return ret;
}

int Database::exec_cont(const char* cmd) {
	int ret;
	SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	ret = SQLExecDirect(hstmt, (SQLCHAR*)cmd, SQL_NTS);
	return ret;
}

int Database::check_exec(int ret) {
	if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO)
		return 0;
	else
		return 1;
}