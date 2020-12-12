#include <bits/stdc++.h>
using namespace std;

pair<int,int> sum_of_two(vector<int> &numbers, int start, int range) {
    set<int> m;

    for (int i = start; i < start+range; i++) {
        int sub = numbers[start+range] - numbers[i];
        if (m.find(sub) == m.end()) m.insert(numbers[i]);
        else return {numbers[i], sub};
    }
    return {-1, -1};
}

int p2(vector<int> numbers, int invalid) {
    for (int i = 0, j = 1, s = numbers[i];;) {
        if (s == invalid) {
            vector<int>::iterator start = numbers.begin() + i, end = numbers.begin() + j;
            return *min_element(start, end) + *max_element(start, end);
        }
        s += s < invalid ? numbers[j++] : -numbers[i++];
    }
    return -1;
}

int p1(vector<int> &numbers) {
    for (int i = 25; i < numbers.size(); i++) {
        pair<int,int> res = sum_of_two(numbers, i-25, 25);
        if (res.first == -1) return numbers[i];
    }
    return -1;
}

int main() {
    vector<int> numbers;
    for (int n; cin >> n;) numbers.push_back(n);

    int invalid = p1(numbers);
    printf("p1: %d\np2: %d", invalid, p2(numbers, invalid));
}