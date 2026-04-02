#include "def.h"

const long long BASE = 31;
const long long MOD = 1e9 + 7;

long long comp_hash(const string &str, int m);
// cal the fix base for hash
// the result is BASE^0, BASE^1,....
vector<long long> precompute(int n)
{
    vector<long long> p(n + 1);
    p[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        p[i] = (p[i - 1] * BASE) % MOD;
    }
    return p;
}

long long comp_hash(const string &str, int m)
{
    long long h = 0;
    for (int i = 0; i < m; i++)
    {
        h = (h * BASE + (str[i] - 'a' + 1)) % MOD;
    }
    return h;
}

vector<vector<pair<pair<int, int>, pair<int, int>>>> Rabin_karp(vector<vector<char>> &grids, vector<string> &keywords)
{
    int rows = grids.size();
    int cols = (rows > 0) ? grids[0].size() : 0;
    int max_pos = max(rows, cols);

    // for rolling hash
    vector<long long> P = precompute(max_pos);
    vector<vector<pair<pair<int, int>, pair<int, int>>>> all_res;

    for (const auto &word : keywords)
    {
        vector<pair<pair<int, int>, pair<int, int>>> res;
        int m = word.length();
        if (m == 0 || m > max_pos)
        {
            all_res.push_back(res);
            continue;
        }

        long long HashWord = comp_hash(word, m);
        // take the hash point according to the lenght of word in this case we take Base^(m-1)
        long long Pm_1 = P[m - 1];
        // if m == 1 then it only check one time
        if (cols >= m && m > 1)
        {
            for (int r = 0; r < rows; r++)
            {
                long long curHash = 0;

                // cal hash for the fist window of r
                for (int i = 0; i < m; i++)
                {
                    curHash = (curHash * BASE + (grids[r][i] - 'a' + 1)) % MOD;
                }

                // check the fist window
                if (curHash == HashWord)
                {
                    bool match = true;
                    for (int i = 0; i < m; i++)
                    {
                        if (grids[r][i] != word[i])
                        {
                            match = false;
                            break;
                        }
                    }
                    if (match)
                        res.push_back({{r, 0}, {r, m - 1}});
                }

                // continue to slide to the end of r
                for (int c = 1; c <= cols - m; c++)
                {
                    long long old_char = grids[r][c - 1] - 'a' + 1; // first char in the prev check
                    long long new_char = grids[r][c + m - 1] - 'a' + 1;
                    // like curHash prev has a1*B^(m-1) + a2*B^(m-2) +...+ a_m
                    // we take a1 out when reach the new window then put the new a_m+1 in then we have a2*B^(m-1) +...+ a_(m+1)
                    curHash = (curHash - (old_char * Pm_1) % MOD + MOD) % MOD;
                    curHash = (curHash * BASE + new_char) % MOD;

                    if (curHash == HashWord)
                    {
                        bool match = true;
                        for (int i = 0; i < m; i++)
                        {
                            if (grids[r][c + i] != word[i])
                            {
                                match = false;
                                break;
                            }
                        }
                        if (match)
                            res.push_back({{r, c}, {r, c + m - 1}});
                    }
                }
            }
        }
        // remain same as above code.-.
        if (rows >= m)
        {
            for (int c = 0; c < cols; c++)
            {
                long long curHash = 0;

                for (int i = 0; i < m; i++)
                {
                    curHash = (curHash * BASE + (grids[i][c] - 'a' + 1)) % MOD;
                }

                if (curHash == HashWord)
                {
                    bool match = true;
                    for (int i = 0; i < m; i++)
                    {
                        if (grids[i][c] != word[i])
                        {
                            match = false;
                            break;
                        }
                    }
                    if (match)
                        res.push_back({{0, c}, {m - 1, c}});
                }

                for (int r = 1; r <= rows - m; r++)
                {
                    long long old_char = grids[r - 1][c] - 'a' + 1;
                    long long new_char = grids[r + m - 1][c] - 'a' + 1;

                    curHash = (curHash - (old_char * Pm_1) % MOD + MOD) % MOD;
                    curHash = (curHash * BASE + new_char) % MOD;

                    if (curHash == HashWord)
                    {
                        bool match = true;
                        for (int i = 0; i < m; i++)
                        {
                            if (grids[r + i][c] != word[i])
                            {
                                match = false;
                                break;
                            }
                        }
                        if (match)
                            res.push_back({{r, c}, {r + m - 1, c}});
                    }
                }
            }
        }
        all_res.push_back(res);
    }

    return all_res;
}

vector<long long> precompute_OC(int n, long long &comparisons)
{
    vector<long long> p(n + 1);
    p[0] = 1;
    for (int i = 1; ++comparisons, i <= n; i++)
    {
        p[i] = (p[i - 1] * BASE) % MOD;
    }
    return p;
}

