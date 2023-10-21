#include "database.hpp"
#include "auditory_mapper.hpp"
#include "diploma_mapper.hpp"
#include "enrollee_mapper.hpp"
#include "exam_mapper.hpp"
#include "grade_mapper.hpp"
#include "subject_mapper.hpp"

void run();
void act_menu(Database *db);
void subjects_menu(int act, SubjectMapper *mapper);
void grades_menu(int act, GradeMapper *mapper);
void auditories_menu(int act, AuditoryMapper *mapper);
void enrollee_menu(int act, EnrolleeMapper *mapper);
void diploma_menu(int act, DiplomaMapper *mapper, EnrolleeMapper *enmapper,
                  SubjectMapper *submapper, GradeMapper *grmapper);
void exam_menu(int act, ExamMapper *mapper, EnrolleeMapper *enmapper, SubjectMapper *submapper,
               GradeMapper *grmapper, AuditoryMapper *audmapper);

int main() {
    run();
    return 0;
}

void run() {
    Database db = Database();
    int con;
    if ((con = db.init_tables()) == 0)
        act_menu(&db);
    else
        cout << "Error: init table " << con << endl;
}

void act_menu(Database *db) {
    int act = -1;
    SubjectMapper subject_mapper(db);
    GradeMapper grade_mapper(db);
    AuditoryMapper auditory_mapper(db);
    EnrolleeMapper enrollee_mapper(db);
    DiplomaMapper diploma_mapper(db);
    ExamMapper exam_mapper(db);

    while (act != 0) {
        cout << "Choose an action:\n1. View data\n2. Add data\n3. Update data\n4. Delete data\n0. Exit\n";
        cin >> act;
        if (act == 0) {
            db->disconnect();
            break;
        }
        int tab;
        cout << "Choose entity:\n1. Subject\n2. Grade\n3. Auditory\n4. Enrollee\n5. Grades in the "
                "diploma\n6. Results of exam"
             << endl;
        cin >> tab;

        switch (tab) {
            case 1:
                subjects_menu(act, &subject_mapper);
                break;
            case 2:
                grades_menu(act, &grade_mapper);
                break;
            case 3:
                auditories_menu(act, &auditory_mapper);
                break;
            case 4:
                enrollee_menu(act, &enrollee_mapper);
                break;
            case 5:
                diploma_menu(act, &diploma_mapper, &enrollee_mapper, &subject_mapper, &grade_mapper);
                break;
            case 6:
                exam_menu(act, &exam_mapper, &enrollee_mapper, &subject_mapper, &grade_mapper,
                          &auditory_mapper);
                break;
            default:
                cout << "Input error" << endl;
        }
    }
}

void subjects_menu(int act, SubjectMapper *mapper) {
    switch (act) {
        case 1: {
            mapper->get_all();
            cout << "N\tSubject\n";
            unsigned int i = 1;
            for (auto it = mapper->subjects.begin(); i <= mapper->subjects.size(); it++, i++)
                cout << i << "\t" << it->get_name() << endl;
            break;
        }
        case 2: {
            Subject obj;
            string name;
            cout << "Enter subject: ";
            cin >> name;
            obj.set_name(name);
            mapper->insert(obj);

            break;
        }
        case 3: {
            Subject old_obj, new_obj;
            unsigned int num, i = 1;
            string new_name;
            cout << "Enter number of row you need to update: ";
            cin >> num;
            if (num < 1 || num > mapper->subjects.size()) {
                cout << "Error" << endl;
                return;
            }

            cout << "Enter new name of subject: ";
            cin >> new_name;
            for (auto it = mapper->subjects.begin(); i <= mapper->subjects.size(); it++, i++) {
                if (i == num) {
                    old_obj.set_name(it->get_name());
                    old_obj.set_id(it->get_id());
                    new_obj.set_id(it->get_id());
                    new_obj.set_name(new_name);
                    break;
                }
            }
            mapper->update(old_obj, new_obj);

            break;
        }
        case 4: {
            Subject obj;
            unsigned int num, i = 1;
            cout << "Enter number of row you need to delete: ";
            cin >> num;
            if (num < 1 || num > mapper->subjects.size()) {
                cout << "Error" << endl;
                return;
            }

            for (auto it = mapper->subjects.begin(); i <= mapper->subjects.size(); it++, i++) {
                if (i == num) {
                    obj.set_name(it->get_name());
                    obj.set_id(it->get_id());
                    mapper->del(obj);
                    break;
                }
            }
            break;
        }
        default: {
            cout << "Input error" << endl;
        }
    }
}

