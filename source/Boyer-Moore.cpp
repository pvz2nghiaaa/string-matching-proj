#include "def.h"

using namespace std;
vector<int> buildCharTable(const string& keyword){

    //table for saving positions of char relative to the keyword string
    vector<int> charTable(26, -1);
    int m = keyword.size();
    
    for(int i = 0; i < m; i++){
        int charToInt = keyword[i] - 'a';
        charTable[charToInt] = i;
    }
    return charTable;
}

vector<int> buildSuffixTable(const string& keyword){
    int n = keyword.size();

    vector<int> suffixTable(n,0);
    suffixTable[n-1] = n;

    //the suffixTable[i] showcase the number of matching chars from right to left from keyword[0->i] to keyword
    //ex: keyword : AIRPLANE 
    //suffix[2] will compare AIR with
    //                  AIRPLANE which is 0 since at the beginning R != E

    //BUBBLE PRINCIPLE
    //the bubble is the matched section/suffix of the keyword showcasing that there is also an identical suffix at the end of the keyword
    //literate i through the keyword, if i is out of the bubble,we have to manually compare from the leftmost of the keyword while resetting the borders if necessary
    //if i is in the bubble we already know that it is in the matched suffix of a substring so we paste in the value from the relative position from the end.

    // initialize borders for comparison bubble or accademically known as z-box
    int left = n-1,right = n-1;

    for(int i= n-2 ;i >= 0; i--){
        int idx_in_substr = (n-1)-right +i;
        //if i is in the bubble
        if (i > left && suffixTable[idx_in_substr] < i - left) {
           suffixTable[i] = suffixTable[idx_in_substr];
        } 
        // if i is outside the bubble
        else {
            if(i < left){
                left = i;
            }
            right = i;
            while(left >= 0 && keyword[left] == keyword[left + n - 1 - right]){
                left--;
            }
            suffixTable[i] = right - left;
        }
    }
    return suffixTable;
}

vector<int> buildShiftSuffixTable(const string& keyword){

    int n = keyword.size();

    vector<int> suffixTable = buildSuffixTable(keyword);
    vector<int> shiftSuffixTable(n+1,n);
    // size is n+1 to advance the index safely if there is a perfect match and n is the cannonical slide distance to get the word out of the view


    for(int i = n - 1; i >= -1; i--){
        //if it matches perfectly or [confusion drumroll...] a part of the suffix of the keyword matches the beginning of the keyword
        //hence suffixTable[i] == i + 1 cause it's length is i+1 so from [0,i] matches the end
        //this is an edge case
        if(i == -1 || suffixTable[i] == i + 1){ 

            //slide the prefix of the keyword to the suffix of the keyword
            int slide_distance = n - 1 - i;
            
            for (int target_idx = 0; target_idx < slide_distance; target_idx++) {
                if(shiftSuffixTable[target_idx] == n){
                    //take min to not skip any cases, the shorter the better;
                    shiftSuffixTable[target_idx] = min(shiftSuffixTable[target_idx], slide_distance);
                }
            }
        }
    }

    //main case meaning prefix of the keyword matches with prefix of substring in keyword
    for(int i = 0; i <= n - 2; ++i){
        //length of the matching prefix of substring
        int copy_length = suffixTable[i];

        if(copy_length > 0){
            int mismatch_index = n - 1 - copy_length;
            int slide_distance = n - 1 - i;
            
            shiftSuffixTable[mismatch_index] = slide_distance;
        }
    }
    //bug here create extra space but doesn't account for change mee badd
    shiftSuffixTable[n] = shiftSuffixTable[0];

    return shiftSuffixTable;
}

