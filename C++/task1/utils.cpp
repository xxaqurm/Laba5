#include <iostream>
#include <iomanip>
#include <vector>
#include <map>

using namespace std;

const int SHELVESPERVERTICALSECTION = 5;
const int VERTICALSECTIONCOUNT = 1;
const int TOTALITEMSTORAGE = 1500;
const int STORAGEZONECOUNT = 10;
const int SHELVESPERZONE = 3;
const int SLOTSTORAGE = 10;

bool validateInput(string command, string itemName, int items, char zone, int section, int verticalSection, int shelf, string sectionCode, map<vector<int>, map<string, int>> storage) {
    /* Проверяет корректность ввода */
    if (zone < 'A' || zone > 'A' + STORAGEZONECOUNT - 1) {
        cout << "Некорректная зона. Зона должна быть от A до " << (char)('A' + STORAGEZONECOUNT - 1) << endl;
        cin.clear();
        cin.ignore();
        return false;
    } else if (section < 1 || section > SHELVESPERZONE) {
        cout << "Некорректный номер секции. Секция должна быть от 1 до " << SHELVESPERZONE << endl;
        cin.clear();
        cin.ignore();
        return false;
    } else if (verticalSection < 1 || verticalSection > VERTICALSECTIONCOUNT) {
        cout << "Некорректный номер вертикальной секции. Вертикальная секция должна быть от 1 до " << VERTICALSECTIONCOUNT << endl;
        cin.clear();
        cin.ignore();
        return false;
    } else if (shelf < 1 || shelf > SHELVESPERVERTICALSECTION) {
        cout << "Некорректный номер полки. Полка должна быть от 1 до " << SHELVESPERVERTICALSECTION << endl;
        cin.clear();
        cin.ignore();
        return false;
    } else if (items <= 0) {
        cout << "Некорректное количество предметов. Количество должно быть больше 0." << endl;
        cin.clear();
        cin.ignore();
        return false;
    } else if (sectionCode.length() != 4) {
        cout << "Некорректный код секции. Код секции должен состоять из 4 символов." << endl;
        cin.clear();
        cin.ignore();
        return false;
    }
    cin.clear();
    cin.ignore();
    return true;
}

void INFO(map<vector<int>, map<string, int>> storage) {
    /* Выводит информацию о складе */
    cout << "Информация о складе:" << endl;

    int totalItems = 0;
    vector<int> storageLoad(STORAGEZONECOUNT, 0);
    for (auto& zone : storage) {
        int zoneIndex = zone.first[0];
        for (auto& item : zone.second) {
            cout << "Зона: " << (char)('A' + zoneIndex) << ", Секция: " << zone.first[1] << ", Вертикальная секция: " << zone.first[2] << ", Полка: " << zone.first[3] << ", Предмет: " << item.first << ", Количество: " << item.second << endl;
            totalItems += item.second;
            storageLoad[zoneIndex] += item.second;
        }
    }

    cout << "Загрузка склада по зонам:" << endl;
    for (int i = 0; i < STORAGEZONECOUNT; ++i) {
        cout << "Зона " << (char)('A' + i) << ": " << storageLoad[i] << endl;
    }
    cout << "Общая загруженность склада: " << fixed << setprecision(1) << (totalItems / (double)TOTALITEMSTORAGE) * 100 << "%" << endl;
}

void ADD(map<vector<int>, map<string, int>>& storage, vector<int> address, string itemName, int items) {
    /* Добавляет предмет на склад */
    int totalItems = 0;
    for (auto& item : storage[address]) {
        totalItems += item.second;
    }

    if (totalItems > 10) {
        cout << "Количество предметов в ячейке не может превышать 10." << endl;
        return;
    }
    if (storage[address].find(itemName) != storage[address].end()) {
        storage[address][itemName] += items;
    } else {
        storage[address][itemName] = items;
    }
    cout << "Добавлено " << items << " предметов " << itemName << " в ячейку " << (char)(address[0] + 'A') << address[1] << address[2] << address[3] << endl;
}

void REMOVE(map<vector<int>, map<string, int>>& storage, vector<int> address, string itemName, int items) {
    /* Удаляет предмет со склада */
    storage[address][itemName] -= items;
    cout << "Удалено " << items << " предметов " << itemName << " из ячейки " << (char)(address[0] + 'A') << address[1] << address[2] << address[3] << endl;
}