void grades_menu(int act, GradeMapper *mapper) {
    switch (act) {
        case 1: {
            mapper->get_all();
            cout << "N\tGrade\n";
            unsigned int i = 1;
            for (auto it = mapper->grades.begin(); i <= mapper->grades.size(); it++, i++)
                cout << i << "\t" << it->get_grade() << endl;
            break;
        }
        case 2: {
            Grade obj;
            int grade;
            cout << "Enter grade: ";
            cin >> grade;
            obj.set_grade(grade);
            mapper->insert(obj);

            break;
        }
        case 3: {
            Grade old_obj, new_obj;
            unsigned int num, i = 1;
            int new_grade;
            cout << "Enter number of row you need to update: ";
            cin >> num;
            if (num < 1 || num > mapper->grades.size()) {
                cout << "Error" << endl;
                return;
            }

            cout << "Enter new grade: ";
            cin >> new_grade;
            for (auto it = mapper->grades.begin(); i <= mapper->grades.size(); it++, i++) {
                if (i == num) {
                    old_obj.set_grade(it->get_grade());
                    old_obj.set_id(it->get_id());
                    new_obj.set_id(it->get_id());
                    new_obj.set_grade(new_grade);
                    break;
                }
            }
            mapper->update(old_obj, new_obj);

            break;
        }
        case 4: {
            Grade obj;
            unsigned int num, i = 1;
            cout << "Enter number of row you need to delete: ";
            cin >> num;
            if (num < 1 || num > mapper->grades.size()) {
                cout << "Error" << endl;
                return;
            }

            for (auto it = mapper->grades.begin(); i <= mapper->grades.size(); it++, i++) {
                if (i == num) {
                    obj.set_grade(it->get_grade());
                    obj.set_id(it->get_id());
                    mapper->del(obj);
                    break;
                }
            }

            break;
        }
        default: {
            cout << "Input error" << endl;
        }
    }
}

void auditories_menu(int act, AuditoryMapper *mapper) {
    switch (act) {
        case 1: {
            mapper->get_all();
            cout << "N\tAuditory\n";
            unsigned int i = 1;
            for (auto it = mapper->auditories.begin(); i <= mapper->auditories.size(); it++, i++)
                cout << i << "\t" << it->get_auditory() << endl;
            break;
        }
        case 2: {
            Auditory obj;
            int auditory;
            cout << "Enter auditory: ";
            cin >> auditory;
            obj.set_auditory(auditory);
            mapper->insert(obj);

            break;
        }
        case 3: {
            Auditory old_obj, new_obj;
            unsigned int num, i = 1;
            int new_auditory;
            cout << "Enter number of row you need to update: ";
            cin >> num;
            if (num < 1 || num > mapper->auditories.size()) {
                cout << "Error" << endl;
                return;
            }

            cout << "Enter new auditory: ";
            cin >> new_auditory;
            for (auto it = mapper->auditories.begin(); i <= mapper->auditories.size(); it++, i++) {
                if (i == num) {
                    old_obj.set_auditory(it->get_auditory());
                    old_obj.set_id(it->get_id());
                    new_obj.set_id(it->get_id());
                    new_obj.set_auditory(new_auditory);
                    break;
                }
            }
            mapper->update(old_obj, new_obj);

            break;
        }
        case 4: {
            Auditory obj;
            unsigned int num, i = 1;
            cout << "Enter number of row you need to delete: ";
            cin >> num;
            if (num < 1 || num > mapper->auditories.size()) {
                cout << "Error" << endl;
                return;
            }

            for (auto it = mapper->auditories.begin(); i <= mapper->auditories.size(); it++, i++) {
                if (i == num) {
                    obj.set_auditory(it->get_auditory());
                    obj.set_id(it->get_id());
                    mapper->del(obj);
                    break;
                }
            }

            break;
        }
        default: {
            cout << "Input error" << endl;
        }
    }
}