vector<vector<pair<pair<int, int>, pair<int, int>>>> Boyer_Moore(vector<vector<char>>& grids,vector<string>& keywords){
    
    vector<vector<pair<pair<int, int>, pair<int, int>>>> result;

    int total_row = grids.size(),total_col = grids[0].size();
    int total_keywords = keywords.size();

    for(int i=0;i<total_keywords;i++){
        vector<pair<pair<int, int>, pair<int, int>>> occurences;

        string keyword = keywords[i];
        vector<int> charTable = buildCharTable(keyword);
        vector<int> suffixTable = buildShiftSuffixTable(keyword); 

        for(int row = 0 ; row<total_row ; row++){

            int k_size = keyword.size();
            int tracker = k_size-1;
            while(tracker < total_col){

                // advance the tracker throughout the row to compare with keyword
                int bad = 0,good = 0;
                for(int idx = k_size-1; idx>=0 ; idx--){

                    //correct idx position relative to the row itself
                    int idx_from_tracker = tracker-(k_size-1-idx);

                    if(keyword[idx] != grids[row][idx_from_tracker]){

                        int trackerToInt = grids[row][idx_from_tracker] - 'a';
                        if( charTable[trackerToInt] == -1 ){
                            //if the char at the tracker is not in the table so we move the tracker accordingly
                            bad = k_size - (tracker - idx_from_tracker);
                        }
                        else{
                            //we move the tracker to the position where it matches so not left out any cases
                            bad = max(1, idx - charTable[trackerToInt]);
                        }
                        good = suffixTable[idx];
                        break;
                    }
                    if(idx==0){

                        occurences.push_back({{row,tracker-(k_size - 1)},{row,tracker}});
                        bad = 1;
                        //utilising the extra space from building the shiftsuftable
                        good = suffixTable[k_size];
                    }
                    
                }
                //max cause it is safe either way so forward tracker for maximum efficiency
                tracker+= max(bad,good);
            }
        }


        //exacly the same but for columns
        for(int col = 0 ; col<total_col ; col++){
            int k_size = keyword.size();
            if(k_size == 1){
                continue;
            }
            int tracker = k_size-1;
            while(tracker < total_row){
    
                int bad = 0, good = 0;
                for(int idx = k_size-1; idx>=0 ; idx--){

                    int idx_from_tracker = tracker-(k_size-1-idx);

                    if(keyword[idx] != grids[idx_from_tracker][col]){
            
                        int trackerToInt = grids[idx_from_tracker][col] - 'a'; 
                        if( charTable[trackerToInt] == -1 ){
                            bad = k_size - (tracker - idx_from_tracker);
                        }
                        else{
                            bad = max(1, idx - charTable[trackerToInt]);
                        }
                        good = suffixTable[idx];
                        break;
                    }
                    if(idx==0){
                        occurences.push_back({{tracker-(k_size - 1),col},{tracker,col}});
                        bad = 1;
                        good = suffixTable[k_size];
                    }
                }
                tracker += max(bad, good);
            }
        }
        result.push_back(occurences);
    }
    return result;
}

vector<vector<pair<pair<int, int>, pair<int, int>>>> Boyer_Moore(vector<vector<char>>& grids,vector<string>& keywords, long long& comparisons){
    
    vector<vector<pair<pair<int, int>, pair<int, int>>>> result;

    int total_row = grids.size(),total_col = grids[0].size();
    int total_keywords = keywords.size();

    for(int i=0;i<total_keywords;i++){

        vector<pair<pair<int, int>, pair<int, int>>> occurences;

        string keyword = keywords[i];
        vector<int> charTable = buildCharTable(keyword);
        vector<int> suffixTable = buildShiftSuffixTable(keyword);

        for(int row = 0 ; row<total_row ; row++){

            int k_size = keyword.size();
            int tracker = k_size-1;
            while(tracker < total_col){
                
                int bad = 0, good = 0;
                for(int idx = k_size-1; idx>=0 ; idx--){

                    int idx_from_tracker = tracker-(k_size-1-idx);

                    if(comparisons++,keyword[idx] != grids[row][idx_from_tracker]){
            
                        int trackerToInt = grids[row][idx_from_tracker] - 'a';
                        if( charTable[trackerToInt] == -1 ){
                            bad = k_size - (tracker - idx_from_tracker);
                        }
                        else{
                            bad = max(1, idx - charTable[trackerToInt]);
                        }
                        good = suffixTable[idx];
                        break;
                    }
                    if(idx==0){

                        occurences.push_back({{row,tracker-(k_size - 1)},{row,tracker}});
                        bad = 1;
                        good = suffixTable[k_size];
                    }
                }
                tracker += max(bad, good);
            }
        }

        for(int col = 0 ; col<total_col ; col++){

            int k_size = keyword.size();
            if(k_size == 1){
                continue;
            }
            int tracker = k_size-1;
            while(tracker < total_row){
                
                int bad = 0, good = 0;
                for(int idx = k_size-1; idx>=0 ; idx--){

                    int idx_from_tracker = tracker-(k_size-1-idx);

                    if(comparisons++ ,keyword[idx] != grids[idx_from_tracker][col]){
            
                        int trackerToInt = grids[idx_from_tracker][col] - 'a';
                        if( charTable[trackerToInt] == -1 ){
                            bad = k_size - (tracker - idx_from_tracker);
                        }
                        else{
                            bad = max(1, idx - charTable[trackerToInt]);
                        }
                        good = suffixTable[idx];
                        break;
                    }
                    if(idx==0){
                        occurences.push_back({{tracker-(k_size - 1),col},{tracker,col}});
                        bad = 1;
                        good = suffixTable[k_size];
                    }
                }
                tracker += max(bad, good);
            }
        }
        result.push_back(occurences);
    }
    return result;
}