#include "commands.h"
#include <iostream>

using namespace std;

void CREATE_TRAM(string tramName, vector<string> stops, map<string, vector<string>>& tramRoutes) {
    /* Создание трамвая tramName, который проходит через остановки stops */
    tramRoutes[tramName] = stops;
}

void TRAMS_IN_STOP(string stop, map<string, vector<string>>& tramRoutes) {
    /* Вывод всех трамваев, которые проходят через остановку stop */
    bool tramExists = false;
    for (auto& tram : tramRoutes) {
        for (auto& tramStop : tram.second) {
            if (tramStop == stop) {
                cout << tram.first << " ";
                tramExists = true;
                break;
            }
        }
    }
    if (!tramExists) {
        cout << "Ни один трамвай не ходит через остановку " << stop << "." << endl;
        return;
    }
    cout << endl;
}

void STOPS_IN_TRAM(string tramName, map<string, vector<string>>& tramRoutes) {
    /* Вывод всех остановок, через которые проезжает трамвай tramName */
    auto it = tramRoutes.find(tramName);
    if (it == tramRoutes.end()) {
        cout << "Трамвая с таким именем не существует." << endl;
        return;
    }

    cout << "Остановки трамвая " << tramName << ": ";
    for (auto& stop : tramRoutes[tramName]) {
        cout << stop << " ";
    }
    cout << endl;
}

void TRAMS(map<string, vector<string>>& tramRoutes) {
    /* Вывод всех трамваей и их остановок */
    for (auto& tram : tramRoutes) {
        cout << "Трамвай " << tram.first << ": ";
        for (auto& stop : tram.second) {
            cout << stop << " ";
        }
        cout << endl;
    }
}