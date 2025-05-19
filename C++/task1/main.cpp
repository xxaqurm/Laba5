#include <iostream>
#include <vector>
#include <map>

#include "utils.h"

using namespace std;

int main() {
    map<vector<int>, map<string, int>> storage;  // map<адрес, map<название, количество>>
    
    char zone = 'A';
    int section = 1;
    int verticalSection = 1;
    int shelf = 1;
    int items = 0;

    string command = "ADD";
    string itemName = "Orange";
    string sectionCode = "0000";

    cout << "Для дообавления предмета воспользуйтесь командой ADD (ADD <название> <количество> <ячейка>)\n";
    cout << "Для удаления предмета воспользуйтесь командой REMOVE (REMOVE <название> <количество> <ячейка>)\n";
    cout << "Для получения информации о складе воспользуйтесь командой INFO\n";
    cout << "Для выхода из программы воспользуйтесь командой EXIT\n";
    while (true) {
        cout << "Введите команду: ";
        cin >> command;

        if (command == "ADD") {
            while (true) {
                cin >> itemName >> items >> sectionCode;
                zone = sectionCode[0];
                section = sectionCode[1] - '0';
                verticalSection = sectionCode[2] - '0';
                shelf = sectionCode[3] - '0';
                if (validateInput(command, itemName, items, zone, section, verticalSection, shelf, sectionCode, storage)) {
                    break;
                }
                cout << "Некорректный ввод. Попробуйте еще раз: ";
                cin.clear();
                cin.ignore();
            }
            if (storage[{ zone - 'A', section, verticalSection, shelf }].find(itemName) != storage[{ zone - 'A', section, verticalSection, shelf }].end() && storage[{ zone - 'A', section, verticalSection, shelf }][itemName] + items > 10 || items > 10) {
                cout << "Недостаточно места на складе. Максимальное количество предметов в ячейке: " << 10 << endl;
                cin.clear();
                cin.ignore();
                continue;
            } else if (items < 0) {
                cout << "Некорректное количество предметов. Количество должно быть больше 0." << endl;
                cin.clear();
                cin.ignore();
                continue;
            }
            vector<int> address = { zone - 'A', section, verticalSection, shelf };
            ADD(storage, address, itemName, items);
        } else if (command == "REMOVE") {
            while (true) {
                cin >> itemName >> items >> sectionCode;
                zone = sectionCode[0];
                section = sectionCode[1] - '0';
                verticalSection = sectionCode[2] - '0';
                shelf = sectionCode[3] - '0';
                if (validateInput(command, itemName, items, zone, section, verticalSection, shelf, sectionCode, storage)) {
                    break;
                }
                cout << "Некорректный ввод. Попробуйте еще раз: ";
                cin.clear();
                cin.ignore();
            }
            if (storage[{ zone - 'A', section, verticalSection, shelf }].find(itemName) == storage[{ zone - 'A', section, verticalSection, shelf }].end()) {
                cout << "Предмет не найден на складе.\n";
                continue;
            } else if (storage[{ zone - 'A', section, verticalSection, shelf }][itemName] < items) {
                cout << "Недостаточно предметов на складе.\n";
                continue;
            }
            vector<int> address = { zone - 'A', section, verticalSection, shelf };
            REMOVE(storage, address, itemName, items);
        } else if (command == "INFO") {
            INFO(storage);
        } else if (command == "EXIT") {
            break;
        } else {
            cout << "Неизвестная команда. Попробуйте еще раз.\n";
        }
        cout << "----------------------------------------\n";
    }
}