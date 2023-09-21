#include "database.hpp"
#include "mapper.hpp"
#include "subject.hpp"
#include <stdlib.h>

void run();
void menu(Database *db);

int main() {
    run();
    return 0;
}

void run() {
    Database db = Database();
    printf("Init tables: %d\n", db.init_tables());
    menu(&db);
}

void menu(Database *db) {
    int act = -1, tab;
    while (act != 0) {
        cout << "Выберите действие:\n1. Вывести таблицу\n2. Добавить строку\n3. Удалить строку\n4. Обновить строку\n0. Выход\n";
        cin >> act;
        if (act == 0) {
            db->disconnect();
            break;
        }
        system("clear");
        cout << "Выберите отношение:\n1. Subjects\n";
        cin >> tab;
        switch (tab) {
            case 1: {
                Subject subject = Subject();
                system("clear");
                switch (act) {
                    case 1: {
                        subject.select(*db);
                        break;
                    }
                    default: {
                        system("clear");
                        cout << "Введено неверное значение!" << endl;
                    }
                }
                break;
            }
            default: {
                system("clear");
                cout << "Введено неверное значение!" << endl;
            }
        }
    }
}
