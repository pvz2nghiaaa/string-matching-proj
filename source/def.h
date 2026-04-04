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
#include <unordered_map>

#define ll long long
using namespace std;

vector<vector<pair<pair<int, int>, pair<int, int>>>> bruteforce(vector<vector<char>>& grids, vector<string>& keywords);
vector<vector<pair<pair<int, int>, pair<int, int>>>> bruteforce(vector<vector<char>>& grids, vector<string>& keywords, long long& comparisons);

vector<vector<pair<pair<int, int>, pair<int, int>>>> Boyer_Moore(vector<vector<char>>& grids, vector<string>& keywords, long long& comparisons);
vector<vector<pair<pair<int, int>, pair<int, int>>>> Boyer_Moore(vector<vector<char>>& grids, vector<string>& keywords);

vector<vector<pair<pair<int, int>, pair<int, int>>>> Rabin_karpOperationCount(vector<vector<char>> &grids, vector<string> &keywords, long long &comparisons);
vector<vector<pair<pair<int, int>, pair<int, int>>>> Rabin_karp(vector<vector<char>> &grids, vector<string> &keywords);

vector<vector<pair<pair<int, int>, pair<int, int>>>> KMP(vector<vector<char>>& grids, vector<string>& keywords);
vector<vector<pair<pair<int, int>, pair<int, int>>>> KMPComparisonCounts(vector<vector<char>>& grids, vector<string>& keywords, long long& comparisons);


extern int dx[];
extern int dy[];

struct Node
{
    unordered_map<char, int> nextChar;
    vector<pair<int, int>> endpoints;

    Node() {}
};

struct Trie
{
    vector<Node> tree{Node()};
    int numNode = 1;

    void add(vector<vector<char>>& grids, int x, int y, const int dirX, const int dirY)
    {
        int id = 0;
        while (x < (int)grids.size() && y < (int)grids[0].size())
        {
            if (tree[id].nextChar.find(grids[x][y]) == tree[id].nextChar.end())
            {
                tree[id].nextChar[grids[x][y]] = numNode;
                tree.push_back(Node());
                ++numNode;
            }
            
            id = tree[id].nextChar[grids[x][y]];
            tree[id].endpoints.push_back({x, y});

            x += dirX;
            y += dirY;
        }    
    }

    void findKeyword(vector<pair<pair<int, int>, pair<int, int>>>& occurrences, string& keyword, const int dirX, const int dirY)
    {
        int id = 0;
        int len = (int)keyword.length();
        for (int i = 0; i < len; i++) // traverse trie
            if (tree[id].nextChar.find(keyword[i]) == tree[id].nextChar.end())
                return;
            else
                id = tree[id].nextChar[keyword[i]];
        
        for (pair<int, int> endpoint: tree[id].endpoints) // add occurrences to result
            occurrences.push_back({{endpoint.first - dirX * (len - 1), endpoint.second - dirY * (len - 1)}, endpoint});
    }
};

#endif