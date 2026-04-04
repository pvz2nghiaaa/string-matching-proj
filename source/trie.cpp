#include "def.h"

vector<vector<pair<pair<int, int>, pair<int, int>>>> trie(vector<vector<char>>& grids, vector<string>& keywords)
{
    Trie horizontal;
    Trie vertical;
    int r = (int)grids.size();
    int c = (int)grids[0].size();
    vector<vector<pair<pair<int, int>, pair<int, int>>>> occurrences;

    // precompute
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
        {
            horizontal.add(grids, i, j, 0, 1);
            vertical.add(grids, i, j, 1, 0);
        }

    // find occurrences
    for (string keyword: keywords)
    {
        occurrences.push_back(vector<pair<pair<int, int>, pair<int, int>>>());

        // special case: keyword's length == 1
        if ((int)keyword.length() == 1)
        {
            for (int i = 0; i < r; i++)
                for (int j = 0; j < c; j++)
                    if (grids[i][j] == keyword[0])
                        occurrences.back().push_back({{i, j}, {i, j}});

            continue;
        }

        horizontal.findKeyword(occurrences.back(), keyword, 0, 1);
        vertical.findKeyword(occurrences.back(), keyword, 1, 0);
    }

    return occurrences;
}