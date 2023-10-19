#ifndef ENROLLEE_MAPPER_HPP

#define ENROLLEE_MAPPER_HPP

#include "enrollee.hpp"
#include "database.hpp"

using namespace std;

class EnrolleeMapper {
   public:
    Database db;
    list<Enrollee> applicants;

    EnrolleeMapper(Database *d) {
        db = *d;
    }

    void get_all() {
        SQLHSTMT hstmt;
        applicants.clear();
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);
        SQLExecDirect(hstmt, (SQLCHAR *)"select enrollee.en_id, first_name, last_name, surname,\
            sex, cityzenship, birth, pass_serial, pass_num, address, parents_address, faculty, speciality,\
            university, year_of_ending, type_of_doc, doc_num, foreign_lang, gpa, ege from enrollee,\
            passport, education where enrollee.en_id=passport.en_id and enrollee.en_id=education.en_id;",
                      SQL_NTS);

        SQLCHAR str_data[1000];
        SQLINTEGER int_data;
        SQL_TIMESTAMP_STRUCT timestamp;

        for (int i = 1; SQLFetch(hstmt) == SQL_SUCCESS; i++) {
            Enrollee enrollee;
            Passport passport;
            Education education;

            SQLGetData(hstmt, 1, SQL_C_LONG, &int_data, sizeof(int_data), NULL);
            passport.set_id(int_data);
            enrollee.set_id(int_data);
            education.set_id(int_data);
            SQLGetData(hstmt, 2, SQL_C_CHAR, str_data, sizeof(str_data), NULL);
            passport.set_first_name(sqlchar_to_string(str_data, strlen((char *)str_data)));
            SQLGetData(hstmt, 3, SQL_C_CHAR, str_data, sizeof(str_data), NULL);
            passport.set_last_name(sqlchar_to_string(str_data, strlen((char *)str_data)));
            SQLGetData(hstmt, 4, SQL_C_CHAR, str_data, sizeof(str_data), NULL);
            passport.set_surname(sqlchar_to_string(str_data, strlen((char *)str_data)));
            SQLGetData(hstmt, 5, SQL_C_LONG, &int_data, sizeof(int_data), NULL);
            passport.set_sex(int_data);
            SQLGetData(hstmt, 6, SQL_C_CHAR, str_data, sizeof(str_data), NULL);
            passport.set_cityzenship(sqlchar_to_string(str_data, strlen((char *)str_data)));
            SQLGetData(hstmt, 7, SQL_C_TYPE_TIMESTAMP, &timestamp, sizeof(timestamp), NULL);
            string date =
                to_string(timestamp.day) + "-" + to_string(timestamp.month) + "-" + to_string(timestamp.year);
            passport.set_birth(date);
            SQLGetData(hstmt, 8, SQL_C_LONG, &int_data, sizeof(int_data), NULL);
            passport.set_pass_serial(int_data);
            SQLGetData(hstmt, 9, SQL_C_LONG, &int_data, sizeof(int_data), NULL);
            passport.set_pass_num(int_data);
            SQLGetData(hstmt, 10, SQL_C_CHAR, str_data, sizeof(str_data), NULL);
            enrollee.set_address(sqlchar_to_string(str_data, strlen((char *)str_data)));
            SQLGetData(hstmt, 11, SQL_C_CHAR, str_data, sizeof(str_data), NULL);
            enrollee.set_parents_address(sqlchar_to_string(str_data, strlen((char *)str_data)));
            SQLGetData(hstmt, 12, SQL_C_CHAR, str_data, sizeof(str_data), NULL);
            education.set_faculty(sqlchar_to_string(str_data, strlen((char *)str_data)));
            SQLGetData(hstmt, 13, SQL_C_CHAR, str_data, sizeof(str_data), NULL);
            education.set_speciality(sqlchar_to_string(str_data, strlen((char *)str_data)));
            SQLGetData(hstmt, 14, SQL_C_CHAR, str_data, sizeof(str_data), NULL);
            education.set_university(sqlchar_to_string(str_data, strlen((char *)str_data)));
            SQLGetData(hstmt, 15, SQL_C_LONG, &int_data, sizeof(int_data), NULL);
            education.set_year_of_ending(int_data);
            SQLGetData(hstmt, 16, SQL_C_CHAR, str_data, sizeof(str_data), NULL);
            education.set_type_of_doc(sqlchar_to_string(str_data, strlen((char *)str_data)));
            SQLGetData(hstmt, 17, SQL_C_LONG, &int_data, sizeof(int_data), NULL);
            education.set_doc_num(int_data);
            SQLGetData(hstmt, 18, SQL_C_CHAR, str_data, sizeof(str_data), NULL);
            education.set_foreign_lang(sqlchar_to_string(str_data, strlen((char *)str_data)));
            SQLGetData(hstmt, 19, SQL_C_LONG, &int_data, sizeof(int_data), NULL);
            education.set_gpa(int_data);
            SQLGetData(hstmt, 20, SQL_C_LONG, &int_data, sizeof(int_data), NULL);
            education.set_gpa(int_data);

            enrollee.set_passport(passport);
            enrollee.set_education(education);
            applicants.push_back(enrollee);
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    }

    void insert(Database db, Enrollee obj) {
        SQLHSTMT hstmt;
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);

        char query[1000];
        sprintf(query,
                "insert into enrollee(address, parents_address) values(\'%s\', \'%s\') returning en_id;",
                obj.get_address().c_str(), obj.get_parents_address().c_str());
        SQLPrepare(hstmt, (SQLCHAR *)query, SQL_NTS);
        SQLExecute(hstmt);

