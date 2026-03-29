#include "def.h"

using namespace std;
vector<int> buildCharTable(const string& keyword){

    //table for saving positions of char relative to the keyword string
    vector<int> charTable(256, -1);
    int m = keyword.size();
    
    for(int i = 0; i < m; i++){
        int charToInt = keyword[i];
        charTable[charToInt] = i;
    }
    return charTable;
}

vector<vector<pair<pair<int, int>, pair<int, int>>>> Boyer_Moore(vector<vector<char>>& grids,vector<string>& keywords){
    

    int total_row = grids.size(),total_col = grids[0].size();
    int total_keywords = keywords.size();

    vector<vector<pair<pair<int, int>, pair<int, int>>>> result(total_keywords);

    for(int i=0;i<total_keywords;i++){
        vector<pair<pair<int, int>, pair<int, int>>> occurences;

        string keyword = keywords[i];
        vector<int> charTable = buildCharTable(keyword);

        for(int row = 0 ; row<total_row ; row++){

            int k_size = keyword.size();
            int tracker = k_size-1;
            while(tracker < total_col){

                // advance the tracker throughout the row to compare with keyword
                for(int idx = k_size-1; idx>=0 ; idx--){

                    //correct idx position relative to the row itself
                    int idx_from_tracker = tracker-(k_size-1-idx);

                    if(keyword[idx] != grids[row][idx_from_tracker]){

                        int trackerToInt = grids[row][idx_from_tracker];
                        if( charTable[trackerToInt] == -1 ){
                            //if the char at the tracker is not in the table so we move the tracker accordingly
                            tracker += k_size - (tracker - idx_from_tracker);
                        }
                        else{
                            //we move the tracker to the position where it matches so not left out any cases
                            tracker += max(1, idx - charTable[trackerToInt]);
                        }
                        break;
                    }
                    if(idx==0){

                        occurences.push_back({{row,tracker-(k_size - 1)},{row,tracker}});
                        tracker++;
                    }
                }
            }
        }

        //exacly the same but for columns
        for(int col = 0 ; col<total_col ; col++){

            int k_size = keyword.size();
            int tracker = k_size-1;
            while(tracker < total_row){

                for(int idx = k_size-1; idx>=0 ; idx--){

                    int idx_from_tracker = tracker-(k_size-1-idx);

                    if(keyword[idx] != grids[idx_from_tracker][col]){
            
                        int trackerToInt = grids[idx_from_tracker][col];
                        if( charTable[trackerToInt] == -1 ){
                            tracker += k_size - (tracker - idx_from_tracker);
                        }
                        else{
                            tracker += max(1, idx - charTable[trackerToInt]);
                        }
                        break;
                    }
                    if(idx==0){
                        occurences.push_back({{tracker-(k_size - 1),col},{tracker,col}});
                        tracker++;
                    }
                }
            }
        }
        sort(occurences.begin(), occurences.end());
        for(int j = 0; j < occurences.size(); j++){
            if(j == 0 || occurences[j] != occurences[j-1]){
                result[i].push_back(occurences[j]);
            }
        }
    }
    return result;
}

vector<vector<pair<pair<int, int>, pair<int, int>>>> Boyer_Moore(vector<vector<char>>& grids,vector<string>& keywords, long long& comparisons){
    
    

    int total_row = grids.size(),total_col = grids[0].size();
    int total_keywords = keywords.size();

    vector<vector<pair<pair<int, int>, pair<int, int>>>> result(total_keywords);

    for(int i=0;i<total_keywords;i++){

        vector<pair<pair<int, int>, pair<int, int>>> occurences;

        string keyword = keywords[i];
        vector<int> charTable = buildCharTable(keyword);

        for(int row = 0 ; row<total_row ; row++){

            int k_size = keyword.size();
            int tracker = k_size-1;
            while(tracker < total_col){

                for(int idx = k_size-1; idx>=0 ; idx--){

                    int idx_from_tracker = tracker-(k_size-1-idx);

                    if(comparisons++,keyword[idx] != grids[row][idx_from_tracker]){
            
                        int trackerToInt = grids[row][idx_from_tracker];
                        if( charTable[trackerToInt] == -1 ){
                            tracker += k_size - (tracker - idx_from_tracker);
                        }
                        else{
                            tracker += max(1, idx - charTable[trackerToInt]);
                        }
                        break;
                    }
                    if(idx==0){

                        occurences.push_back({{row,tracker-(k_size - 1)},{row,tracker}});
                        tracker++;
                    }
                }
            }
        }

        for(int col = 0 ; col<total_col ; col++){

            int k_size = keyword.size();
            int tracker = k_size-1;
            while(tracker < total_row){

                for(int idx = k_size-1; idx>=0 ; idx--){

                    int idx_from_tracker = tracker-(k_size-1-idx);

                    if(comparisons++ ,keyword[idx] != grids[idx_from_tracker][col]){
            
                        int trackerToInt = grids[idx_from_tracker][col];
                        if( charTable[trackerToInt] == -1 ){
                            tracker += k_size - (tracker - idx_from_tracker);
                        }
                        else{
                            tracker += max(1, idx - charTable[trackerToInt]);
                        }
                        break;
                    }
                    if(idx==0){
                        occurences.push_back({{tracker-(k_size - 1),col},{tracker,col}});
                        tracker++;
                    }
                }
            }
        }
        sort(occurences.begin(), occurences.end());
        for(int j = 0; j < occurences.size(); j++){
            if(j == 0 || occurences[j] != occurences[j-1]){
                result[i].push_back(occurences[j]);
            }
        }
    }
    return result;
}

