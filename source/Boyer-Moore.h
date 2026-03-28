#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

vector<vector<pair<pair<int, int>, pair<int, int>>>> Boyer_Moore(vector<vector<char>>& grids, vector<string>& keywords, int& comparisons);
vector<vector<pair<pair<int, int>, pair<int, int>>>> Boyer_Moore(vector<vector<char>>& grids, vector<string>& keywords);

