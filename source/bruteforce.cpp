#include "def.h"

vector<vector<pair<pair<int, int>, pair<int, int>>>> bruteforce(vector<vector<char>>& grids, vector<string>& keywords)
{
    int r = (int)grids.size();
    int c = (int)grids[0].size();
    int q = (int)keywords.size();
    vector<vector<pair<pair<int, int>, pair<int, int>>>> occurrences;

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

        // horizontal
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c - (int)keyword.length() + 1; j++)
                if (grids[i][j] == keyword[0])
                {
                    int nextOccurrence = -1;
                    bool occur = true;

                    for (int k = 1; k < (int)keyword.length(); k++)
                    {
                        if (grids[i][j + k] == keyword[0] && nextOccurrence == -1) // optimization for later
                            nextOccurrence = j + k;
                        if (grids[i][j + k] != keyword[k])
                        {
                            occur = false;
                            break;
                        }
                    }   

                    if (occur == true)
                        occurrences.back().push_back({{i, j}, {i, j + (int)keyword.length() - 1}});
                    if (nextOccurrence != -1)
                        j = nextOccurrence - 1;
                    else
                        j += (int)keyword.length() - 1;
                }

        // vertical
        for (int j = 0; j < c; j++)
            for (int i = 0; i < r - (int)keyword.length() + 1; i++)
                if (grids[i][j] == keyword[0])
                {
                    int nextOccurrence = -1;
                    bool occur = true;

                    for (int k = 1; k < (int)keyword.length(); k++)
                    {
                        if (grids[i + k][j] == keyword[0] && nextOccurrence == -1)
                            nextOccurrence = i + k;
                        if (grids[i + k][j] != keyword[k])
                        {
                            occur = false;
                            break;
                        }
                    }

                    if (occur == true)
                        occurrences.back().push_back({{i, j}, {i + (int)keyword.length() - 1, j}});
                    if (nextOccurrence != -1)
                        i = nextOccurrence - 1;
                    else
                        i += (int)keyword.length() - 1;
                }
    }

    return occurrences;
}

vector<vector<pair<pair<int, int>, pair<int, int>>>> bruteforce(vector<vector<char>>& grids, vector<string>& keywords, long long& comparisons)
{
    int r = (int)grids.size();
    int c = (int)grids[0].size();
    int q = (int)keywords.size();
    comparisons = 0;
    vector<vector<pair<pair<int, int>, pair<int, int>>>> occurrences;

    for (string keyword: keywords)
    {
        occurrences.push_back(vector<pair<pair<int, int>, pair<int, int>>>());
        
        // special case: keyword's length == 1
        if ((int)keyword.length() == 1)
        {
            for (int i = 0; i < r; i++)
                for (int j = 0; j < c; j++)
                    if (++comparisons && grids[i][j] == keyword[0])
                        occurrences.back().push_back({{i, j}, {i, j}});

            continue;
        }

        // horizontal
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c - (int)keyword.length() + 1; j++)
                if (++comparisons && grids[i][j] == keyword[0])
                {
                    int nextOccurrence = -1;
                    bool occur = true;

                    for (int k = 1; k < (int)keyword.length(); k++)
                    {
                        if (++comparisons && grids[i][j + k] == keyword[0] && nextOccurrence == -1) // optimization for later
                            nextOccurrence = j + k;
                        if (++comparisons && grids[i][j + k] != keyword[k])
                        {
                            occur = false;
                            break;
                        }
                    }   

                    if (occur == true)
                        occurrences.back().push_back({{i, j}, {i, j + (int)keyword.length() - 1}});
                    if (nextOccurrence != -1)
                        j = nextOccurrence - 1;
                    else
                        j += (int)keyword.length() - 1;
                }

        // vertical
        for (int j = 0; j < c; j++)
            for (int i = 0; i < r - (int)keyword.length() + 1; i++)
                if (++comparisons && grids[i][j] == keyword[0])
                {
                    int nextOccurrence = -1;
                    bool occur = true;

                    for (int k = 1; k < (int)keyword.length(); k++)
                    {
                        if (++comparisons && grids[i + k][j] == keyword[0] && nextOccurrence == -1)
                            nextOccurrence = i + k;
                        if (++comparisons && grids[i + k][j] != keyword[k])
                        {
                            occur = false;
                            break;
                        }
                    }

                    if (occur == true)
                        occurrences.back().push_back({{i, j}, {i + (int)keyword.length() - 1, j}});
                    if (nextOccurrence != -1)
                        i = nextOccurrence - 1;
                    else
                        i += (int)keyword.length() - 1;
                }
    }

    return occurrences;
}