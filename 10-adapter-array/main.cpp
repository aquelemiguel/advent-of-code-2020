#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

ull p2(vector<int> &adapters) {
    ull dp[10000];

    for (int adapter: adapters) {
        if (adapter == 0) dp[adapter] = 1;
        else if (adapter == 1) dp[adapter] = dp[adapter-1];
        else if (adapter == 2) dp[adapter] += dp[adapter-1] + dp[adapter-2];
        else dp[adapter] = dp[adapter-1] + dp[adapter-2] + dp[adapter-3];
    }
    return dp[adapters[adapters.size() - 1]];
}

int p1(vector<int> &adapters) {
    map<int,int> m;

    for (int i = 1; i < adapters.size(); i++)
        m[adapters[i] - adapters[i-1]]++;

    return m[1] * m[3];
}

int main() {
    vector<int> adapters = {0};
    for (int n; cin >> n;) adapters.push_back(n);

    sort(adapters.begin(), adapters.end());
    adapters.push_back(adapters[adapters.size() - 1] + 3);

    printf("p1: %d\np2: %llu\n", p1(adapters), p2(adapters));
}