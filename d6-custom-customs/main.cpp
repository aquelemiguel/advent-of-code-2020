#include <bits/stdc++.h>
using namespace std;

int get_anyone(string group) {
    group.erase(remove(group.begin(), group.end(), ','), group.end());
    return set<char>(group.begin(), group.end()).size();
}

int get_everyone(string group) {
    vector<set<char>> groups;

    for (size_t pos = group.find(','); pos != string::npos; pos = group.find(',')) {
        string token = group.substr(0, pos);
        groups.push_back(set<char>(token.begin(), token.end()));
        group.erase(0, pos + sizeof(','));
    }

    set<char> last = groups[0], curr;

    for (size_t i = 1; i < groups.size(); i++) {
        set_intersection(last.begin(), last.end(), groups[i].begin(), groups[i].end(), inserter(curr, curr.begin()));
        swap(last, curr);
        curr.clear();
    }
    return last.size();
}

int p1(vector<string> &groups) {
    return accumulate(groups.begin(), groups.end(), 0, [=](int sum, string group) {
        return sum + get_anyone(group);
    });
}

int p2(vector<string> &groups) {
    return accumulate(groups.begin(), groups.end(), 0, [=](int sum, string group) {
        return sum + get_everyone(group);
    });
}

int main() {
    string line;
    stringstream ss;

    vector<string> groups;

    while(getline(cin, line))
        if (line.size() == 0) ss << '\n';
        else ss << line << ',';

    while (getline(ss, line))
        groups.push_back(line);

    cout << p1(groups) << endl;
    cout << p2(groups) << endl;
}