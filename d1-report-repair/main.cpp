#include <bits/stdc++.h>
using namespace std;

vector<int> file_to_int_vector(string path) {
    int n;
    vector<int> arr;
    ifstream infile(path);

    while (infile >> n) arr.push_back(n);
    return arr;
}

pair<int,int> part_one(vector<int> &puzzle, int target) {
    set<int> s1;

    for (int elem : puzzle) {
        int diff = target - elem;

        if (s1.find(diff) == s1.end()) s1.insert(elem);
        else return make_pair(elem, diff);
    }
}

tuple<int,int,int> part_two(vector<int> &puzzle, int target) {
    for (int elem : puzzle) {
        pair<int,int> pair = part_one(puzzle, target - elem);
        if (pair.first + pair.second + elem == target)
            return make_tuple(pair.first, pair.second, elem);
    }
}

int main() {
    vector<int> puzzle = file_to_int_vector("input.txt");
    
    pair<int,int> p1 = part_one(puzzle, 2020);
    cout << p1.first * p1.second << endl;

    tuple<int,int,int> p2 = part_two(puzzle, 2020);
    cout << get<0>(p2) * get<1>(p2) * get<2>(p2) << endl;
}