void enrollee_menu(int act, EnrolleeMapper *mapper) {
    switch (act) {
        case 1: {
            mapper->get_all();
            cout << "N\tFirst name\tLast name\tSurname\t\tSex\tCityzenship\tDate of birth\t"
                 << "Passport\tAddress\tParents address\n";
            unsigned int i = 1;
            for (auto it = mapper->applicants.begin(); i <= mapper->applicants.size(); it++, i++)
                cout << i << "\t" << it->get_passport().get_first_name() << "\t\t"
                     << it->get_passport().get_last_name() << "\t\t" << it->get_passport().get_surname()
                     << "\t" << ((it->get_passport().get_sex()) ? "Man" : "Woman") << "\t"
                     << it->get_passport().get_cityzenship() << "\t\t" << it->get_passport().get_birth()
                     << "\t" << it->get_passport().get_pass_serial() << " "
                     << it->get_passport().get_pass_num() << "\t" << it->get_address() << "\t"
                     << it->get_parents_address() << endl;
            break;
        }
        case 2: {
            Enrollee enrollee;
            Passport passport;
            Education education;
            string str;
            int num;
            float f;

            cout << "Enter first name: ";
            cin >> str;
            passport.set_first_name(str);
            cout << "Enter last name: ";
            cin >> str;
            passport.set_last_name(str);
            cout << "Enter surname: ";
            cin >> str;
            passport.set_surname(str);
            cout << "Enter sex: ";
            cin >> num;
            passport.set_sex(num);
            cout << "Enter cityzenship: ";
            cin >> str;
            passport.set_cityzenship(str);
            cout << "Enter birth: ";
            cin >> str;
            passport.set_birth(str);
            cout << "Enter pass serial: ";
            cin >> num;
            passport.set_pass_serial(num);
            cout << "Enter pass number: ";
            cin >> num;
            passport.set_pass_num(num);
            cout << "Enter address: ";
            cin >> str;
            enrollee.set_address(str);
            cout << "Enter parents address: ";
            cin >> str;
            enrollee.set_parents_address(str);
            cout << "Enter faculty: ";
            cin >> str;
            education.set_faculty(str);
            cout << "Enter speciality: ";
            cin >> str;
            education.set_speciality(str);
            cout << "Enter university: ";
            cin >> str;
            education.set_university(str);
            cout << "Enter year of ending: ";
            cin >> num;
            education.set_year_of_ending(num);
            cout << "Enter type of document: ";
            cin >> str;
            education.set_type_of_doc(str);
            cout << "Enter document number: ";
            cin >> num;
            education.set_doc_num(num);
            cout << "Enter foreign language: ";
            cin >> str;
            education.set_faculty(str);
            cout << "Enter GPA: ";
            cin >> f;
            education.set_gpa(f);
            cout << "Enter EGE score: ";
            cin >> num;
            education.set_ege(num);

            enrollee.set_education(education);
            enrollee.set_passport(passport);
            mapper->insert(enrollee);

            break;
        }
        case 3: {
            Enrollee new_obj;
            Passport passport;
            Education education;
            Enrollee old_obj;
            unsigned int num = -1, i = 1;
            string col;
            cout << "Enter row number: ";
            cin >> num;
            if (num < 1 || num > mapper->applicants.size()) {
                cout << "Error" << endl;
                return;
            }

            for (auto it = mapper->applicants.begin(); i <= mapper->applicants.size(); it++, i++) {
                if (i == num) {
                    old_obj.set_id(it->get_id());
                    old_obj.set_address(it->get_address());
                    old_obj.set_parents_address(it->get_parents_address());
                    old_obj.set_education(it->get_education());
                    old_obj.set_passport(it->get_passport());

                    new_obj.set_id(it->get_id());
                    new_obj.set_address(it->get_address());
                    new_obj.set_parents_address(it->get_parents_address());
                    new_obj.set_education(it->get_education());
                    new_obj.set_passport(it->get_passport());
                }
            }

            cout << "Enter column: " << endl;
            cin >> col;

            cout << "Enter data: ";
            string str;
            int n;
            float f;
            if (col == "first_name") {
                cin >> str;
                new_obj.get_link_passport()->set_first_name(str);
            } else if (col == "last_name") {
                cin >> str;
                new_obj.get_link_passport()->set_last_name(str);
            } else if (col == "surname") {
                cin >> str;
                new_obj.get_link_passport()->set_surname(str);
            } else if (col == "sex") {
                cin >> n;
                new_obj.get_link_passport()->set_sex(n);
            } else if (col == "cityzenship") {
                cin >> str;
                new_obj.get_link_passport()->set_cityzenship(str);
            } else if (col == "birth") {
                cin >> str;
                new_obj.get_link_passport()->set_birth(str);
            } else if (col == "pass_serial") {
                cin >> n;
                new_obj.get_link_passport()->set_pass_serial(n);
            } else if (col == "pass_num") {
                cin >> n;
                new_obj.get_link_passport()->set_pass_num(n);
            } else if (col == "address") {
                cin >> str;
                new_obj.set_address(str);
            } else if (col == "parents_address") {
                cin >> str;
                new_obj.set_parents_address(str);
            } else if (col == "faculty") {
                cin >> str;
                new_obj.get_link_education()->set_faculty(str);
            } else if (col == "speciality") {
                cin >> str;
                new_obj.get_link_education()->set_speciality(str);
            } else if (col == "university") {
                cin >> str;
                new_obj.get_link_education()->set_university(str);
            } else if (col == "year_of_ending") {
                cin >> n;
                new_obj.get_link_education()->set_year_of_ending(n);
            } else if (col == "type_of_doc") {
                cin >> str;
                new_obj.get_link_education()->set_type_of_doc(str);
            } else if (col == "doc_num") {
                cin >> n;
                new_obj.get_link_education()->set_doc_num(n);
            } else if (col == "foreign_lang") {
                cin >> str;
                new_obj.get_link_education()->set_foreign_lang(str);
            } else if (col == "gpa") {
                cin >> f;
                new_obj.get_link_education()->set_gpa(f);
            } else if (col == "ege") {
                cin >> n;
                new_obj.get_link_education()->set_ege(n);
            } else {
                cout << "Input error" << endl;
                return;
            }

            mapper->update(old_obj, new_obj);
            break;
        }
        case 4: {
            Enrollee obj;
            unsigned int num, i = 1;
            cout << "Enter row number: ";
            cin >> num;

            for (auto it = mapper->applicants.begin(); i <= mapper->applicants.size(); it++, i++) {
                if (i == num) {
                    obj.set_id(it->get_id());
                    obj.set_address(it->get_address());
                    obj.set_parents_address(it->get_parents_address());
                    obj.set_education(it->get_education());
                    obj.set_passport(it->get_passport());
                }
            }

            mapper->del(obj);

            break;
        }
        default: {
            cout << "Input error" << endl;
        }
    }
}