long long comp_hash_OC(const string &str, int m, long long &comparisons)
{
    long long h = 0;
    for (int i = 0; ++comparisons, i < m; i++)
    {
        h = (h * BASE + (str[i] - 'a' + 1)) % MOD;
    }
    return h;
}

vector<vector<pair<pair<int, int>, pair<int, int>>>> Rabin_karpOperationCount(vector<vector<char>> &grids, vector<string> &keywords, long long &comparisons)
{
    int rows = grids.size();
    int cols = (rows > 0) ? grids[0].size() : 0;
    int max_pos = max(rows, cols);
    ++comparisons;

    // for rolling hash
    vector<long long> P = precompute_OC(max_pos, comparisons);
    vector<vector<pair<pair<int, int>, pair<int, int>>>> all_res;

    for (const auto &word : keywords)
    {
        vector<pair<pair<int, int>, pair<int, int>>> res;
        int m = word.length();
        comparisons += 2;
        if (m == 0 || m > max_pos)
        {
            all_res.push_back(res);
            continue;
        }

        long long HashWord = comp_hash_OC(word, m, comparisons);
        long long Pm_1 = P[m - 1];

        if (++comparisons, cols >= m && (++comparisons, m > 1))
        {
            for (int r = 0; ++comparisons, r < rows; r++)
            {
                long long curHash = 0;
                for (int i = 0; ++comparisons, i < m; i++)
                {
                    curHash = (curHash * BASE + (grids[r][i] - 'a' + 1)) % MOD;
                }

                // check the fist window
                if (++comparisons, curHash == HashWord)
                {
                    bool match = true;
                    for (int i = 0; ++comparisons, i < m; i++)
                    {
                        if (++comparisons, grids[r][i] != word[i])
                        {
                            match = false;
                            break;
                        }
                    }
                    if (++comparisons, match)
                        res.push_back({{r, 0}, {r, m - 1}});
                }

                // continue to slide to the end of r
                for (int c = 1; ++comparisons, c <= cols - m; c++)
                {
                    long long old_char = grids[r][c - 1] - 'a' + 1; // first char in the prev check
                    long long new_char = grids[r][c + m - 1] - 'a' + 1;
                    // like curHash prev has a1*B^(m-1) + a2*B^(m-2) +...+ a_m
                    // we take a1 out when reach the new window then put the new a_m+1 in then we have a2*B^(m-1) +...+ a_(m+1)
                    curHash = (curHash - (old_char * Pm_1) % MOD + MOD) % MOD;
                    curHash = (curHash * BASE + new_char) % MOD;

                    if (++comparisons, curHash == HashWord)
                    {
                        bool match = true;
                        for (int i = 0; ++comparisons, i < m; i++)
                        {
                            if (++comparisons, grids[r][c + i] != word[i])
                            {
                                match = false;
                                break;
                            }
                        }
                        if (++comparisons, match)
                            res.push_back({{r, c}, {r, c + m - 1}});
                    }
                }
            }
        }
        // remain same as above code.-.
        if (++comparisons, rows >= m)
        {
            for (int c = 0; ++comparisons, c < cols; c++)
            {
                long long curHash = 0;

                for (int i = 0; ++comparisons, i < m; i++)
                {
                    curHash = (curHash * BASE + (grids[i][c] - 'a' + 1)) % MOD;
                }

                if (++comparisons, curHash == HashWord)
                {
                    bool match = true;
                    for (int i = 0; ++comparisons, i < m; i++)
                    {
                        if (++comparisons, grids[i][c] != word[i])
                        {
                            match = false;
                            break;
                        }
                    }
                    if (++comparisons, match)
                        res.push_back({{0, c}, {m - 1, c}});
                }

                for (int r = 1; ++comparisons, r <= rows - m; r++)
                {
                    long long old_char = grids[r - 1][c] - 'a' + 1;
                    long long new_char = grids[r + m - 1][c] - 'a' + 1;

                    curHash = (curHash - (old_char * Pm_1) % MOD + MOD) % MOD;
                    curHash = (curHash * BASE + new_char) % MOD;

                    if (++comparisons, curHash == HashWord)
                    {
                        bool match = true;
                        for (int i = 0; ++comparisons, i < m; i++)
                        {
                            if (++comparisons, grids[r + i][c] != word[i])
                            {
                                match = false;
                                break;
                            }
                        }
                        if (++comparisons, match)
                            res.push_back({{r, c}, {r + m - 1, c}});
                    }
                }
            }
        }
        all_res.push_back(res);
    }

    return all_res;
}