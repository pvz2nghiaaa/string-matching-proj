#include "def.h"

typedef long long ll;
const ll BASE = 31;
const ll MOD = 1e9 + 7;

ll comp_hash(const string &str, int m)
{
    ll h = 0;
    for (int i = 0; i < m; i++)
    {
        h += (h * BASE + (str[i] - 'A' + 1)) % MOD;
    }
    return h;
}

vector<vector<pair<pair<int, int>, pair<int, int>>>> Rabin_karp(vector<vector<char>> &grids, vector<string> &keywords)
{
    int rows = grids.size();
    int cols = (rows > 0) ? grids[0].size() : 0;

    vector<vector<pair<pair<int, int>, pair<int, int>>>> all_res;

    for (const auto &word : keywords)
    {
    }
}

vector<vector<pair<pair<int, int>, pair<int, int>>>> Rabin_karpCountOperation(vector<vector<char>> &grids, vector<string> &keywords, int &comparisons)
{
}