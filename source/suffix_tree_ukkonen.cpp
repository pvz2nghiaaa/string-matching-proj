#include "def.h"

using namespace std;

struct Node;

struct Edge{
    int start;
    int *end;
    Node* next_child;

};

struct Node{
    Edge* list_edge[27] = {};
    Node* suffix_link;
};

Node* active_node;
Node* root;
int active_edge; // point to the current index of string s
int active_length;
int remainder_in_queue;
int* global_end;

Node* create_node(){
    Node* node = new Node;
    node -> suffix_link = nullptr;
    return node;
}

Edge* create_edge(int start, int* end = global_end){
    Edge* edge = new Edge;
    edge -> start = start;
    edge -> end = end;
    edge -> next_child = nullptr;
    return edge;
}

int get_key(char u){
    if (u == '$')
        return 26;
    return u - 'a';
}

Edge* exist_edge(string &s, int i){
    return active_node -> list_edge[get_key(s[i])];
}

void walk_down(string &s){
    Edge* e = active_node -> list_edge[get_key(s[active_edge])];
    while(active_length >= (*e -> end) - (e -> start) + 1){
        int edge_len = (*e->end) - (e->start) + 1;
        active_length -= edge_len;
        active_edge += edge_len;
        active_node = e -> next_child;

        if (active_length > 0)
            e = active_node -> list_edge[get_key(s[active_edge])];
        else break;
    }
}

void extend(string &s, int i){
    Node* last_created_internal_node = nullptr;
    ++remainder_in_queue;
    ++(*global_end);

    while (remainder_in_queue){
        if (active_length == 0){
            if (exist_edge(s, i)){
                if (last_created_internal_node != nullptr) {
                    last_created_internal_node->suffix_link = active_node;
                    last_created_internal_node = nullptr;
                }
                active_edge = i;
                ++active_length;
                break;
            }
            else {
                active_node -> list_edge[get_key(s[i])] = create_edge(i);
                --remainder_in_queue;
                if (last_created_internal_node != nullptr) {
                    last_created_internal_node->suffix_link = active_node;
                    last_created_internal_node = nullptr;
                }
                if (active_node != root) {
                    active_node = active_node->suffix_link;
                }
            }
        }
        else {
            walk_down(s);

            if (active_length == 0)
                continue;

            Edge *e = active_node -> list_edge[get_key(s[active_edge])];
            if (s[i] == s[e -> start + active_length]){
                ++active_length;
                break;
            }
            else {
                int split_end = e -> start + active_length - 1;
                int *old_end = e -> end;
                e -> end = new int(split_end);
                Node* split_node = create_node();
                split_node -> suffix_link = root;
                // first edge
                split_node -> list_edge[get_key(s[i])] = create_edge(i);
                // second edge
                Edge* updated_edge = create_edge(split_end + 1, old_end);
                updated_edge -> next_child = e -> next_child;
                split_node -> list_edge[get_key(s[e -> start + active_length])] = updated_edge;
                // middle edge
                e -> next_child = split_node;
                // suffix link
                if (last_created_internal_node != nullptr)
                    last_created_internal_node -> suffix_link = split_node;

                remainder_in_queue--;
                last_created_internal_node = split_node;

                if (active_node == root && active_length > 0) {
                    active_length--;
                    active_edge = i - remainder_in_queue + 1;
                } else if (active_node != root) {
                    active_node = active_node->suffix_link;
                }
            }
        }
    }
}

void construct_suffix_tree(string &s){
    s.push_back('$');

    int n = s.length();
    root = create_node();
    active_node = root;
    active_edge = -1;
    active_length = 0;
    global_end = new int(-1);
    remainder_in_queue = 0;

    for (int i = 0; i < n; i++){
        extend(s, i);
    }

}

void find_occurrences_subtree(Node* root, int len_t, int string_depth, vector<pair<pair<int, int>, pair<int, int>>>& result, int pos, bool checkRow){
    if (root == nullptr)
        return ;
    for (auto const& e : root -> list_edge) if (e){
        int edge_len = (*e -> end) - e -> start + 1;
        string_depth += edge_len;
        if (e -> next_child)
            find_occurrences_subtree(e -> next_child, len_t, string_depth, result, pos, checkRow);
        else if (checkRow)
            result.push_back({{pos, (*e -> end) - string_depth + 1}, {pos, (*e -> end) - string_depth + len_t}});
        else result.push_back({{(*e -> end) - string_depth + 1, pos}, {(*e -> end) - string_depth + len_t, pos}});
        string_depth -= edge_len;
    }
}

