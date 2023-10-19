#ifndef EXAM_MAPPER_HPP

#define EXAM_MAPPER_HPP

#include <list>

#include "res_exam.hpp"
#include "grade.hpp"
#include "subject.hpp"
#include "database.hpp"
#include "auditory.hpp"

using namespace std;

class ExamMapper {
   public:
    Database db;
    list<ResExam> results;

    ExamMapper(Database *d) {
        db = *d;
    }

    void get_all() {
        results.clear();
        SQLHSTMT hstmt;
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);

        char query[1000];
        sprintf(query,
                "select en_id, group_num, auditories.auditory_id, auditory, grades.grade_id, grade, \
            subjects.subject_id, subject from res_exam, grades, subjects, auditories where \
            res_exam.grade_id=grades.grade_id and res_exam.subject_id=subjects.subject_id and \
            res_exam.auditory_id=auditories.auditory_id;");

        SQLExecDirect(hstmt, (SQLCHAR *)query, SQL_NTS);

        int data;
        SQLCHAR str[1000];

        for (int i = 1; SQLFetch(hstmt) == SQL_SUCCESS; i++) {
            ResExam obj;
            Grade grade;
            Subject subject;
            Auditory auditory;
            SQLGetData(hstmt, 1, SQL_C_LONG, &data, sizeof(data), NULL);
            obj.set_id(data);
            SQLGetData(hstmt, 2, SQL_C_LONG, &data, sizeof(data), NULL);
            obj.set_group_num(data);
            SQLGetData(hstmt, 3, SQL_C_LONG, &data, sizeof(data), NULL);
            auditory.set_id(data);
            SQLGetData(hstmt, 4, SQL_C_LONG, &data, sizeof(data), NULL);
            auditory.set_auditory(data);
            SQLGetData(hstmt, 5, SQL_C_LONG, &data, sizeof(data), NULL);
            grade.set_id(data);
            SQLGetData(hstmt, 6, SQL_C_LONG, &data, sizeof(data), NULL);
            grade.set_grade(data);
            SQLGetData(hstmt, 7, SQL_C_LONG, &data, sizeof(data), NULL);
            subject.set_id(data);
            SQLGetData(hstmt, 8, SQL_C_CHAR, str, sizeof(str), NULL);
            subject.set_name(sqlchar_to_string(str, strlen((char *)str)));

            obj.set_grade(grade);
            obj.set_subject(subject);
            obj.set_auditory(auditory);
            results.push_back(obj);
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    }

    void insert(Database db, ResExam obj) {
        SQLHSTMT hstmt;
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);

        char query[1000];
        sprintf(query, "insert into res_exam values (%d, %d, %d, %d, %d);", obj.get_id(), obj.get_group_num(),
                obj.get_auditory().get_id(), obj.get_subject().get_id(), obj.get_grade().get_id());
        SQLPrepare(hstmt, (SQLCHAR *)query, SQL_NTS);
        SQLExecute(hstmt);

        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
        results.push_back(obj);
    }

    void update(Database db, ResExam old_obj, ResExam new_obj) {
        del(db, old_obj);

        SQLHSTMT hstmt;
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);
        char query[1000];
        sprintf(query, "insert into res_exam values (%d, %d, %d, %d, %d);", new_obj.get_id(),
                new_obj.get_group_num(), new_obj.get_auditory().get_id(), new_obj.get_subject().get_id(),
                new_obj.get_grade().get_id());
        cout << query << endl;
        SQLPrepare(hstmt, (SQLCHAR *)query, SQL_NTS);
        SQLExecute(hstmt);
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    }

    void del(Database db, ResExam obj) {
        SQLHSTMT hstmt;
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);

        char query[1000];
        sprintf(query,
                "delete from res_exam where en_id=%d and group_num=%d and auditory_id=%d and subject_id=%d "
                "and grade_id=%d;",
                obj.get_id(), obj.get_group_num(), obj.get_auditory().get_id(), obj.get_subject().get_id(),
                obj.get_grade().get_id());
        SQLPrepare(hstmt, (SQLCHAR *)query, SQL_NTS);
        SQLExecute(hstmt);
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);

        results.remove(obj);
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