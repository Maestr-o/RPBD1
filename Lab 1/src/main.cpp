#include <stdlib.h>
#include "database.hpp"
#include "subject_mapper.hpp"

void run();
void act_menu(Database *db);
void select_menu(Database *db, int tab);
void insert_menu(Database *db, int tab);
void update_menu(Database *db, int tab);
void del_menu(Database *db, int tab);

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
    while (act != 0) {
        cout << "Choose an action:\n1. View table\n2. Add data\n3. Update data\n4. Delete data\n5. Find data\n0. Exit\n";
        cin >> act;
        if (act == 0) {
            db->disconnect();
            break;
        }
        int tab;
        cout << "Choose table:\n1. Subjects\n";
        cin >> tab;
        switch (act) {
            case 1:
                select_menu(db, tab);
                break;
            case 2:
                insert_menu(db, tab);
                break;
            case 3:
                update_menu(db, tab);
                break;
            case 4:
                del_menu(db, tab);
                break;
            default:
                cout << "Input error" << endl;
        }
    }
}

void select_menu(Database *db, int tab) {
    switch (tab) {
        case 1: {
            SubjectMapper subject_mapper;
            subject_mapper.select(*db);
            if (db->get_ret() < 0)
                printf("Error: %d\n", db->get_ret());
            break;
        }
        default: {
            cout << "Input error" << endl;
        }
    }
}

void insert_menu(Database *db, int tab) {
    switch (tab) {
        case 1: {
            SubjectMapper subject_mapper;
            subject_mapper.insert(*db);
            if (db->get_ret() < 0)
                printf("Error: %d\n", db->get_ret());
            break;
        }
        default: {
            cout << "Input error" << endl;
        }
    }
}

void update_menu(Database *db, int tab) {
    switch (tab) {
        case 1: {
            SubjectMapper subject_mapper;
            subject_mapper.update(*db);
            if (db->get_ret() < 0)
                printf("Error: %d\n", db->get_ret());
            break;
        }
        default: {
            cout << "Input error" << endl;
        }
    }
}

void del_menu(Database *db, int tab) {
    switch (tab) {
        case 1: {
            SubjectMapper subject_mapper;
            subject_mapper.del(*db);
            if (db->get_ret() < 0)
                printf("Error: %d\n", db->get_ret());
            break;
        }
        default: {
            cout << "Input error" << endl;
        }
    }
}