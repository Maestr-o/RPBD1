#include "database.hpp"
#include "subject_mapper.hpp"

void run();
void act_menu(Database *db);
void subjects_menu(Database *db, int act, SubjectMapper mapper);

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
                subjects_menu(db, act, subject_mapper);
                break;
            default:
                cout << "Input error" << endl;
        }
    }
}

void subjects_menu(Database *db, int act, SubjectMapper mapper) {
    switch (act) {
        case 1: {
            cout << "N\tSubject\n";
            for (auto it = mapper.subjects.begin(); it != mapper.subjects.end(); it++)
                cout << it->get_id() << "\t" << it->get_name() << endl;
            break;
        }
        case 2: {
            
            if (db->get_ret() < 0)
                printf("Error: %d\n", db->get_ret());
            break;
        }
        case 3: {
            
            if (db->get_ret() < 0)
                printf("Error: %d\n", db->get_ret());
            break;
        }
        case 4: {
            
            if (db->get_ret() < 0)
                printf("Error: %d\n", db->get_ret());
            break;
        }
        default: {
            cout << "Input error" << endl;
        }
    }
}
