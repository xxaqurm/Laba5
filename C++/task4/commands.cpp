#include <iostream>
#include <map>

#include "commands.h"

using namespace std;

void CHANGE(string region, string newCenter, map<string, string>& regions) {
    /* Изменение центра региона region на newCenter */
    auto it = regions.find(region);
    if (it != regions.end()) {
        cout << "Переименование названия административного (" << regions[region] << ") центра региона " << region << " в " << newCenter << endl;
    } else {
        for (auto& region : regions) {
            if (region.second == newCenter) {
                cout << "Регион с таким центром уже существует." << endl;
                return;
            }
        }
        cout << "Создание региона " << region << " с административным центром " << newCenter << endl;
    }
    regions[region] = newCenter;
}

void RENAME(string old_region, string new_region, map<string, string>& regions) {
    /* Переименование региона old_region в new_region */
    auto it = regions.find(old_region);
    if (it != regions.end()) {
        cout << "Переименование региона со старым названием " << old_region << " в регион с новым названием " << new_region << endl;
        regions[new_region] = regions[old_region];
        regions.erase(old_region);
    } else {
        cout << "Incorrect (региона с названием " << old_region << " не существует)" << endl;
    }
}

void ABOUT(string region, map<string, string>& regions) {
    /* Вывод информации о регионе region */
    auto it = regions.find(region);
    if (it != regions.end()) {
        cout << "Регион " << region << " имеет административный центр " << regions[region] << endl;
    } else {
        cout << "Incorrect (региона " << region << " не существует)" << endl;
    }
}

void ALL(map<string, string>& regions) {
    /* Вывод всех регионов и их административных центров */
    for (const auto& region : regions) {
        cout << "Регион: " << region.first << ", Административный центр: " << region.second << endl;
    }
    cout << endl;
}