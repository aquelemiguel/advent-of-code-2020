#include <bits/stdc++.h>
#include <regex>
using namespace std;

typedef map<string, map<string, int>> BagMap;

bool find_bag(BagMap bags, string key, string target) {
    if (bags[key].find(target) != bags[key].end())
        return true;

    for (auto const& child : bags[key]) {
        bool found = find_bag(bags, child.first, target);
        if (found) return true;
    }

    return false;
}

int count_bags(BagMap bags, string key) {
    int count = 0;
    if (bags[key].size() == 0) return 0;

    for (auto const& child : bags[key])
        count += (child.second + child.second * count_bags(bags, child.first));

    return count;
}

int p2(BagMap bags, string target) {
    return count_bags(bags, target);
}

int p1(BagMap bags, string target) {
    return count_if(bags.begin(), bags.end(), [=](auto const& bag) {
        return find_bag(bags, bag.first, target);
    });
}

int main() {
    string line;
    BagMap bags;

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

    cout << p1(bags, "shiny gold") << endl;
    cout << p2(bags, "shiny gold") << endl;
}
