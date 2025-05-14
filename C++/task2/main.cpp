#include <iostream>
#include <vector>
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
        cout << "Введите команду (ENQUEUE, DEQUEUE, EXIT): ";
        cin >> command;

        if (command == "ENQUEUE") {
            numberOfClients++;
            cin >> time;
            if (time < 1) {
                cout << "Время должно быть больше 0." << endl;
                continue;
            }
            clients.push_back({"T" + to_string(numberOfClients), time});
        } else if (command == "DEQUEUE") {
            if (clients.empty()) {
                cout << "Нет клиентов в очереди." << endl;
                continue;
            }
            for (auto& client : clients) {
                int bestWindow = 0;
                int bestTime = INT_MAX;
                for (auto& window : windowQueues) {
                    if (window.first < bestTime) {
                        bestTime = window.first;
                        bestWindow = &window - &windowQueues[0];
                    }
                }
                windowQueues[bestWindow].first += client.second;
                windowQueues[bestWindow].second.push_back(client.first);
            }
            break;
        } else {
            cout << "Неизвестная команда. Введите ENQUEUE, DEQUEUE или EXIT." << endl;
        }
    }

    for (auto& window : windowQueues) {
        cout << "Окно " << &window - &windowQueues[0] + 1 << " (" << window.first << " мин): ";
        for (auto& client : window.second) {
            cout << client << " ";
        }
        cout << endl;
    }
}