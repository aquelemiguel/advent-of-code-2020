#include <bits/stdc++.h>
using namespace std;

int traverse(vector<vector<char>> &forest, int x, int y) {
    int count = 0;

    for (int i = 0, j = 0; i < forest.size(); i+=y, j+=x) {
        if (j >= forest[i].size()) j -= forest[i].size();
        if (forest[i][j] == '#') count++;
    }

    return count;
}

int part_1(vector<vector<char>> &forest) {
    return traverse(forest, 3, 1);
}

long long part_2(vector<vector<char>> &forest) {
    vector<int> traversals;
    vector<pair<int,int>> steps = {{1,1}, {3,1}, {5,1}, {7,1}, {1,2}};

    auto lambda = [&forest](pair<int,int> p) { return traverse(forest, p.first, p.second); };
    transform(steps.begin(), steps.end(), back_inserter(traversals), lambda);

    return accumulate(traversals.begin(), traversals.end(), 1LL, multiplies<long long>());
}

int main() {
    string line;
    vector<vector<char>> forest;

    while (getline(cin, line)) {
        vector<char> v(line.begin(), line.end());
        forest.push_back(v);
    }

    cout << part_1(forest) << endl;
    cout << part_2(forest) << endl;
}
