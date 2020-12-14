#include <bits/stdc++.h>
#include <regex>
using namespace std;

typedef unsigned long long ull;

ull sum_alloc(map<ull,ull> &mem) {
    ull sum = 0;
    for (auto const& m: mem) sum += m.second;
    return sum;
}

void p2(map<ull,ull> &mem, string mask, int addr, ull value) {
    string res = bitset<36>(addr).to_string();
    vector<int> f;

    for (int i = 0; i < 36; i++) {
        if (mask[i] == 'X') { res[i] = 'X'; f.push_back(i); }
        else if (mask[i] == '1') res[i] = '1';
    }

    for (int i = 0; i < pow(2, f.size()); i++) {
        string perm = bitset<36>(i).to_string().substr(36-f.size(), f.size());
        
        for (int j = 0; j < perm.size(); j++)
            res[f[j]] = perm[j];

        mem[bitset<36>(res).to_ullong()] = value;
    }
}

void p1(map<ull,ull> &mem, string mask, int addr, ull value) {
    string res = bitset<36>(value).to_string();

    for (int i = 0; i < 36; i++)
        if (mask[i] != 'X') res[i] = mask[i];

    mem[addr] = bitset<36>(res).to_ullong();
}

int main() {
    map<ull,ull> mem1, mem2;

    for (string line, mask; getline(cin, line);) {
        smatch match;

        if (regex_match(line, match, regex("mask = (.+)")))
            mask = match[1];

        else if (regex_match(line, match, regex("mem\\[(\\d+)\\] = (.+)"))) {
            p1(mem1, mask, stoi(match[1]), stoi(match[2]));
            p2(mem2, mask, stoi(match[1]), stoi(match[2]));
        }
    }

    printf("p1: %llu\np2: %llu\n", sum_alloc(mem1), sum_alloc(mem2));
}