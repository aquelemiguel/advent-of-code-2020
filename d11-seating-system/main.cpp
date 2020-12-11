#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<char>> Ferry;

int p1() {

}

int main() {
    Ferry ferry;

    for (string line; getline(cin, line);)
        ferry.push_back(vector<char>(line.begin(), line.end()));

    for (int i = 0; i < ferry.size(); i++) {
        for (int j = 0; j < ferry[i].size(); j++) {
            cout << ferry[i][j] << " ";
        }
        cout << endl;
    }
}