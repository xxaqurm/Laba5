#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <map>

using namespace std;

bool validateInput(string command, string itemName, int items, char zone, int section, int verticalSection, int shelf, string sectionCode, map<vector<int>, map<string, int>> storage);
void ADD(map<vector<int>, map<string, int>>& storage, vector<int> address, string itemName, int items);
void REMOVE(map<vector<int>, map<string, int>>& storage, vector<int> address, string itemName, int items);
void INFO(map<vector<int>, map<string, int>> storage);

#endif