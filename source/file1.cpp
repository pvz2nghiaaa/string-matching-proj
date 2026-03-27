#include <iostream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <chrono>
#include <fstream>
#include <utility>
//#include "def.h"

using namespace std;

// algorithm
char* algorithmName = nullptr;
int IDAlgorithm = -1;
const char* algorithmPrototypeName[] = {
	"bf", "rk", "kmp", "bm"
};
const char* algorithmFullName[] = {
	"Brute-Force", "Rabin-Karp", "KMP", "Boyer-Moore"
};
vector<vector<pair<pair<int, int>, pair<int, int>>>> (*const listSort[])(vector<vector<char>>, vector<string>) = {

};
vector<vector<pair<pair<int, int>, pair<int, int>>>> (*const listSortComparisonsCount[])(vector<vector<char>>, vector<string>, long long&) = {

};

// file name
char* inputFile = nullptr;
char* outputFile = nullptr;

// result
vector<vector<pair<pair<int, int>, pair<int, int>>>> result;

void findAlgorithmUsed() {
	// process algorithm used from algorithm names
	for (int i = 0; i < 4; i++) {
		if (algorithmName && strcmp(algorithmName, algorithmPrototypeName[i]) == 0)
			return IDAlgorithm = i, void();
	}
}

void readInputFile(vector<vector<char>>& grids, vector<string>& keywords) {
	ifstream fin(inputFile);
	int n, m, k;
	fin >> n >> m;
    grids.assign(n, vector<char>(m));
	for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            fin >> grids[i][j];
    fin >> k;
    keywords.assign(k, "");
    for (int i = 0; i < k; i++)
        fin >> keywords[i];
	fin.close();
}

double executionTimeAlgorithm(vector<vector<char>>& grids, vector<string>& keywords) {
	auto Start = chrono::high_resolution_clock::now();
	result = listSort[IDAlgorithm](grids, keywords);
	auto End = chrono::high_resolution_clock::now();
	chrono::duration<double, milli> duration = End - Start;
	return duration.count();
}

long long comparisionsAlgorithm(vector<vector<char>>& grids, vector<string>& keywords) {
	long long comparisons = 0;
	listSortComparisonsCount[IDAlgorithm](grids, keywords, comparisons);
	return comparisons;
}

void outputResult(vector<string> keywords, double executionTime, long long comparisons) {
	ofstream fout(outputFile);
    for (int i = 0; i < (int)keywords.size(); i++){
        string keyword = keywords[i];
        auto listLocation = result[i];
        fout << keyword << ": ";
        if (listLocation.empty()){
            fout << "not found\n";
        } else {
            int n = listLocation.size();
            for (int j = 0; j < n; j++)
                fout << "(" << listLocation[j].first.first << ", " << listLocation[j].first.second << ") -> " <<
                "(" << listLocation[j].second.first << ", " << listLocation[j].second.second << ");";
            fout << "\n";
        }
    }
    fout << "--------------------------------\n";
    fout << "Algorithm: " << algorithmFullName[IDAlgorithm] << "\n";
    fout << "Comparisons: " << comparisons << "\n";
    fout << "Execution Time: " << setprecision(3) << fixed << executionTime;
	fout.close();
}

void modeExecution() {
    vector<vector<char>> grids;
    vector<string> keywords;

    readInputFile(grids, keywords);
    double executionTime = executionTimeAlgorithm(grids, keywords);
    long long comparisons = comparisionsAlgorithm(grids, keywords);
    outputResult(keywords, executionTime, comparisons);
}

int main(int argc, char* argv[]) {
    for (int pos_argv = 1; pos_argv < argc; pos_argv += 2){
        // checking errors
        if (pos_argv + 1 >= argc) {
            cout << "INVALID ARGUMENTS!\n";
            return 0;
        }
        // comparing prototypes
        if (strcmp(argv[pos_argv], "-a") == 0)
            algorithmName = argv[pos_argv + 1];
        else if (strcmp(argv[pos_argv], "-i") == 0)
            inputFile = argv[pos_argv + 1];
        else if (strcmp(argv[pos_argv], "-o") == 0)
            outputFile = argv[pos_argv + 1];
        else {
            cout << "NO REGCONIZED MODE FOUND!\n";
            return 0;
        }
    }
    if (!inputFile || !outputFile || !algorithmName){
        cout << "MISSING ARGUMENTS!\n";
        return 0;
    }
    ifstream fin(inputFile);
    if (!fin) {
        cout << "INPUT FILE NOT FOUND!\n";
        return 0;
    }
    fin.close();

	findAlgorithmUsed();
	if (IDAlgorithm == -1){
        cout << "ALGORITHM NOT FOUND!\n";
        return 0;
	}
	modeExecution();

	return 0;
}
