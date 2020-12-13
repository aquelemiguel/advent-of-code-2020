#include <bits/stdc++.h>
using namespace std;

int p1(vector<int> buses, int earliest) {
    int id, wait = INT_MAX;

    for (int bus: buses) {
        int dist = ceil(earliest / double(bus)) * bus - earliest;
        if (dist < wait) { wait = dist; id = bus; }
    }
    return id * wait;
}

int main() {
    int earliest;
    string line;
    cin >> earliest >> line;

    vector<int> buses;

    stringstream ss(line);
    for (string token; getline(ss, token, ',');)
        if (token[0] != 'x') buses.push_back(stoi(token));

    cout << p1(buses, earliest) << endl;
}