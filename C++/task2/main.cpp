#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

int main() {
    int windowCount = 0;
    while (windowCount < 1) {
        cout << "Введите количество окон: ";
        cin >> windowCount;
        if (windowCount < 1) {
            cout << "Количество окон должно быть больше 0." << endl;
        }
    }

    int time = 0;
    int numberOfClients = 0;
    string command = "NONE";

    vector<pair<int, vector<string>>> windowQueues(windowCount, {0, {}});
    vector<pair<string, int>> clients;

    while (true) {
        cout << "Введите команду (ENQUEUE, DISTRIBUTE): ";
        cin >> command;

        if (command == "ENQUEUE") {
            numberOfClients++;
            cin >> time;
            if (time < 1) {
                cout << "Время должно быть больше 0." << endl;
                continue;
            }
            clients.push_back({"T" + to_string(numberOfClients), time});
        } else if (command == "DISTRIBUTE") {
            if (clients.empty()) {
                cout << "Нет клиентов в очереди." << endl;
                continue;
            }

            sort(clients.begin(), clients.end(), [](const auto& a, const auto& b) {
                return a.second > b.second;
            });


            for (auto& client : clients) {
                int bestWindow = 0;
                int bestTime = INT_MAX;

                for (int i = 0; i < windowCount; ++i) {
                    if (windowQueues[i].first < bestTime) {
                        bestTime = windowQueues[i].first;
                        bestWindow = i;
                    }
                }

                windowQueues[bestWindow].first += client.second;
                windowQueues[bestWindow].second.push_back(client.first);
            }
            break;
        } else {
            cout << "Неизвестная команда. Введите ENQUEUE или DEQUEUE." << endl;
        }
    }

    // Вывод состояния окон
    for (int i = 0; i < windowCount; ++i) {
        cout << "Окно " << i + 1 << " (" << windowQueues[i].first << " мин): ";
        for (const string& client : windowQueues[i].second) {
            cout << client << " ";
        }
        cout << endl;
    }

    return 0;
}
