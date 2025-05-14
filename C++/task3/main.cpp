#include <iostream>

#include "utils.h"

using namespace std;

int main() {
    string command;
    while (true) {
        cout << "Введите команду (CREATE_TRAM, TRAMS_IN_STOP, STOPS_IN_TRAM): ";
        cin >> command;

        if (command == "CREATE_TRAM") {
            string tramName;
            vector<string> stops;
            int stopCount = 0;

            cin >> tramName;
            cin >> stops[stopCount];
            while (stops[stopCount] != EOF) {
                
            }

            CREATE_TRAM(tramName, stops);
        } else if (command == "TRAMS_IN_STOP") {
            string stop;
            cout << "Enter stop name: ";
            cin >> stop;
            TRAMS_IN_STOP(stop);
        } else if (command == "STOPS_IN_TRAM") {
            string tramName;
            cout << "Enter tram name: ";
            cin >> tramName;
            STOPS_IN_TRAM(tramName);
        } else if (command == "TRAMS") {
            TRAMS();
        } else {
            cout << "Неизвестная команда. Попробуйте еще раз." << endl;
        }
    }

    return 0;
}