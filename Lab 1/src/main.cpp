#include <stdlib.h>
#include "database.hpp"
#include "subject_mapper.hpp"

void run();
void menu(Database *db);

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
    if ((con = db.init_tables()) == 0) {
        menu(&db);
    } else {
        printf("Error: init table %d\n", con);
    }
    
}

void menu(Database *db) {
    int act = -1, tab;
    while (act != 0) {
        cout << "Choose an action:\n1. View table\n2. Add data\n3. Delete data\n4. Find data\n5. Update data\n0. Exit\n";
        cin >> act;
        if (act == 0) {
            db->disconnect();
            break;
        }
        system("cls");
        cout << "Choose table:\n1. Subjects\n";
        cin >> tab;
        switch (tab) {
            case 1: {
                SubjectMapper subject_mapper;
                system("cls");
                switch (act) {
                    case 1: {
                        subject_mapper.select(*db);
                        break;
                    }
                    default: {
                        system("clear");
                        cout << "Input error" << endl;
                    }
                }
                break;
            }
            default: {
                system("cls");
                cout << "Input error" << endl;
            }
        }
    }
}
