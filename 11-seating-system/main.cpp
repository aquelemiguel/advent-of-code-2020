#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<char>> Ferry;

Ferry initial_ferry;
vector<pair<int,int>> adjacency = {
    {-1, 0}, {-1, 1}, {0, 1}, {1, 1},
    {1, 0}, {1, -1}, {0, -1}, {-1, -1}
};

int count_occupied(Ferry &ferry) {
    int count = 0;
    for (auto row: ferry) for (char c: row) if (c == '#') count++;
    return count;
}

bool is_valid(int i, int j) {
    return i >= 0 && j >= 0 && i < initial_ferry.size() && j < initial_ferry[i].size();
}

pair<int,int> get_immediate(int i, int j, pair<int,int> k) {
    return {i + k.first, j + k.second};
}

pair<int,int> get_visible(int i, int j, pair<int,int> k) {
    do { i += k.first, j += k.second; } 
    while (is_valid(i, j) && initial_ferry[i][j] == '.');
    return {i, j};
}

int run(pair<int,int> strategy(int i, int j, pair<int,int> k), int rule) {
    Ferry ferry = initial_ferry;
    bool has_changed = false;

    do {
        Ferry temp_ferry = ferry;
        has_changed = false;

        for (int i = 0; i < ferry.size(); i++) {
            for (int j = 0; j < ferry[i].size(); j++) {

                int adjs = count_if(adjacency.begin(), adjacency.end(), [=](const pair<int,int> k) {
                    pair<int,int> adj = strategy(i, j, k);
                    return is_valid(adj.first, adj.second) && ferry[adj.first][adj.second] == '#';
                });

                if (ferry[i][j] == 'L' && adjs == 0) {
                    temp_ferry[i][j] = '#';
                    has_changed = true;
                }

                else if (ferry[i][j] == '#' && adjs >= rule) {
                    temp_ferry[i][j] = 'L';
                    has_changed = true;
                }
            }
        }
        ferry = temp_ferry;
    } while (has_changed);

    return count_occupied(ferry);
}

int main() {
    for (string line; getline(cin, line);)
        initial_ferry.push_back(vector<char>(line.begin(), line.end()));

    printf("p1: %d\np2: %d\n", run(get_immediate, 4), run(get_visible, 5));
}