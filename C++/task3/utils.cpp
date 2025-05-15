#include <iostream>
#include <vector>
#include <map>

using namespace std;

void CREATE_TRAM(string tramName, vector<string> stops, map<string, vector<string>>& tramRoutes) {
    /* Создает трамвай tramName, который проходит через остановки stops */
    for (auto& stop : stops) {
        tramRoutes[tramName].push_back(stop);
    }
}

void TRAMS_IN_STOP(string stop, map<string, vector<string>>& tramRoutes) {
    /* Вывод всех трамваев, которые проходят через конкретную остановку */
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
    /* Вывод всех остановок, через которые проходит трамвай tramName */
    for (auto& stop : tramRoutes[tramName]) {
        cout << stop << " ";
    }
    cout << endl;
}

void TRAMS(map<string, vector<string>>& tramRoutes) {
    /* Отображает все трамваи с указанием остановок */
    for (auto& tram : tramRoutes) {
        cout << "Трамвай " << tram.first << ": ";
        for (auto& stop : tram.second) {
            cout << stop << " ";
        }
        cout << endl;
    }
}