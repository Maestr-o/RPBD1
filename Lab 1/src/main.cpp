#include "database.h"
#include <stdlib.h>

void run();
void menu(database *db);
void print_menu();

int main() {
    run();
    return 0;
}

void run() {
    database db = database();
    printf("%d", db.init_tables());
    menu(&db);
}

void menu(database *db) {
    int q = -1;
    while (q != 0) {
        print_menu();
        cin >> q;
        switch (q) {
            case 0: {
                db->disconnect();
                break;
            }
            case 1: {
                
                system("cls");
                break;
            }
        }
    }
}

void print_menu() {
    cout << "1. ASDF" << endl << "0. Exit" << endl;
}