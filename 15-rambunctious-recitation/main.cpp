#include <bits/stdc++.h>
using namespace std;

int play(vector<int> &numbers, int target) {
    unordered_map<int, int> m;

    for (int i = 0; i < numbers.size(); i++)
        m[numbers[i]] = i;

    for (int i = numbers.size(), now=0, last;; i++) {
        last = now;
        now = m.find(last) != m.end() ? i - m[now] : 0;
        m[last] = i;

        if (i+1 == target) return last;
    }
}

int main() {
    string line, token;
    getline(cin, line);

    stringstream ss(line);
    vector<int> numbers;

    for (int i = 0; getline(ss, token, ','); i++)
        numbers.push_back(stoi(token));

    printf("p1: %d\np2: %d\n", play(numbers, 2020), play(numbers, 30000000));
}