#include "commands.h"
#include <iostream>

using namespace std;

void CREATE_TRAM(string tramName, vector<string> stops, map<string, vector<string>>& tramRoutes) {
    /* Создание трамвая tramName, который проходит через остановки stops */
    tramRoutes[tramName] = stops;
}

void TRAMS_IN_STOP(string stop, map<string, vector<string>>& tramRoutes) {
    /* Вывод всех трамваев, которые проходят через остановку stop */
    for (auto& tram : tramRoutes) {
        for (auto& tramStop : tram.second) {
            if (tramStop == stop) {
                cout << tram.first << " ";
                break;
            }
        }
    }
    cout << endl;
}

void STOPS_IN_TRAM(string tramName, map<string, vector<string>>& tramRoutes) {
    /* Вывод всех остановок, через которые проезжает трамвай tramName */
    auto it = tramRoutes.find(tramName);
    if (it == tramRoutes.end()) {
        cout << "No tram" << endl;
        return;
    }

    for (const string& stop : it->second) {
        cout << "Остановка " << stop << ": ";
        bool hasOther = false;
        for (auto& tram : tramRoutes) {
            if (tram.first != tramName) {
                for (const string& s : tram.second) {
                    if (s == stop) {
                        cout << tram.first << " ";
                        hasOther = true;
                        break;
                    }
                }
            }
        }
        if (!hasOther) cout << "no interchange";
        cout << endl;
    }
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