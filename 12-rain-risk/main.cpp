#include <bits/stdc++.h>
using namespace std;

typedef pair<char,int> Action;
const long double PI = acos(-1.L);

struct Ship {
    int x = 0, y = 0, dir = 1;
    pair<int,int> waypoint = {10, 1};
    
    map<int, pair<int,int>> d {
        {0, {0, 1}}, {1, {1, 0}}, {2, {0, -1}}, {3, {-1, 0}}
    };

    void rotate_ship(int angle) {
        dir = (dir + angle / 90 + 4) % 4;
    }

    void rotate_waypoint(float angle) {
        float s = sin(angle * PI / 180.0), c = cos(angle * PI / 180.0);
        int new_x = waypoint.first * c - waypoint.second * s;
        int new_y = waypoint.first * s + waypoint.second * c;
        waypoint.first = new_x;
        waypoint.second = new_y;
    }
};

int p2(Ship &ship, vector<Action> &actions) {
    for (Action action: actions) {
        if (action.first == 'N')
            ship.waypoint.second += action.second;

        if (action.first == 'S')
            ship.waypoint.second -= action.second;

        if (action.first == 'E')
            ship.waypoint.first += action.second;

        if (action.first == 'W')
            ship.waypoint.first -= action.second;

        if (action.first == 'L') {
            ship.rotate_waypoint(action.second);
        }

        if (action.first == 'R') {
            ship.rotate_waypoint(-action.second);
        }

        if (action.first == 'F') {
            ship.x += (ship.waypoint.first * action.second);
            ship.y += (ship.waypoint.second * action.second);
        }
    }
    return abs(ship.x) + abs(ship.y);
}

int p1(Ship &ship, vector<Action> &actions) {
    for (Action action: actions) {
        if (action.first == 'N')
            ship.y += action.second;

        if (action.first == 'S')
            ship.y -= action.second;

        if (action.first == 'E')
            ship.x += action.second;

        if (action.first == 'W')
            ship.x -= action.second;

        if (action.first == 'L')
            ship.rotate_ship(-action.second);

        if (action.first == 'R')
            ship.rotate_ship(action.second);

        if (action.first == 'F') {
            ship.x += (ship.d[ship.dir].first * action.second);
            ship.y += (ship.d[ship.dir].second * action.second);
        }
    }
    return abs(ship.x) + abs(ship.y);
}

int main() {
    vector<Action> actions;
    Ship s1, s2;

    for (string line; getline(cin, line);) {
        actions.push_back({line[0], stoi(line.substr(1, line.length()-1))});
    }

    printf("p1: %d\np2: %d\n", p1(s1, actions), p2(s2, actions));
}