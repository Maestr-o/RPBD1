#include "database.hpp"
#include "subject_mapper.hpp"

#define CHECK_INPUT_INDEX if (num < 1 || num > mapper->subjects.size()) {\
                cout << "No such row" << endl;\
                return;\
            }

void run();
void act_menu(Database *db);
void subjects_menu(Database *db, int act, SubjectMapper *mapper);

int main() {
    run();
    return 0;
}

void run() {
    Database db = Database();
    if (db.get_ret() != 0) {
        printf("Connection error: %d\n", db.get_ret());
        return;
    }
    int con;
    if ((con = db.init_tables()) == 0)
        act_menu(&db);
    else
        printf("Error: init table %d\n", con);
}

void act_menu(Database *db) {
    int act = -1;
    SubjectMapper subject_mapper(db);

    while (act != 0) {
        cout << "Choose an action:\n1. View table\n2. Add data\n3. Update data\n4. Delete data\n0. Exit\n";
        cin >> act;
        if (act == 0) {
            db->disconnect();
            break;
        }
        int tab;
        cout << "Choose table:\n1. Subjects\n";
        cin >> tab;

        switch (tab) {
            case 1:
                subjects_menu(db, act, &subject_mapper);
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
            CHECK_INPUT_INDEX

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
            CHECK_INPUT_INDEX

            cout << "Mapper size: " << mapper->subjects.size();
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