void find_occurrences(Node* root, string& s, string& T, vector<pair<pair<int, int>, pair<int, int>>>& result, int pos, bool checkRow) {
    Node* current_node = root;
    int i = 0;
    int m = T.length();
    int string_depth = 0;

    while (i < m) {
        if (!current_node -> list_edge[get_key(T[i])])
            return ;

        Edge* e = current_node->list_edge[get_key(T[i])];
        int edge_len = (*e -> end) - e -> start + 1;
        int j = 0; // for traveling across the edge
        while (j < edge_len && i < m) {
            if (s[e -> start + j] != T[i])
                return ;
            j++;
            i++;
        }
        if (i == m) {
            if (e -> next_child == nullptr){
                if (checkRow)
                    result.push_back({{pos, e -> start + j - m}, {pos, e -> start + j - 1}});
                else result.push_back({{e -> start + j - m, pos}, {e -> start + j - 1, pos}});
            }
            else find_occurrences_subtree(e -> next_child, m, string_depth + edge_len, result, pos, checkRow);

            return ;
        }
        string_depth += edge_len;
        current_node = e -> next_child;
    }
}

void find_occurrences(Node* root, string& s, string& T, vector<pair<pair<int, int>, pair<int, int>>>& result, int pos, bool checkRow, long long& comparisons) {
    Node* current_node = root;
    int i = 0;
    int m = T.length();
    int string_depth = 0;

    while (i < m) {
        if (!current_node -> list_edge[get_key(T[i])])
            return ;

        Edge* e = current_node->list_edge[get_key(T[i])];
        int edge_len = (*e -> end) - e -> start + 1;
        int j = 0; // for traveling across the edge
        while (j < edge_len && i < m) {
            if (++comparisons, s[e -> start + j] != T[i])
                return ;
            j++;
            i++;
        }
        if (i == m) {
            if (e -> next_child == nullptr){
                if (checkRow)
                    result.push_back({{pos, e -> start + j - m}, {pos, e -> start + j - 1}});
                else result.push_back({{e -> start + j - m, pos}, {e -> start + j - 1, pos}});
            }
            else find_occurrences_subtree(e -> next_child, m, string_depth + edge_len, result, pos, checkRow);

            return ;
        }
        string_depth += edge_len;
        current_node = e -> next_child;
    }
}

void free_internal_nodes(Node* node){
    for (auto const& e : node -> list_edge) if (e){
        if (e -> next_child)
            free_internal_nodes(e -> next_child);
        if (e -> end != global_end)
            delete e -> end;
        delete e;
    }
    delete node;
}

void free_memory(){
    free_internal_nodes(root);
    delete global_end;
    active_node = root = nullptr;
    global_end = nullptr;
}

vector<vector<pair<pair<int, int>, pair<int, int>>>> suffix_tree_ukkonen(vector<vector<char>>& grids, vector<string>& keywords){
    string s;
    int n = grids.size();
    int m = grids[0].size();
    int t = keywords.size();
    vector<vector<pair<pair<int, int>, pair<int, int>>>> result(t, vector<pair<pair<int, int>, pair<int, int>>>());
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++)
            s += grids[i][j];
        construct_suffix_tree(s);
        for (int k = 0; k < t; k++)
            find_occurrences(root, s, keywords[k], result[k], i, 1);
        s.clear();
        free_memory();
    }
    for (int j = 0; j < m; j++){
        for (int i = 0; i < n; i++)
            s += grids[i][j];
        construct_suffix_tree(s);
        for (int k = 0; k < t; k++)
            if (keywords[k].size() > 1)
                find_occurrences(root, s, keywords[k], result[k], j, 0);
        s.clear();
        free_memory();
    }
    return result;
}


vector<vector<pair<pair<int, int>, pair<int, int>>>> suffix_tree_ukkonen(vector<vector<char>>& grids, vector<string>& keywords, long long& comparisons){
    comparisons = 0;
    string s;
    int n = grids.size();
    int m = grids[0].size();
    int t = keywords.size();
    vector<vector<pair<pair<int, int>, pair<int, int>>>> result(t, vector<pair<pair<int, int>, pair<int, int>>>());
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++)
            s += grids[i][j];
        construct_suffix_tree(s);
        for (int k = 0; k < t; k++)
            find_occurrences(root, s, keywords[k], result[k], i, 1, comparisons);
        s.clear();
        free_memory();
    }
    for (int j = 0; j < m; j++){
        for (int i = 0; i < n; i++)
            s += grids[i][j];
        construct_suffix_tree(s);
        for (int k = 0; k < t; k++)
            if (keywords[k].size() > 1)
                find_occurrences(root, s, keywords[k], result[k], j, 0, comparisons);
        s.clear();
        free_memory();
    }
    return result;
}
