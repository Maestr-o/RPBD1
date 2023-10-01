#include "database.hpp"
#include "subject_mapper.hpp"
#include "grade_mapper.hpp"
#include "auditory_mapper.hpp"

void run();
void act_menu(Database *db);
void subjects_menu(Database *db, int act, SubjectMapper *mapper);
void grades_menu(Database *db, int act, GradeMapper *mapper);
void auditories_menu(Database *db, int act, AuditoryMapper *mapper);

int main() {
    run();
    return 0;
}

void run() {
    Database db = Database();
    if (db.get_ret() != 0) {
        cout << "Connection error: " << db.get_ret() << endl;
        return;
    }
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

    while (act != 0) {
        cout << "Choose an action:\n1. View data\n2. Add data\n3. Update data\n4. Delete data\n0. Exit\n";
        cin >> act;
        if (act == 0) {
            db->disconnect();
            break;
        }
        int tab;
        cout << "Choose entity:\n1. Subject\n2. Grade\n3. Auditory\n4. Student\n";
        cin >> tab;

        switch (tab) {
            case 1:
                subjects_menu(db, act, &subject_mapper);
                break;
            case 2:
                grades_menu(db, act, &grade_mapper);
                break;
            case 3:
                auditories_menu(db, act, &auditory_mapper);
                break;
            case 4:
                break;
            default:
                cout << "Input error" << endl;
        }
    }
}

void subjects_menu(Database *db, int act, SubjectMapper *mapper) {
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
            mapper->insert(*db, obj);
            if (db->get_ret() < 0)
                cout << "Error" << endl;
            break;
        }
        case 3: {
            Subject old_obj, new_obj;
            unsigned int num, i = 1;
            string new_name;
            cout << "Enter number of row you need to update: ";
            cin >> num;
            if (num < 1 || num > mapper->subjects.size()) {
                cout << "No such row" << endl;
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
            mapper->update(*db, old_obj, new_obj);
            if (db->get_ret() < 0)
                cout << "Error" << endl;
            break;
        }
        case 4: {
            Subject obj;
            unsigned int num, i = 1;
            cout << "Enter number of row you need to delete: ";
            cin >> num;
            if (num < 1 || num > mapper->subjects.size()) {
                cout << "No such row" << endl;
                return;
            }

            for (auto it = mapper->subjects.begin(); i <= mapper->subjects.size(); it++, i++) {
                if (i == num) {
                    obj.set_name(it->get_name());
                    obj.set_id(it->get_id());
                    mapper->del(*db, obj);
                    break;
                }
            }
            if (db->get_ret() < 0)
                cout << "Error" << endl;
            break;
        }
        default: {
            cout << "Input error" << endl;
        }
    }
}

void grades_menu(Database *db, int act, GradeMapper *mapper) {
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
            mapper->insert(*db, obj);
            if (db->get_ret() < 0)
                cout << "Error" << endl;
            break;
        }
        case 3: {
            Grade old_obj, new_obj;
            unsigned int num, i = 1;
            int new_grade;
            cout << "Enter number of row you need to update: ";
            cin >> num;
            if (num < 1 || num > mapper->grades.size()) {
                cout << "No such row" << endl;
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
            mapper->update(*db, old_obj, new_obj);
            if (db->get_ret() < 0)
                cout << "Error" << endl;
            break;
        }
        case 4: {
            Grade obj;
            unsigned int num, i = 1;
            cout << "Enter number of row you need to delete: ";
            cin >> num;
            if (num < 1 || num > mapper->grades.size()) {
                cout << "No such row" << endl;
                return;
            }

            for (auto it = mapper->grades.begin(); i <= mapper->grades.size(); it++, i++) {
                if (i == num) {
                    obj.set_grade(it->get_grade());
                    obj.set_id(it->get_id());
                    mapper->del(*db, obj);
                    break;
                }
            }
            if (db->get_ret() < 0)
                cout << "Error" << endl;
            break;
        }
        default: {
            cout << "Input error" << endl;
        }
    }
}

void auditories_menu(Database *db, int act, AuditoryMapper *mapper) {
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
            mapper->insert(*db, obj);
            if (db->get_ret() < 0)
                cout << "Error" << endl;
            break;
        }
        case 3: {
            Auditory old_obj, new_obj;
            unsigned int num, i = 1;
            int new_auditory;
            cout << "Enter number of row you need to update: ";
            cin >> num;
            if (num < 1 || num > mapper->auditories.size()) {
                cout << "No such row" << endl;
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
            mapper->update(*db, old_obj, new_obj);
            if (db->get_ret() < 0)
                cout << "Error" << endl;
            break;
        }
        case 4: {
            Auditory obj;
            unsigned int num, i = 1;
            cout << "Enter number of row you need to delete: ";
            cin >> num;
            if (num < 1 || num > mapper->auditories.size()) {
                cout << "No such row" << endl;
                return;
            }

            for (auto it = mapper->auditories.begin(); i <= mapper->auditories.size(); it++, i++) {
                if (i == num) {
                    obj.set_auditory(it->get_auditory());
                    obj.set_id(it->get_id());
                    mapper->del(*db, obj);
                    break;
                }
            }
            if (db->get_ret() < 0)
                cout << "Error" << endl;
            break;
        }
        default: {
            cout << "Input error" << endl;
        }
    }
}