#include <bits/stdc++.h>
#include <regex>
using namespace std;

set<string> intersect(set<string> s1, set<string> s2) {
    set<string> res;
    set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(res, res.begin()));
    return res;
}

string p2(map<string, set<string>> &allergens) {
    string res = "";
    for (auto const& a : allergens) res += *a.second.begin() + ",";
    return res.substr(0, res.size() - 1);
}

int p1(vector<set<string>> foods, set<string> allergens) {
    return accumulate(foods.begin(), foods.end(), 0, [&](int sum, const auto &food) {
        set<string> safe;
        set_difference(food.begin(), food.end(), allergens.begin(), allergens.end(),
            inserter(safe, safe.begin()));
        return sum + safe.size();
    });
}

void calculate_allergens(map<string, set<string>> &allergens) {
    auto lambda = [](const auto &ingredients) { return ingredients.second.size() != 1; };
    
    while (any_of(allergens.begin(), allergens.end(), lambda))
        for (auto const& a1 : allergens)
            if (a1.second.size() == 1)
                for (auto const& a2 : allergens) {
                    if (a1.first == a2.first) continue;
                    allergens[a2.first].erase(*allergens[a1.first].begin());
                }
}

int main() {
    vector<set<string>> foods; 
    map<string, set<string>> allergens;
    
    for (string line, res; getline(cin, line);) {
        smatch m;
        if (regex_match(line, m, regex("(.+) \\(contains (.+)\\)"))) {
            stringstream ss(m[1]);
            set<string> ings, alls;

            for (string token; getline(ss, token, ' ');)
                ings.insert(token);
            foods.push_back(ings);

            res = regex_replace(string(m[2]), regex(",\\s"), " ");
            stringstream sst(res);

            for (string token; getline(sst, token, ' ');) {
                if (allergens.find(token) != allergens.end())
                    allergens[token] = intersect(allergens[token], ings);
                else
                    allergens[token].insert(ings.begin(), ings.end());
            }
        }
    }

    calculate_allergens(allergens);
    set<string> values;
    for (auto const& a : allergens) values.insert(*a.second.begin());
   
    cout << p1(foods, values) << endl;
    cout << p2(allergens) << endl;
}