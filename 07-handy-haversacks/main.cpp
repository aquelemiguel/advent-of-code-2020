#include <bits/stdc++.h>
#include <regex>
using namespace std;

typedef map<string, map<string, int>> BagMap;
BagMap bags;

bool find_bag(string key, string target) {
    if (bags[key].find(target) != bags[key].end())
        return true;

    for (auto child : bags[key]) {
        bool found = find_bag(child.first, target);
        if (found) return true;
    }

    return false;
}

int count_bags(string key) {
    int count = 0;
    if (bags[key].size() == 0) return 0;

    for (auto child : bags[key])
        count += (child.second + child.second * count_bags(child.first));

    return count;
}

int p2(string target) {
    return count_bags(target);
}

int p1(string target) {
    return count_if(bags.begin(), bags.end(), [=](auto const& bag) {
        return find_bag(bag.first, target);
    });
}

int main() {
    string line;

    while (getline(cin, line)) {
        line = regex_replace(line, regex(" bags contain "), ";");
        stringstream ss(line);

        vector<string> big;
        for (string token; getline(ss, token, ';');)
            big.push_back(token);

        string temp = regex_replace(big[1], regex(", "), ";");
        stringstream sst(temp);

        for (string token; getline(sst, token, ';');) {
            smatch match;
            if (regex_search(token, match, regex("(\\d+) (.+) bags?.?")))
                bags[big[0]][match[2]] = stoi(match[1]);
        }
    }

    cout << p1("shiny gold") << endl;
    cout << p2("shiny gold") << endl;
}
