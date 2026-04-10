#include <bits/stdc++.h>
using namespace std;

// ===== RANDOM ENGINE =====
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int randInt(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

// bias nhẹ để tạo case thú vị (không quá cực đoan)
char randChar() {
    int x = randInt(1, 100);
    if (x <= 40) return 'a';          // 40% 'a'
    return 'a' + randInt(0, 25);      // còn lại random
}

string randString(int len) {
    string s;
    for (int i = 0; i < len; i++)
        s += randChar();
    return s;
}

// ================== 1. NO MATCH ==================
void generateNoMatch(int R, int C, int K,
                     vector<vector<char>>& grid,
                     vector<string>& keywords) {

    grid.assign(R, vector<char>(C));

    keywords.clear();

    // random chọn kiểu test
    bool nearlyMatchMode = randInt(0, 1); // 0 = no match dễ, 1 = nearly match

    if (!nearlyMatchMode) {
        // ================== CASE 1: NO MATCH THUẦN ==================
        // grid random KHÔNG chứa 'z'
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++) {
                char ch = randChar();
                if (ch == 'z') ch = 'y';
                grid[i][j] = ch;
            }

        // keyword toàn 'z' → chắc chắn không match
        for (int i = 0; i < K; i++) {
            int len = randInt(3, 10);
            keywords.push_back(string(len, 'z'));
        }
    } else {
        // ================== CASE 2: NEARLY MATCH ==================
        // grid: mostly 'a'
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++) {
                if (randInt(1, 100) <= 85)
                    grid[i][j] = 'a';
                else
                    grid[i][j] = 'a' + randInt(0, 25);
            }

        // keyword: aaaa...ab
        for (int i = 0; i < K; i++) {
            int len = randInt(5, 12);

            string s(len - 1, 'a'); // match gần hết
            s += 'b';               // fail ở cuối

            keywords.push_back(s);
        }
    }
}

// ================== 2. SINGLE MATCH ==================
void generateSingleMatch(int R, int C, int K,
                         vector<vector<char>>& grid,
                         vector<string>& keywords) {

    grid.assign(R, vector<char>(C));

    // random grid
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            grid[i][j] = randChar();

    keywords.clear();

    for (int i = 0; i < K; i++) {
        int len = randInt(3, min(10, max(R, C)));

        string s = randString(len);

        // đảm bảo chèn được
        bool horizontal = (len <= C) ? randInt(0, 1) : false;

        if (horizontal) {
            int row = randInt(0, R - 1);
            int col = randInt(0, C - len);

            for (int j = 0; j < len; j++)
                grid[row][col + j] = s[j];
        } else {
            int col = randInt(0, C - 1);
            int row = randInt(0, R - len);

            for (int j = 0; j < len; j++)
                grid[row + j][col] = s[j];
        }

        keywords.push_back(s);
    }
}

// ================== 3. MULTIPLE MATCH ==================
void generateMultipleMatch(int R, int C, int K,
                          vector<vector<char>>& grid,
                          vector<string>& keywords) {

    grid.assign(R, vector<char>(C));

    // random grid
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            grid[i][j] = randChar();

    keywords.clear();

    for (int i = 0; i < K; i++) {
        int len = randInt(3, min(10, max(R, C)));
        string s = randString(len);

        keywords.push_back(s);

        int times = randInt(2, 6); // xuất hiện nhiều lần

        for (int t = 0; t < times; t++) {
            bool horizontal = (len <= C) ? randInt(0, 1) : false;

            if (horizontal) {
                int row = randInt(0, R - 1);
                int col = randInt(0, C - len);

                for (int j = 0; j < len; j++)
                    grid[row][col + j] = s[j];
            } else if (len <= R) {
                int col = randInt(0, C - 1);
                int row = randInt(0, R - len);

                for (int j = 0; j < len; j++)
                    grid[row + j][col] = s[j];
            }
        }
    }
}

// ================== WRITE ==================
void writeToFile(const string& filename,
                 const vector<vector<char>>& grid,
                 const vector<string>& keywords) {

    ofstream out(filename);

    int R = grid.size();
    int C = grid[0].size();

    out << R << " " << C << "\n";

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            out << grid[i][j];
            // if (j < C - 1) out << " ";
        }
        out << "\n";
    }

    out << keywords.size() << "\n";
    for (auto& s : keywords)
        out << s << "\n";
}

// ================== MAIN ==================
int main(int argc, char* argv[]) {
    if (argc < 7) {
        cerr << "Usage: ./gen R C K mode output_file seed\n";
        return 1;
    }

    int R = stoi(argv[1]);
    int C = stoi(argv[2]);
    int K = stoi(argv[3]);
    int mode = stoi(argv[4]);
    string filename = argv[5];
    int seed = stoi(argv[6]);

    rng.seed(seed);

    vector<vector<char>> grid;
    vector<string> keywords;

    if (mode == 1)
        generateNoMatch(R, C, K, grid, keywords);
    else if (mode == 2)
        generateSingleMatch(R, C, K, grid, keywords);
    else if (mode == 3)
        generateMultipleMatch(R, C, K, grid, keywords);
    else {
        cerr << "Invalid mode\n";
        return 1;
    }

    writeToFile(filename, grid, keywords);

    cout << "Generated " << filename << " (mode=" << mode << ", seed=" << seed << ")\n";
}