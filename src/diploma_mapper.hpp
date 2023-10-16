#ifndef DIPLOMA_MAPPER_HPP

#define DIPLOMA_MAPPER_HPP

#include <list>
#include "res_diploma.hpp"
#include "grade.hpp"
#include "subject.hpp"
#include "database.hpp"

using namespace std;

class DiplomaMapper
{
public:
    Database db;
    list<ResDiploma> results;

    DiplomaMapper(Database *d)
    {
        db = *d;
    }

    void get_all()
    {
        results.clear();
        SQLHSTMT hstmt;
        SQLAllocHandle(SQL_HANDLE_STMT, db.get_hdbc(), &hstmt);

        char query[1000];
        sprintf(query, "select en_id, grades.grade_id, grade, \
            subjects.subject_id, subject from res_diploma, grades, subjects \
            where res_diploma.grade_id=grades.grade_id and \
            res_diploma.subject_id=subjects.subject_id;");

        SQLExecDirect(hstmt, (SQLCHAR *)query, SQL_NTS);

        int data;
        SQLCHAR str[1000];

        for (int i = 1; SQLFetch(hstmt) == SQL_SUCCESS; i++)
        {
            ResDiploma obj;
            Grade grade;
            Subject subject;
            SQLGetData(hstmt, 1, SQL_C_LONG, &data, sizeof(data), NULL);
            obj.set_id(data);
            SQLGetData(hstmt, 2, SQL_C_LONG, &data, sizeof(data), NULL);
            grade.set_id(data);
            SQLGetData(hstmt, 3, SQL_C_LONG, &data, sizeof(data), NULL);
            grade.set_grade(data);
            SQLGetData(hstmt, 4, SQL_C_LONG, &data, sizeof(data), NULL);
            subject.set_id(data);
            SQLGetData(hstmt, 5, SQL_C_CHAR, str, sizeof(str), NULL);
            subject.set_name(sqlchar_to_string(str, strlen((char *)str)));

            obj.set_grade(grade);
            obj.set_subject(subject);
            results.push_back(obj);
        }
        SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    }

    void insert(Database db, ResDiploma obj)
    {
    }

    void update(Database db, ResDiploma old_obj, ResDiploma new_obj)
    {
    }

    void del(Database db, ResDiploma obj)
    {
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