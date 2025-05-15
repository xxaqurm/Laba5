#include <iostream>
#include <vector>
#include <map>

#include "commands.h"

using namespace std;

Type parseCommand(const string& command) {
    if (command == "CREATE_TRAM") return Type::CREATE_TRAM;
    if (command == "TRAMS_IN_STOP") return Type::TRAMS_IN_STOP;
    if (command == "STOPS_IN_TRAM") return Type::STOPS_IN_TRAM;
    if (command == "TRAMS") return Type::TRAMS;
    if (command == "EXIT") return Type::EXIT;
    return Type::UNKNOWN;
}

int main() {
    string inputCommand;
    map<string, vector<string>> tramRoutes;

    while (true) {
        cout << "Введите команду (CREATE_TRAM, TRAMS_IN_STOP, STOPS_IN_TRAM, TRAMS, EXIT): ";
        cin >> inputCommand;

        Type command = parseCommand(inputCommand);

        switch (command) {
            case Type::CREATE_TRAM: {
                string tramName;
                cin >> tramName;
                string line;
                getline(cin, line);
                line += " ";
                
                string stopName = "";
                vector<string> stops;
                for (char c : line) {
                    if (c != ' ') {
                        stopName += c;
                    } else if (!stopName.empty()) {
                        stops.push_back(stopName);
                        stopName = "";
                    }
                }
                CREATE_TRAM(tramName, stops, tramRoutes);
                break;
            }
            case Type::TRAMS_IN_STOP: {
                string line;
                getline(cin, line);
                line += " ";

                string stopName = "";
                vector<string> stops;
                for (char c : line) {
                    if (c != ' ') {
                        stopName += c;
                    } else if (!stopName.empty()) {
                        stops.push_back(stopName);
                        stopName = "";
                    }
                }

                if (stops.size() != 1) {
                    cout << "Неверный ввод. Ожидалось одно название остановки." << endl;
                    break;
                }
                stopName = stops[0];

                TRAMS_IN_STOP(stopName, tramRoutes);
                break;
            }
            case Type::STOPS_IN_TRAM: {
                string line;
                getline(cin, line);
                line += " ";

                string tramName = "";
                vector<string> trams;
                for (char c : line) {
                    if (c != ' ') {
                        tramName += c;
                    } else if (!tramName.empty()) {
                        trams.push_back(tramName);
                        tramName = "";
                    }
                }

                if (trams.size() != 1) {
                    cout << "Неверный ввод. Ожидалось одно название трамвая." << endl;
                    break;
                }
                tramName = trams[0];
                
                STOPS_IN_TRAM(tramName, tramRoutes);
                break;
            }
            case Type::TRAMS: {
                TRAMS(tramRoutes);
                break;
            }
            case Type::EXIT: {
                return 0;
            }
            default:
                cout << "Неизвестная команда. Попробуйте еще раз." << endl;
                break;
        }
    }
}