        int index;
        SQLFetch(hstmt);
        SQLGetData(hstmt, 1, SQL_C_SLONG, &index, sizeof(index), NULL);
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);

        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);
        sprintf(query,
                "insert into passport(en_id, first_name, last_name, surname, sex, cityzenship,\
            birth, pass_serial, pass_num) values(\
            %d, \'%s\', \'%s\', \'%s\', %d, \'%s\', \'%s\', %d, %d);",
                index, obj.get_passport().get_first_name().c_str(),
                obj.get_passport().get_last_name().c_str(), obj.get_passport().get_surname().c_str(),
                obj.get_passport().get_sex(), obj.get_passport().get_cityzenship().c_str(),
                obj.get_passport().get_birth().c_str(), obj.get_passport().get_pass_serial(),
                obj.get_passport().get_pass_num());
        SQLPrepare(hstmt, (SQLCHAR *)query, SQL_NTS);
        SQLExecute(hstmt);

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);

        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);
        sprintf(query,
                "insert into education(en_id, faculty, speciality, university, year_of_ending,\
            type_of_doc, doc_num, foreign_lang, gpa, ege) values(\
            %d, \'%s\', \'%s\', \'%s\', %d, \'%s\', %d, \'%s\', %.2f, %d);",
                index, obj.get_education().get_faculty().c_str(),
                obj.get_education().get_speciality().c_str(), obj.get_education().get_university().c_str(),
                obj.get_education().get_year_of_ending(), obj.get_education().get_type_of_doc().c_str(),
                obj.get_education().get_doc_num(), obj.get_education().get_foreign_lang().c_str(),
                obj.get_education().get_gpa(), obj.get_education().get_ege());
        SQLPrepare(hstmt, (SQLCHAR *)query, SQL_NTS);
        SQLExecute(hstmt);

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        applicants.push_back(obj);
    }

    void update(Database db, Enrollee old_obj, Enrollee new_obj) {
        del(db, old_obj);

        SQLHSTMT hstmt;
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);
        char query[1000];
        sprintf(query, "insert into enrollee(en_id, address, parents_address) values(%d, \'%s\', \'%s\');",
                old_obj.get_id(), new_obj.get_address().c_str(), new_obj.get_parents_address().c_str());
        SQLPrepare(hstmt, (SQLCHAR *)query, SQL_NTS);
        SQLExecute(hstmt);

        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);
        sprintf(query,
                "insert into passport(en_id, first_name, last_name, surname, sex, cityzenship,\
            birth, pass_serial, pass_num) values(\
            %d, \'%s\', \'%s\', \'%s\', %d, \'%s\', \'%s\', %d, %d);",
                old_obj.get_id(), new_obj.get_passport().get_first_name().c_str(),
                new_obj.get_passport().get_last_name().c_str(), new_obj.get_passport().get_surname().c_str(),
                new_obj.get_passport().get_sex(), new_obj.get_passport().get_cityzenship().c_str(),
                new_obj.get_passport().get_birth().c_str(), new_obj.get_passport().get_pass_serial(),
                new_obj.get_passport().get_pass_num());
        SQLPrepare(hstmt, (SQLCHAR *)query, SQL_NTS);
        SQLExecute(hstmt);

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);

        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);
        sprintf(query,
                "insert into education(en_id, faculty, speciality, university, year_of_ending,\
            type_of_doc, doc_num, foreign_lang, gpa, ege) values(\
            %d, \'%s\', \'%s\', \'%s\', %d, \'%s\', %d, \'%s\', %.2f, %d);",
                old_obj.get_id(), new_obj.get_education().get_faculty().c_str(),
                new_obj.get_education().get_speciality().c_str(),
                new_obj.get_education().get_university().c_str(),
                new_obj.get_education().get_year_of_ending(),
                new_obj.get_education().get_type_of_doc().c_str(), new_obj.get_education().get_doc_num(),
                new_obj.get_education().get_foreign_lang().c_str(), new_obj.get_education().get_gpa(),
                new_obj.get_education().get_ege());
        SQLPrepare(hstmt, (SQLCHAR *)query, SQL_NTS);
        SQLExecute(hstmt);
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    }

    void del(Database db, Enrollee obj) {
        SQLHSTMT hstmt;
        char query[1000];

        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);
        sprintf(query, "delete from passport where en_id = %d;", obj.get_id());
        SQLPrepare(hstmt, (SQLCHAR *)(query), SQL_NTS);
        SQLExecute(hstmt);
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);

        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);
        sprintf(query, "delete from education where en_id = %d;", obj.get_id());
        SQLPrepare(hstmt, (SQLCHAR *)(query), SQL_NTS);
        SQLExecute(hstmt);
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);

        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);
        sprintf(query, "delete from res_diploma where en_id = %d;", obj.get_id());
        SQLPrepare(hstmt, (SQLCHAR *)(query), SQL_NTS);
        SQLExecute(hstmt);
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);

        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);
        sprintf(query, "delete from res_exam where en_id = %d;", obj.get_id());
        SQLPrepare(hstmt, (SQLCHAR *)(query), SQL_NTS);
        SQLExecute(hstmt);
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);

        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);
        sprintf(query, "delete from enrollee where en_id = %d;", obj.get_id());
        SQLPrepare(hstmt, (SQLCHAR *)(query), SQL_NTS);
        SQLExecute(hstmt);
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);

        applicants.remove(obj);
    }

    string sqlchar_to_string(SQLCHAR *sqlchar_data, int data_size) {
        return string(reinterpret_cast<char *>(sqlchar_data), data_size);
    }

    SQLCHAR *string_to_sqlchar(const std::string &input) {
        SQLCHAR *result = new SQLCHAR[input.size() + 1];
        strcpy(reinterpret_cast<char *>(result), input.c_str());
        return result;
    }
};

#endif