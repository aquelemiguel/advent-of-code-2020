#include <bits/stdc++.h>
using namespace std;

typedef vector<string> Group;

int get_anyone(Group group) {
    auto lambda = [](const string& a, const string &b) { return a+b; };
    string imploded = accumulate(group.begin(), group.end(), string(), lambda);
    return set<char>(imploded.begin(), imploded.end()).size();
}

int get_everyone(Group group) {
    vector<set<char>> sets;

    for (string ans: group)
        sets.push_back(set<char>(ans.begin(), ans.end()));

    set<char> curr, last = sets[0];

    for (size_t i = 1; i < sets.size(); i++) {
        set_intersection(last.begin(), last.end(), sets[i].begin(), sets[i].end(), inserter(curr, curr.begin()));
        swap(last, curr); curr.clear();
    }
    return last.size();
}

int p1(vector<Group> groups) {
    return accumulate(groups.begin(), groups.end(), 0, [=](int sum, Group group) {
        return sum + get_anyone(group);
    });
}

int p2(vector<Group> groups) {
    return accumulate(groups.begin(), groups.end(), 0, [=](int sum, Group group) {
        return sum + get_everyone(group);
    });
}

int main() {
    vector<Group> groups;

    while (!cin.eof()) {
        string line;
        vector<string> group;

        while (getline(cin, line) && !line.empty())
            group.push_back(line);

        groups.push_back(group);
    }

    cout << p1(groups) << endl;
    cout << p2(groups) << endl;
}