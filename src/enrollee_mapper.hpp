#ifndef ENROLLEE_MAPPER_HPP

#define ENROLLEE_MAPPER_HPP
#define CHECK_LAST_OPERATION                                \
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) \
    {                                                       \
        SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());     \
        db.set_ret(-1);                                     \
        return;                                             \
    }

#include "enrollee.hpp"
#include "database.hpp"

using namespace std;

class EnrolleeMapper
{
public:
    Database db;
    list<Enrollee> applicants;

    EnrolleeMapper(Database *d)
    {
        db = *d;
    }

    void get_all()
    {
        applicants.clear();
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), db.get_hstmt_address());
        int ret = SQLExecDirect(db.get_hstmt(), (SQLCHAR *)"select enrollee.en_id, first_name, last_name, surname,\
            sex, cityzenship, birth, pass_serial, pass_num, address, parents_address, faculty, speciality,\
            university, year_of_ending, type_of_doc, doc_num, foreign_lang, gpa, ege from enrollee,\
            passport, education where enrollee.en_id=passport.en_id and enrollee.en_id=education.en_id;",
                                SQL_NTS);
        CHECK_LAST_OPERATION
        SQLCHAR str_data[256];
        SQLINTEGER int_data;
        SQL_TIMESTAMP_STRUCT timestamp;

        for (int i = 1; SQLFetch(db.get_hstmt()) == SQL_SUCCESS; i++)
        {
            Enrollee enrollee;
            Passport passport;
            Education education;

            SQLGetData(db.get_hstmt(), 1, SQL_C_LONG, &int_data, sizeof(int_data), NULL);
            passport.set_id(int_data);
            enrollee.set_id(int_data);
            education.set_id(int_data);
            SQLGetData(db.get_hstmt(), 2, SQL_C_CHAR, str_data, sizeof(str_data), NULL);
            passport.set_first_name(sqlchar_to_string(str_data, strlen((char *)str_data)));
            SQLGetData(db.get_hstmt(), 3, SQL_C_CHAR, str_data, sizeof(str_data), NULL);
            passport.set_last_name(sqlchar_to_string(str_data, strlen((char *)str_data)));
            SQLGetData(db.get_hstmt(), 4, SQL_C_CHAR, str_data, sizeof(str_data), NULL);
            passport.set_surname(sqlchar_to_string(str_data, strlen((char *)str_data)));
            SQLGetData(db.get_hstmt(), 5, SQL_C_LONG, &int_data, sizeof(int_data), NULL);
            passport.set_sex(int_data);
            SQLGetData(db.get_hstmt(), 6, SQL_C_CHAR, str_data, sizeof(str_data), NULL);
            passport.set_cityzenship(sqlchar_to_string(str_data, strlen((char *)str_data)));
            SQLGetData(db.get_hstmt(), 7, SQL_C_TYPE_TIMESTAMP, &timestamp, sizeof(timestamp), NULL);
            string date = to_string(timestamp.day) + "-" + to_string(timestamp.month) + "-" + to_string(timestamp.year);
            passport.set_birth(date);
            SQLGetData(db.get_hstmt(), 8, SQL_C_LONG, &int_data, sizeof(int_data), NULL);
            passport.set_pass_serial(int_data);
            SQLGetData(db.get_hstmt(), 9, SQL_C_LONG, &int_data, sizeof(int_data), NULL);
            passport.set_pass_num(int_data);
            SQLGetData(db.get_hstmt(), 10, SQL_C_CHAR, str_data, sizeof(str_data), NULL);
            enrollee.set_address(sqlchar_to_string(str_data, strlen((char *)str_data)));
            SQLGetData(db.get_hstmt(), 11, SQL_C_CHAR, str_data, sizeof(str_data), NULL);
            enrollee.set_parents_address(sqlchar_to_string(str_data, strlen((char *)str_data)));
            SQLGetData(db.get_hstmt(), 12, SQL_C_CHAR, str_data, sizeof(str_data), NULL);
            education.set_faculty(sqlchar_to_string(str_data, strlen((char *)str_data)));
            SQLGetData(db.get_hstmt(), 13, SQL_C_CHAR, str_data, sizeof(str_data), NULL);
            education.set_speciality(sqlchar_to_string(str_data, strlen((char *)str_data)));
            SQLGetData(db.get_hstmt(), 14, SQL_C_CHAR, str_data, sizeof(str_data), NULL);
            education.set_university(sqlchar_to_string(str_data, strlen((char *)str_data)));
            SQLGetData(db.get_hstmt(), 15, SQL_C_LONG, &int_data, sizeof(int_data), NULL);
            education.set_year_of_ending(int_data);
            SQLGetData(db.get_hstmt(), 16, SQL_C_CHAR, str_data, sizeof(str_data), NULL);
            education.set_type_of_doc(sqlchar_to_string(str_data, strlen((char *)str_data)));
            SQLGetData(db.get_hstmt(), 17, SQL_C_LONG, &int_data, sizeof(int_data), NULL);
            education.set_doc_num(int_data);
            SQLGetData(db.get_hstmt(), 18, SQL_C_CHAR, str_data, sizeof(str_data), NULL);
            education.set_foreign_lang(sqlchar_to_string(str_data, strlen((char *)str_data)));
            SQLGetData(db.get_hstmt(), 19, SQL_C_LONG, &int_data, sizeof(int_data), NULL);
            education.set_gpa(int_data);
            SQLGetData(db.get_hstmt(), 20, SQL_C_LONG, &int_data, sizeof(int_data), NULL);
            education.set_gpa(int_data);

            enrollee.set_passport(passport);
            enrollee.set_education(education);
            enrollee.set_diploma(get_res_diploma(enrollee.get_id()));
            enrollee.set_exams(get_res_exams(enrollee.get_id()));
            applicants.push_back(enrollee);
        }
        SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
        db.set_ret(0);
    }

    list<ResDiploma> get_res_diploma(int id)
    {
        list<ResDiploma> results;
        SQLHSTMT hstmt;
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);

        char query[256];
        sprintf(query, "select grades.grade_id, grade, \
            subjects.subject_id, subject from res_diploma, grades, subjects \
            where res_diploma.grade_id=grades.grade_id and \
            res_diploma.subject_id=subjects.subject_id and en_id=%d;",
                id);

        SQLExecDirect(hstmt, (SQLCHAR *)query, SQL_NTS);

        int data;
        SQLCHAR str[256];

        for (int i = 1; SQLFetch(hstmt) == SQL_SUCCESS; i++)
        {
            ResDiploma obj;
            Grade grade;
            Subject subject;
            obj.set_id(id);
            SQLGetData(hstmt, 1, SQL_C_LONG, &data, sizeof(data), NULL);
            grade.set_id(data);
            SQLGetData(hstmt, 2, SQL_C_LONG, &data, sizeof(data), NULL);
            grade.set_grade(data);
            SQLGetData(hstmt, 3, SQL_C_LONG, &data, sizeof(data), NULL);
            subject.set_id(data);
            SQLGetData(hstmt, 4, SQL_C_CHAR, str, sizeof(str), NULL);
            subject.set_name(sqlchar_to_string(str, strlen((char *)str)));

            obj.set_grade(grade);
            obj.set_subject(subject);
            results.push_back(obj);
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        db.set_ret(0);
        return results;
    }

    list<ResExam> get_res_exams(int id)
    {
        list<ResExam> results;
        SQLHSTMT hstmt;
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);

        char query[256];
        sprintf(query, "select group_num, auditories.auditory_id, auditory, grades.grade_id, grade, \
            subjects.subject_id, subject from res_exam, grades, subjects, auditories where \
            res_exam.grade_id=grades.grade_id and res_exam.subject_id=subjects.subject_id and \
            res_exam.auditory_id=auditories.auditory_id and en_id=%d;",
                id);

        SQLExecDirect(hstmt, (SQLCHAR *)query, SQL_NTS); // error

        int data;
        SQLCHAR str[256];

        for (int i = 1; SQLFetch(hstmt) == SQL_SUCCESS; i++)
        {
            ResExam obj;
            Grade grade;
            Subject subject;
            Auditory auditory;
            obj.set_id(id);

            SQLGetData(hstmt, 1, SQL_C_LONG, &data, sizeof(data), NULL);
            obj.set_group_num(data);
            SQLGetData(hstmt, 2, SQL_C_LONG, &data, sizeof(data), NULL);
            auditory.set_id(data);
            SQLGetData(hstmt, 3, SQL_C_LONG, &data, sizeof(data), NULL);
            auditory.set_auditory(data);
            SQLGetData(hstmt, 4, SQL_C_LONG, &data, sizeof(data), NULL);
            grade.set_id(data);
            SQLGetData(hstmt, 5, SQL_C_LONG, &data, sizeof(data), NULL);
            grade.set_grade(data);
            SQLGetData(hstmt, 6, SQL_C_LONG, &data, sizeof(data), NULL);
            subject.set_id(data);
            SQLGetData(hstmt, 7, SQL_C_CHAR, str, sizeof(str), NULL);
            subject.set_name(sqlchar_to_string(str, strlen((char *)str)));

            obj.set_grade(grade);
            obj.set_subject(subject);
            obj.set_auditory(auditory);
            results.push_back(obj);
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        db.set_ret(0);
        return results;
    }

    void insert(Database db, Enrollee obj)
    {
        int ret = SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), db.get_hstmt_address());
        CHECK_LAST_OPERATION
        char query[1000];
        sprintf(query, "insert into enrollee(address, parents_address) values(\'%s\', \'%s\') returning en_id;",
                obj.get_address().c_str(), obj.get_parents_address().c_str());
        ret = SQLPrepare(db.get_hstmt(), (SQLCHAR *)query, SQL_NTS);
        ret = SQLExecute(db.get_hstmt());
        CHECK_LAST_OPERATION
        int index;
        ret = SQLFetch(db.get_hstmt());
        CHECK_LAST_OPERATION
        SQLGetData(db.get_hstmt(), 1, SQL_C_SLONG, &index, sizeof(index), NULL);
        CHECK_LAST_OPERATION
        SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());

        ret = SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), db.get_hstmt_address());
        sprintf(query, "insert into passport(en_id, first_name, last_name, surname, sex, cityzenship,\
            birth, pass_serial, pass_num) values(\
            %d, \'%s\', \'%s\', \'%s\', %d, \'%s\', \'%s\', %d, %d);",
                index,
                obj.get_passport().get_first_name().c_str(), obj.get_passport().get_last_name().c_str(),
                obj.get_passport().get_surname().c_str(), obj.get_passport().get_sex(),
                obj.get_passport().get_cityzenship().c_str(), obj.get_passport().get_birth().c_str(),
                obj.get_passport().get_pass_serial(), obj.get_passport().get_pass_num());
        ret = SQLPrepare(db.get_hstmt(), (SQLCHAR *)query, SQL_NTS);
        ret = SQLExecute(db.get_hstmt());
        CHECK_LAST_OPERATION
        SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());

        ret = SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), db.get_hstmt_address());
        sprintf(query, "insert into education(en_id, faculty, speciality, university, year_of_ending,\
            type_of_doc, doc_num, foreign_lang, gpa, ege) values(\
            %d, \'%s\', \'%s\', \'%s\', %d, \'%s\', %d, \'%s\', %.2f, %d);",
                index, obj.get_education().get_faculty().c_str(),
                obj.get_education().get_speciality().c_str(),
                obj.get_education().get_university().c_str(), obj.get_education().get_year_of_ending(),
                obj.get_education().get_type_of_doc().c_str(), obj.get_education().get_doc_num(),
                obj.get_education().get_foreign_lang().c_str(), obj.get_education().get_gpa(),
                obj.get_education().get_ege());
        ret = SQLPrepare(db.get_hstmt(), (SQLCHAR *)query, SQL_NTS);
        ret = SQLExecute(db.get_hstmt());
        CHECK_LAST_OPERATION
        SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
        db.set_ret(0);
        applicants.push_back(obj);
    }

    void update(Database db, Enrollee old_obj, Enrollee new_obj)
    {
        del(db, old_obj);

        int ret = SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), db.get_hstmt_address());
        CHECK_LAST_OPERATION

        char query[1000];
        sprintf(query, "insert into enrollee(en_id, address, parents_address) values(%d, \'%s\', \'%s\');",
                old_obj.get_id(), new_obj.get_address().c_str(), new_obj.get_parents_address().c_str());
        ret = SQLPrepare(db.get_hstmt(), (SQLCHAR *)query, SQL_NTS);
        ret = SQLExecute(db.get_hstmt());
        CHECK_LAST_OPERATION

        ret = SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), db.get_hstmt_address());
        sprintf(query, "insert into passport(en_id, first_name, last_name, surname, sex, cityzenship,\
            birth, pass_serial, pass_num) values(\
            %d, \'%s\', \'%s\', \'%s\', %d, \'%s\', \'%s\', %d, %d);",
                old_obj.get_id(),
                new_obj.get_passport().get_first_name().c_str(), new_obj.get_passport().get_last_name().c_str(),
                new_obj.get_passport().get_surname().c_str(), new_obj.get_passport().get_sex(),
                new_obj.get_passport().get_cityzenship().c_str(), new_obj.get_passport().get_birth().c_str(),
                new_obj.get_passport().get_pass_serial(), new_obj.get_passport().get_pass_num());
        ret = SQLPrepare(db.get_hstmt(), (SQLCHAR *)query, SQL_NTS);
        ret = SQLExecute(db.get_hstmt());
        CHECK_LAST_OPERATION
        SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());

        ret = SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), db.get_hstmt_address());
        sprintf(query, "insert into education(en_id, faculty, speciality, university, year_of_ending,\
            type_of_doc, doc_num, foreign_lang, gpa, ege) values(\
            %d, \'%s\', \'%s\', \'%s\', %d, \'%s\', %d, \'%s\', %.2f, %d);",
                old_obj.get_id(), new_obj.get_education().get_faculty().c_str(),
                new_obj.get_education().get_speciality().c_str(),
                new_obj.get_education().get_university().c_str(), new_obj.get_education().get_year_of_ending(),
                new_obj.get_education().get_type_of_doc().c_str(), new_obj.get_education().get_doc_num(),
                new_obj.get_education().get_foreign_lang().c_str(), new_obj.get_education().get_gpa(),
                new_obj.get_education().get_ege());
        ret = SQLPrepare(db.get_hstmt(), (SQLCHAR *)query, SQL_NTS);
        ret = SQLExecute(db.get_hstmt());
        CHECK_LAST_OPERATION
        SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());
        db.set_ret(0);
    }

    void del(Database db, Enrollee obj)
    {
        int ret = SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), db.get_hstmt_address());
        CHECK_LAST_OPERATION
        char query[1000];
        sprintf(query, "delete from passport where en_id = %d;", obj.get_id());
        ret = SQLPrepare(db.get_hstmt(), (SQLCHAR *)(query), SQL_NTS);
        ret = SQLExecute(db.get_hstmt());
        CHECK_LAST_OPERATION
        SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());

        ret = SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), db.get_hstmt_address());
        CHECK_LAST_OPERATION
        sprintf(query, "delete from education where en_id = %d;", obj.get_id());
        ret = SQLPrepare(db.get_hstmt(), (SQLCHAR *)(query), SQL_NTS);
        ret = SQLExecute(db.get_hstmt());
        CHECK_LAST_OPERATION
        SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());

        ret = SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), db.get_hstmt_address());
        CHECK_LAST_OPERATION
        sprintf(query, "delete from enrollee where en_id = %d;", obj.get_id());
        ret = SQLPrepare(db.get_hstmt(), (SQLCHAR *)(query), SQL_NTS);
        ret = SQLExecute(db.get_hstmt());
        CHECK_LAST_OPERATION
        SQLFreeHandle(SQL_HANDLE_STMT, db.get_hstmt());

        applicants.remove(obj);
        db.set_ret(0);
    }

    string sqlchar_to_string(SQLCHAR *sqlchar_data, int data_size)
    {
        return string(reinterpret_cast<char *>(sqlchar_data), data_size);
    }

    SQLCHAR *string_to_sqlchar(const std::string &input)
    {
        SQLCHAR *result = new SQLCHAR[input.size() + 1];
        strcpy(reinterpret_cast<char *>(result), input.c_str());
        return result;
    }
};

#endif