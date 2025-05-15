#include <iostream>
#include <vector>
#include <map>

#include "utils.h"

using namespace std;

int main() {
    string command = "NONE";;

    
    map<string, vector<string>> tramRoutes;

    while (true) {
        cout << "Введите команду (CREATE_TRAM, TRAMS_IN_STOP, STOPS_IN_TRAM, TRAMS, EXIT): ";
        cin >> command;

        if (command == "CREATE_TRAM") {
            string tramName = "NONE";
            cin >> tramName;

            string stop = "";
            string allStops = "";
            getline(cin, allStops);
            allStops += " ";

            vector<string> stops;
            for (char& c : allStops) {
                if (c != ' ') {
                    stop += c;
                } else if (stop != "") {
                    stops.push_back(stop);
                    stop = "";
                }
            }
            
            CREATE_TRAM(tramName, stops, tramRoutes);
        } else if (command == "TRAMS_IN_STOP") {
            string stop = "";
            string allStops = "";
            getline(cin, allStops);
            allStops += " ";

            vector<string> stops;
            for (char& c : allStops) {
                if (c != ' ') {
                    stop += c;
                } else if (stop != "") {
                    stops.push_back(stop);
                    stop = "";
                }
            }

            if (stops.size() > 1) {
                cout << "Остановка должна быть одна." << endl;
                continue;
            }
            stop = stops[0];

            TRAMS_IN_STOP(stop, tramRoutes);
        } else if (command == "STOPS_IN_TRAM") {
            string tramName;
            string allTrams = "";
            getline(cin, allTrams);
            allTrams += " ";

            vector<string> trams;
            for (char& c : allTrams) {
                if (c != ' ') {
                    tramName += c;
                } else if (tramName != "") {
                    trams.push_back(tramName);
                    tramName = "";
                }
            }

            if (trams.size() > 1) {
                cout << "Трамвай должен быть один." << endl;
                continue;
            }
            tramName = trams[0];
            
            STOPS_IN_TRAM(tramName, tramRoutes);
        } else if (command == "TRAMS") {
            TRAMS(tramRoutes);
        } else if (command == "EXIT") {
            break;
        } else {
            cout << "Неизвестная команда. Попробуйте еще раз." << endl;
        }
    }

    return 0;
}