#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

ull modular_multiplicative_inverse(ull a, ull mod) { 
    for (ull i = 1; i < mod; i++)
        if (a % mod * i % mod == 1) return i;
    return 1;
}

ull CRT(vector<int> a, vector<int> n) {
    ull M = accumulate(n.begin(), n.end(), 1ULL, multiplies<ull>()), Y = 0;

    for (int i = 0; i < n.size(); i++) {
        ull p = M / n[i];
        Y += a[i] * modular_multiplicative_inverse(p, n[i]) * p;
    }
    return Y % M;
}

int p1(vector<int> n, int earliest) {
    int id, wait = INT_MAX;

    for (int bus: n) {
        int dist = ceil(earliest / double(bus)) * bus - earliest;
        if (dist < wait) { wait = dist; id = bus; }
    }
    return id * wait;
}

int main() {
    int earliest;
    string line, token;
    cin >> earliest >> line;
    
    vector<int> a, n;
    stringstream ss(line);

    for (int i = 0; getline(ss, token, ','); i++) {
        if (token[0] != 'x') {
            n.push_back(stoi(token));
            a.push_back(stoi(token) - i % stoi(token));
        }
    }
    printf("p1: %d\np2: %llu\n", p1(n, earliest), CRT(a, n));
}