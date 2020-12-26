#include <bits/stdc++.h>
#include <regex>
using namespace std;

typedef pair<int,int> Tile;

map<string, Tile> hex_grid {
    {"ne", {0, 1}}, {"e", {1, 0}}, {"se", {1, -1}},
    {"nw", {-1, 1}}, {"w", {-1, 0}}, {"sw", {0, -1}}
};

int count_adjacent_black(set<Tile> &black, Tile tile) {
    return count_if(hex_grid.begin(), hex_grid.end(), [&](const auto& h) {
        return black.find({h.second.first + tile.first, h.second.second + tile.second}) != black.end();
    });
}

int p2(set<Tile> &black) {
    set<Tile> dupe = black;

    for (int i = 1; i <= 100; i++) {
        for (Tile tile : black)
            if (count_adjacent_black(black, tile) != 1) 
                dupe.erase(tile);

        for (int i = -75; i < 75; i++)
            for (int j = -75; j < 75; j++)
                if (count_adjacent_black(black, {i, j}) == 2) 
                    dupe.insert({i, j});

        black = dupe;
    }
    return black.size();
}

void flip_tile(set<Tile> &black, vector<string> dirs) {
    int x = 0, y = 0;
    
    for (string dir : dirs) {
        x += hex_grid[dir].first;
        y += hex_grid[dir].second;
    }

    if (black.find({x, y}) != black.end()) black.erase({x, y});
    else black.insert({x, y});
}

int main() {
    set<Tile> black;
    regex re("(e|se|sw|w|nw|ne)");

    for (string line; getline(cin, line);) {
        vector<string> dirs;

        for (smatch m; regex_search(line, m, re); line = m.suffix().str())
            for (int i = 1; i < m.size(); i++)
                dirs.push_back(m[i]);

        flip_tile(black, dirs);
    }

    cout << "p1: " << black.size() << endl;
    cout << "p2: " << p2(black) << endl;
}