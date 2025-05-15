#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <map>

using namespace std;

void CREATE_TRAM(string tramName, vector<string> stops, map<string, vector<string>>& tramRoutes);
void TRAMS_IN_STOP(string stop, map<string, vector<string>>& tramRoutes);
void STOPS_IN_TRAM(string tramName, map<string, vector<string>>& tramRoutes);
void TRAMS(map<string, vector<string>>& tramRoutes);

#endif