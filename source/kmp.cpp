#include "def.h"

vector<vector<pair<pair<int, int>, pair<int, int>>>> KMP(vector<vector<char>>& grids, vector<string>& keywords)
{
	vector<vector<pair<pair<int, int>, pair<int, int>>>> total_res;
	if (grids.empty() || grids[0].empty() || keywords.empty()) return total_res;
	int r = grids.size(),
	c = grids[0].size();
	for (int j = 0; j < keywords.size(); j++){
		vector<pair<pair<int, int>, pair<int, int>>> res;
		vector<int> lps(keywords[j].size(), 0);
		// precompute 
		int k = 0;
		int len = keywords[j].size();
		for (int i = 1; i < len; i++){
			while (k > 0 && keywords[j][i] != keywords[j][k])
				k = lps[k-1];
			if (keywords[j][i] == keywords[j][k])
				k++;
			lps[i] = k;
		}

		// row, horizontal
		for (int row = 0; row < r; row++){
			// vector<int> match(c, 0);
			int k = 0;
			for (int i = 0; i < c; i++){
				while (k > 0 && grids[row][i] != keywords[j][k])
					k = lps[k-1];
				if (grids[row][i] == keywords[j][k])
					k++;
				// match[i] = k;
				if (k == len){
					res.push_back({{row, i-k+1},{row, i}});
					k = lps[k-1];
				}
			}
		}
		// col, vertical
		if (len > 1){
			for (int col = 0; col < c; col++){
				int k = 0;
				for (int i = 0; i < r; i++){
					while (k > 0 && grids[i][col] != keywords[j][k])
						k = lps[k-1];
					if (grids[i][col] == keywords[j][k])
						k++;
					// match[i] = k;
					if (k == len){
						res.push_back({{i-k+1, col},{i, col}});
						k = lps[k-1];
					}
				}		
			}
		}

		total_res.push_back(res);
	}
	return total_res;
}

vector<vector<pair<pair<int, int>, pair<int, int>>>> KMPComparisonCounts(vector<vector<char>>& grids, vector<string>& keywords, long long& comparisons)
{
	comparisons = 0;
	vector<vector<pair<pair<int, int>, pair<int, int>>>> total_res;
	comparisons += 3;
	if (grids.empty() || grids[0].empty() || keywords.empty()) return total_res;
	int r = grids.size(),
		c = grids[0].size();
	for (int j = 0; ++comparisons, j < keywords.size(); j++){
		vector<pair<pair<int, int>, pair<int, int>>> res;
		vector<int> lps(keywords[j].size(), 0);
		// precompute 
		int k = 0;
		int len = keywords[j].size();
		for (int i = 1; ++comparisons, i < len; i++){
			while ((++comparisons, k > 0) && (++comparisons, keywords[j][i] != keywords[j][k]))
				k = lps[k-1];
			if (++comparisons, keywords[j][i] == keywords[j][k])
				k++;
			lps[i] = k;
		}

		// row, horizontal
		for (int row = 0; ++comparisons, row < r; row++){
			// vector<int> match(c, 0);
			int k = 0;
			for (int i = 0; ++comparisons, i < c; i++){
				while ((++comparisons, k > 0) && (++comparisons, grids[row][i] != keywords[j][k]))
					k = lps[k-1];
				if (++comparisons, grids[row][i] == keywords[j][k])
					k++;
				// match[i] = k;
				if (++comparisons, k == len){
					res.push_back({{row, i-k+1},{row, i}});
					k = lps[k-1];
				}
			}
		}
		// col, vertical
		if (++comparisons, len > 1){
			for (int col = 0; ++comparisons, col < c; col++){
				int k = 0;
				for (int i = 0; ++comparisons, i < r; i++){
					while ((++comparisons, k > 0) && (++comparisons, grids[i][col] != keywords[j][k]))
						k = lps[k-1];
					if (++comparisons, grids[i][col] == keywords[j][k])
						k++;
					// match[i] = k;
					if (++comparisons, k == len){
						res.push_back({{i-k+1, col},{i, col}});
						k = lps[k-1];
					}
				}		
			}
		}

		total_res.push_back(res);
	}
	return total_res;
}