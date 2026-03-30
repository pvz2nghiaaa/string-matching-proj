#ifndef DEF_H
#define DEF_H

#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <chrono>
#include <fstream>
#include <utility>
#include <math.h>

#define ll long long
using namespace std;

vector<vector<pair<pair<int, int>, pair<int, int>>>> Boyer_Moore(vector<vector<char>>& grids, vector<string>& keywords, long long& comparisons);
vector<vector<pair<pair<int, int>, pair<int, int>>>> Boyer_Moore(vector<vector<char>>& grids, vector<string>& keywords);

vector<vector<pair<pair<int, int>, pair<int, int>>>> Rabin_karpOperationCount(vector<vector<char>> &grids, vector<string> &keywords, long long &comparisons);
vector<vector<pair<pair<int, int>, pair<int, int>>>> Rabin_karp(vector<vector<char>> &grids, vector<string> &keywords);


extern int dx[];
extern int dy[];

#endif