void diploma_menu(int act, DiplomaMapper *mapper, EnrolleeMapper *enmapper,
                  SubjectMapper *submapper, GradeMapper *grmapper) {
    switch (act) {
        case 1: {
            enmapper->get_all();
            mapper->get_all();
            int st;
            cout << "Enter number of student: ";
            cin >> st;
            cout << "N\tSubject\t\tGrade\n";
            unsigned int i = 1;
            for (auto it = enmapper->applicants.begin(); i <= enmapper->applicants.size(); it++, i++) {
                if (i == (unsigned int)st) {
                    st = it->get_id();
                    break;
                }
            }
            i = 1;
            int j = 1;
            for (auto it = mapper->results.begin(); i <= mapper->results.size(); it++, i++) {
                if (it->get_id() == st)
                    cout << j++ << "\t" << it->get_subject().get_name() << "\t\t"
                         << it->get_grade().get_grade() << endl;
            }
            break;
        }
        case 2: {
            enmapper->get_all();
            grmapper->get_all();
            submapper->get_all();
            ResDiploma obj;
            Grade grade;
            Subject subject;
            int data, id;
            string str;
            cout << "Enter number of student: ";
            cin >> data;
            unsigned int i = 1;
            for (auto it = enmapper->applicants.begin(); i <= enmapper->applicants.size(); it++, i++) {
                if (i == (unsigned int)data) {
                    obj.set_id(it->get_id());
                    break;
                }
            }

            i = 0;
            cout << "Enter subject: ";
            cin >> str;
            for (auto it = submapper->subjects.begin(); i <= submapper->subjects.size(); it++, i++) {
                if (it->get_name() == str) {
                    data = it->get_id();
                    break;
                }
            }
            subject.set_id(data);
            subject.set_name(str);

            i = 0;
            cout << "Enter grade: ";
            cin >> data;
            for (auto it = grmapper->grades.begin(); i <= grmapper->grades.size(); it++, i++) {
                if (it->get_grade() == data) {
                    id = it->get_id();
                    break;
                }
            }
            grade.set_id(id);
            grade.set_grade(data);

            obj.set_grade(grade);
            obj.set_subject(subject);
            mapper->insert(obj);
            break;
        }
        case 3: {
            ResDiploma new_obj;
            ResDiploma old_obj;
            unsigned int num = -1, i = 1;
            int data;
            string col;

            cout << "Enter number of student: ";
            cin >> data;
            i = 1;
            for (auto it = enmapper->applicants.begin(); i <= enmapper->applicants.size(); it++, i++) {
                if (i == (unsigned int)data) {
                    old_obj.set_id(it->get_id());
                    new_obj.set_id(it->get_id());
                    break;
                }
            }

            cout << "Enter row number: ";
            cin >> num;
            if (num < 1 || num > mapper->results.size()) {
                cout << "Error" << endl;
                return;
            }

            i = 1;
            for (auto it = mapper->results.begin(); i <= mapper->results.size(); it++, i++) {
                if (i == num) {
                    old_obj.set_grade(it->get_grade());
                    old_obj.set_subject(it->get_subject());

                    new_obj.set_grade(it->get_grade());
                    new_obj.set_subject(it->get_subject());
                }
            }

            cout << "Enter column: ";
            cin >> col;

            string str;
            int id;
            cout << "Enter data: ";
            i = 1;
            if (col == "subject") {
                cin >> str;
                for (auto it = submapper->subjects.begin(); i <= submapper->subjects.size(); it++, i++) {
                    if (it->get_name() == str) {
                        data = it->get_id();
                        break;
                    }
                }
                new_obj.get_link_subject()->set_id(data);
                new_obj.get_link_subject()->set_name(str);
            } else if (col == "grade") {
                cin >> data;
                for (auto it = grmapper->grades.begin(); i <= grmapper->grades.size(); it++, i++) {
                    if (it->get_grade() == data) {
                        id = it->get_id();
                        break;
                    }
                }
                new_obj.get_link_grade()->set_id(id);
                new_obj.get_link_grade()->set_grade(data);
            } else {
                cout << "Input error" << endl;
                return;
            }

            mapper->update(old_obj, new_obj);
            break;
        }
        case 4: {
            ResDiploma obj;
            unsigned int num, i = 1;
            int st;
            cout << "Enter number of student: ";
            cin >> st;
            if (st < 1 || (unsigned int)st > enmapper->applicants.size()) {
                cout << "Error" << endl;
                return;
            }
            cout << "Enter number of row you need to delete: ";
            cin >> num;
            if (num < 1 || num > mapper->results.size()) {
                cout << "Error" << endl;
                return;
            }

            for (auto it = enmapper->applicants.begin(); i <= enmapper->applicants.size(); it++, i++) {
                if (i == (unsigned int)st) {
                    st = it->get_id();
                    break;
                }
            }

            unsigned int j = 1;
            i = 1;
            for (auto it = mapper->results.begin(); i <= mapper->results.size(); it++, i++) {
                if (it->get_id() == st && j == num) {
                    obj.set_grade(it->get_grade());
                    obj.set_subject(it->get_subject());
                    obj.set_id(it->get_id());
                    mapper->del(obj);
                    break;
                }
                if (it->get_id() == st)
                    j++;
            }
            break;
        }
        default: {
            cout << "Input error" << endl;
        }
    }
}

