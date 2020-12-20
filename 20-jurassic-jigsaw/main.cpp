#include <bits/stdc++.h>
#include <regex>
using namespace std;

int main() {
    map<int,vector<vector<char>>> tiles;

    for (string header; getline(cin, header);) {
        smatch m;
        regex_search(header, m, regex("(\\d+)"));
        
        for (string row; getline(cin, row);) {
            if (row.length() == 0) break;
            tiles[stoi(m[1])].push_back(vector<char>(row.begin(), row.end()));
        }
    }
}