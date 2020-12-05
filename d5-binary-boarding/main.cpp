#include <bits/stdc++.h>
using namespace std;

int get_seat_id(string seat) {
    string row = seat.substr(0, 7), col = seat.substr(7, 3);

    replace(row.begin(), row.end(), 'F', '0');
    replace(row.begin(), row.end(), 'B', '1');
    replace(col.begin(), col.end(), 'L', '0');
    replace(col.begin(), col.end(), 'R', '1');

    return stoi(row, nullptr, 2) * 8 + stoi(col, nullptr, 2);
}

int p1(vector<int> seats) {
    return *max_element(seats.begin(), seats.end());
}

int p2(vector<int> seats) {
    sort(seats.begin(), seats.end(), less<int>());
    for (int i = 0; i < seats.size(); i++)
        if (seats[i] == seats[i+1]-2) return seats[i]+1;
}

int main() {
    string seat;
    vector<int> seats;

    while (getline(cin, seat))
        seats.push_back(get_seat_id(seat));

    cout << p1(seats) << endl;
    cout << p2(seats) << endl;
}