void exam_menu(int act, ExamMapper *mapper, EnrolleeMapper *enmapper, SubjectMapper *submapper,
               GradeMapper *grmapper, AuditoryMapper *audmapper) {
    switch (act) {
        case 1: {
            enmapper->get_all();
            mapper->get_all();
            int st;
            cout << "Enter number of student: ";
            cin >> st;
            cout << "N\tGroup\tAuditory\tSubject\t\tGrade\n";
            unsigned int i = 1;
            for (auto it = enmapper->applicants.begin(); i <= enmapper->applicants.size(); it++, i++) {
                if (i == (unsigned int)st) {
                    st = it->get_id();
                    break;
                }
            }
            i = 1;
            int j = 1;
            for (auto it = mapper->results.begin(); i <= mapper->results.size(); it++, i++) {
                if (it->get_id() == st)
                    cout << j++ << "\t" << it->get_group_num() << "\t" << it->get_auditory().get_auditory()
                         << "\t\t" << it->get_subject().get_name() << "\t\t" << it->get_grade().get_grade()
                         << endl;
            }
            break;
        }
        case 2: {
            enmapper->get_all();
            grmapper->get_all();
            submapper->get_all();
            audmapper->get_all();
            ResExam obj;
            Grade grade;
            Subject subject;
            Auditory auditory;
            int data, id;
            string str;
            cout << "Enter number of student: ";
            cin >> data;
            unsigned int i = 1;
            for (auto it = enmapper->applicants.begin(); i <= enmapper->applicants.size(); it++, i++) {
                if (i == (unsigned int)data) {
                    obj.set_id(it->get_id());
                    break;
                }
            }

            cout << "Enter group number:";
            cin >> data;
            obj.set_group_num(data);

            i = 0;
            cout << "Enter auditory: ";
            cin >> data;
            for (auto it = audmapper->auditories.begin(); i <= audmapper->auditories.size(); it++, i++) {
                if (it->get_auditory() == data) {
                    id = it->get_id();
                    break;
                }
            }
            auditory.set_auditory(data);
            auditory.set_id(id);

            i = 0;
            cout << "Enter subject: ";
            cin >> str;
            for (auto it = submapper->subjects.begin(); i <= submapper->subjects.size(); it++, i++) {
                if (it->get_name() == str) {
                    data = it->get_id();
                    break;
                }
            }
            subject.set_id(data);
            subject.set_name(str);

            i = 0;
            cout << "Enter grade: ";
            cin >> data;
            for (auto it = grmapper->grades.begin(); i <= grmapper->grades.size(); it++, i++) {
                if (it->get_grade() == data) {
                    id = it->get_id();
                    break;
                }
            }
            grade.set_id(id);
            grade.set_grade(data);

            obj.set_auditory(auditory);
            obj.set_grade(grade);
            obj.set_subject(subject);
            mapper->insert(obj);
            break;
        }
        case 3: {
            ResExam new_obj;
            ResExam old_obj;
            unsigned int num = -1, i = 1;
            int data;
            string col;

            cout << "Enter number of student: ";
            cin >> data;
            i = 1;
            for (auto it = enmapper->applicants.begin(); i <= enmapper->applicants.size(); it++, i++) {
                if (i == (unsigned int)data) {
                    old_obj.set_id(it->get_id());
                    new_obj.set_id(it->get_id());
                    break;
                }
            }

            cout << "Enter row number: ";
            cin >> num;
            if (num < 1 || num > mapper->results.size()) {
                cout << "Error" << endl;
                return;
            }

            i = 1;
            for (auto it = mapper->results.begin(); i <= mapper->results.size(); it++, i++) {
                if (i == num) {
                    old_obj.set_auditory(it->get_auditory());
                    old_obj.set_group_num(it->get_group_num());
                    old_obj.set_grade(it->get_grade());
                    old_obj.set_subject(it->get_subject());

                    new_obj.set_auditory(it->get_auditory());
                    new_obj.set_group_num(it->get_group_num());
                    new_obj.set_grade(it->get_grade());
                    new_obj.set_subject(it->get_subject());
                }
            }

            cout << "Enter column: ";
            cin >> col;

            string str;
            int id;
            cout << "Enter data: ";
            i = 1;
            if (col == "subject") {
                cin >> str;
                for (auto it = submapper->subjects.begin(); i <= submapper->subjects.size(); it++, i++) {
                    if (it->get_name() == str) {
                        data = it->get_id();
                        break;
                    }
                }
                new_obj.get_link_subject()->set_id(data);
                new_obj.get_link_subject()->set_name(str);
            } else if (col == "grade") {
                cin >> data;
                for (auto it = grmapper->grades.begin(); i <= grmapper->grades.size(); it++, i++) {
                    if (it->get_grade() == data) {
                        id = it->get_id();
                        break;
                    }
                }
                new_obj.get_link_grade()->set_id(id);
                new_obj.get_link_grade()->set_grade(data);
            } else if (col == "auditory") {
                cin >> data;
                for (auto it = audmapper->auditories.begin(); i <= audmapper->auditories.size(); it++, i++) {
                    if (it->get_auditory() == data) {
                        id = it->get_id();
                        break;
                    }
                }
                new_obj.get_link_auditory()->set_id(id);
                new_obj.get_link_auditory()->set_auditory(data);
            } else if (col == "group_num") {
                cin >> data;
                new_obj.set_group_num(data);
            } else {
                cout << "Input error" << endl;
                return;
            }

            mapper->update(old_obj, new_obj);
            break;
        }
        case 4: {
            ResExam obj;
            unsigned int num, i = 1;
            int st;
            cout << "Enter number of student: ";
            cin >> st;
            if (st < 1 || (unsigned int)st > enmapper->applicants.size()) {
                cout << "Error" << endl;
                return;
            }
            cout << "Enter number of row you need to delete: ";
            cin >> num;
            if (num < 1 || num > mapper->results.size()) {
                cout << "Error" << endl;
                return;
            }

            for (auto it = enmapper->applicants.begin(); i <= enmapper->applicants.size(); it++, i++) {
                if (i == (unsigned int)st) {
                    st = it->get_id();
                    break;
                }
            }

            unsigned int j = 1;
            i = 1;
            for (auto it = mapper->results.begin(); i <= mapper->results.size(); it++, i++) {
                if (it->get_id() == st && j == num) {
                    obj.set_auditory(it->get_auditory());
                    obj.set_group_num(it->get_group_num());
                    obj.set_grade(it->get_grade());
                    obj.set_subject(it->get_subject());
                    obj.set_id(it->get_id());
                    mapper->del(obj);
                    break;
                }
                if (it->get_id() == st)
                    j++;
            }
            break;
        }
        default: {
            cout << "Input error" << endl;
        }
    }
}