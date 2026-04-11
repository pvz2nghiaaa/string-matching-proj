#include <bits/stdc++.h>
using namespace std;

// ===== RANDOM ENGINE =====
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int randInt(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

char randChar() {
    return 'a' + randInt(0, 25);
}

string randString(int len) {
    string s;
    for (int i = 0; i < len; i++)
        s += randChar();
    return s;
}

// ================= CHECK + PLACE =================
bool canPlaceHorizontal(vector<vector<char>>& grid, int row, int col, const string& s) {
    for (int j = 0; j < s.size(); j++) {
        if (grid[row][col + j] != '#' && grid[row][col + j] != s[j])
            return false;
    }
    return true;
}

bool canPlaceVertical(vector<vector<char>>& grid, int row, int col, const string& s) {
    for (int j = 0; j < s.size(); j++) {
        if (grid[row + j][col] != '#' && grid[row + j][col] != s[j])
            return false;
    }
    return true;
}

void placeHorizontal(vector<vector<char>>& grid, int row, int col, const string& s) {
    for (int j = 0; j < s.size(); j++)
        grid[row][col + j] = s[j];
}

void placeVertical(vector<vector<char>>& grid, int row, int col, const string& s) {
    for (int j = 0; j < s.size(); j++)
        grid[row + j][col] = s[j];
}

// ================= RANDOM DATA =================
void generateRandomData(int R, int C, int K,
                        vector<vector<char>>& grid,
                        vector<string>& keywords) {

    // grid trống
    grid.assign(R, vector<char>(C, '#'));
    keywords.clear();

    for (int i = 0; i < K; i++) {
        int len = randInt(3, min(10, max(R, C)));
        string s = randString(len);

        int type = randInt(1, 3); // 1: NoMatch, 2: Single, 3: Multiple

        if (type == 1) {
            // ❌ NoMatch
            s = string(len, 'z');
        }
        else {
            int times = (type == 2) ? 1 : randInt(2, 5);

            for (int t = 0; t < times; t++) {
                int attempts = 50;

                while (attempts--) {
                    bool horizontal = (len <= C) ? randInt(0, 1) : false;

                    if (horizontal) {
                        int row = randInt(0, R - 1);
                        int col = randInt(0, C - len);

                        if (canPlaceHorizontal(grid, row, col, s)) {
                            placeHorizontal(grid, row, col, s);
                            break;
                        }
                    } else if (len <= R) {
                        int col = randInt(0, C - 1);
                        int row = randInt(0, R - len);

                        if (canPlaceVertical(grid, row, col, s)) {
                            placeVertical(grid, row, col, s);
                            break;
                        }
                    }
                }
            }
        }

        keywords.push_back(s);
    }

    // fill ô trống
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            if (grid[i][j] == '#')
                grid[i][j] = randChar();
}

// ================= REPETITIVE DATA =================
void generateRepetitiveData(int R, int C, int K,
                            vector<vector<char>>& grid,
                            vector<string>& keywords) {

    grid.assign(R, vector<char>(C, '#'));
    keywords.clear();

    for (int i = 0; i < K; i++) {
        int len = randInt(5, 12);

        string s;
        if (randInt(0, 1))
            s = string(len - 1, 'a') + 'b'; // nearly match
        else
            s = string(len, 'a');           // full match

        keywords.push_back(s);

        int times = randInt(1, 4);

        for (int t = 0; t < times; t++) {
            int attempts = 50;

            while (attempts--) {
                bool horizontal = (len <= C) ? randInt(0, 1) : false;

                if (horizontal) {
                    int row = randInt(0, R - 1);
                    int col = randInt(0, C - len);

                    if (canPlaceHorizontal(grid, row, col, s)) {
                        placeHorizontal(grid, row, col, s);
                        break;
                    }
                } else if (len <= R) {
                    int col = randInt(0, C - 1);
                    int row = randInt(0, R - len);

                    if (canPlaceVertical(grid, row, col, s)) {
                        placeVertical(grid, row, col, s);
                        break;
                    }
                }
            }
        }
    }

    // fill phần còn lại bằng 'a'
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            if (grid[i][j] == '#')
                grid[i][j] = 'a';
}

// ================= WRITE FILE =================
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
            if (j < C - 1) out << " ";
        }
        out << "\n";
    }

    out << keywords.size() << "\n";
    for (auto& s : keywords)
        out << s << "\n";
}

// ================= MAIN =================
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
        generateRandomData(R, C, K, grid, keywords);
    else if (mode == 2)
        generateRepetitiveData(R, C, K, grid, keywords);
    else {
        cerr << "Invalid mode\n";
        return 1;
    }

    writeToFile(filename, grid, keywords);

    cout << "Generated " << filename
         << " (mode=" << mode
         << ", seed=" << seed << ")\n";
}