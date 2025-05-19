#include "commands.h"
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

void CREATE_TRAM(string tramName, vector<string> stops, map<string, vector<string>>& tramRoutes) {
    /* Создание трамвая tramName, который проходит через остановки stops */
    auto it = tramRoutes.find(tramName);
    if (it == tramRoutes.end()) {
        set<string> uniqStops(stops.begin(), stops.end());
        if (stops.size() > uniqStops.size()) {
            cout << "У трамвая несколько остановок с одним и тем же названием." << endl;
            return;
        } else if (stops.size() == 1) {
            cout << "У трамвая не может быть одной остановки." << endl;
            return;
        }
        for (auto& tram : tramRoutes) {
            if (tram.second == stops) {
                cout << "Трамвай с такими остановками уже существует." << endl;
                return;
            }
        }
        tramRoutes[tramName] = stops;
    } else {
        cout << "Трамвай с таким названием уже существует." << endl;
    }

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
        for (auto& tram : tramRoutes) {
            if (tram.first != tramName && find(tram.second.begin(), tram.second.end(), stop) != tram.second.end()) {
                cout << "(" << tram.first << ") ";
            }
        }
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