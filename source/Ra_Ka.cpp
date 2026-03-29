#include "def.h"

typedef long long ll;
const ll BASE = 31;
const ll MOD = 1e9 + 7;

int dx[] = {0, 0, 1, -1, -1, -1, 1, 1};
int dy[] = {1, -1, 0, 0, 1, -1, 1, -1};

ll comp_hash(const string &str, int m)
{
    ll h = 0;
    for (int i = 0; i < m; i++)
    {
        h += (h * BASE + (str[i] - 'a' + 1)) % MOD;
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
        vector<pair<pair<int, int>, pair<int, int>>> res;
        int m = word.length();
        if (m == 0 || m > max(rows, cols))
        {
            all_res.push_back(res);
            continue;
        }

        ll HashWord = comp_hash(word, m);

        // ll h_inv = 1;
        // for (int i = 0; i < m; i++)
        //     h_inv = (h_inv * BASE) % MOD;

        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                for (int gir = 0; gir < 8; gir++)
                {
                    int endRow = r + (m - 1) * dx[gir];
                    int endCol = c + (m - 1) * dy[gir];

                    if (endRow > 0 && endRow < rows && endCol > 0 && endCol < cols)
                    {
                        ll h_cur = 0;
                        bool match = 1;

                        for (int i = 0; i < m; i++)
                        {
                            h_cur += (h_cur * BASE + grids[r + i + dx[gir]][c + i + dy[gir]] - 'a' + 1) % MOD;
                        }

                        if (h_cur == HashWord)
                        {
                            for (int i = 0; i < m; i++)
                            {
                                if (grids[r + i + dx[gir]][c + i + dy[gir]] != word[i])
                                {
                                    match = 0;
                                    break;
                                }
                            }
                            if (match)
                                res.push_back({{r, c}, {endRow, endCol}});
                        }
                    }
                }
            }
        }
        all_res.push_back(res);
    }

    return all_res;
}

ll comp_hash_OC(const string &str, int m, int &comparisons)
{
    ll h = 0;
    for (int i = 0; ++comparisons, i < m; i++)
    {
        h += (h * BASE + (str[i] - 'a' + 1)) % MOD;
    }
    return h;
}

vector<vector<pair<pair<int, int>, pair<int, int>>>> Rabin_karpOperationCount(vector<vector<char>> &grids, vector<string> &keywords, int &comparisons)
{
    int rows = grids.size();
    int cols = (rows > 0) ? grids[0].size() : 0;

    vector<vector<pair<pair<int, int>, pair<int, int>>>> all_res;

    for (const auto &word : keywords)
    {
        ++comparisons;
        vector<pair<pair<int, int>, pair<int, int>>> res;
        int m = word.length();
        if (++comparisons, m == 0 || m > max(rows, cols))
        {
            all_res.push_back(res);
            continue;
        }

        ll HashWord = comp_hash_OC(word, m, comparisons);

        // ll h_inv = 1;
        // for (int i = 0; i < m; i++)
        //     h_inv = (h_inv * BASE) % MOD;

        for (int r = 0; ++comparisons, r < rows; r++)
        {
            for (int c = 0; ++comparisons, c < cols; c++)
            {
                for (int gir = 0; ++comparisons, gir < 8; gir++)
                {
                    int endRow = r + (m - 1) * dx[gir];
                    int endCol = c + (m - 1) * dy[gir];

                    if (++comparisons, endRow > 0 && endRow < rows && endCol > 0 && endCol < cols)
                    {
                        ll h_cur = 0;
                        bool match = 1;

                        for (int i = 0; ++comparisons, i < m; i++)
                        {
                            h_cur += (h_cur * BASE + grids[r + i + dx[gir]][c + i + dy[gir]] - 'a' + 1) % MOD;
                        }
                        ++comparisons;
                        if (h_cur == HashWord)
                        {
                            for (int i = 0; ++comparisons, i < m; i++)
                            {
                                ++comparisons;
                                if (grids[r + i + dx[gir]][c + i + dy[gir]] != word[i])
                                {
                                    match = 0;
                                    break;
                                }
                            }
                            if (++comparisons, match)
                                res.push_back({{r, c}, {endRow, endCol}});
                        }
                    }
                }
            }
        }
        all_res.push_back(res);
    }

    return all_res;
}