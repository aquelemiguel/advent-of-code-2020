#include <bits/stdc++.h>
#include <regex>
using namespace std;

typedef unsigned long long ull;

struct Rule {
    string name;
    pair<int,int> r1, r2;

    Rule(string name, pair<int,int> r1, pair<int,int> r2) {
        this->name = name;
        this->r1 = r1;
        this->r2 = r2;
    }
};

struct Ticket {
    vector<int> fields;

    Ticket(vector<int> fields) {
        this->fields = fields;
    }
};

bool is_in_range(Rule &r, int n) {
    return (n >= r.r1.first && n <= r.r1.second) || (n >= r.r2.first && n <= r.r2.second);
}

ull p2(vector<Rule> &rules, vector<Ticket> &tickets) {
    ull mul = 1;
    vector<pair<int, set<string>>> vec;

    for (int i = 0; i < rules.size(); i++) {
        vector<int> fields;
        vec.push_back({tickets[0].fields[i], set<string>()});
         
        for (int j = 1; j < tickets.size(); j++)
            fields.push_back(tickets[j].fields[i]);

        for (int j = 0; j < rules.size(); j++) {
            auto l = [&](const int &field) { return is_in_range(rules[j], field); };
            
            if (count_if(fields.begin(), fields.end(), l) == tickets.size() - 1)
                vec[i].second.insert(rules[j].name);
        }
    }

    sort(vec.begin(), vec.end(), [=](const pair<int, set<string>> &a, const pair<int, set<string>> &b) {
        return a.second.size() < b.second.size();
    });

    map<string,int> assigns {{*vec[0].second.begin(), vec[0].first}};

    for (int i = 1; i < vec.size(); i++) {
        vector<string> s;
        set_difference(vec[i].second.begin(), vec[i].second.end(), vec[i-1].second.begin(), vec[i-1].second.end(), inserter(s, s.begin()));
        assigns[s[0]] = vec[i].first;
    }

    for (auto a : assigns)
        if (a.first.find("departure") != string::npos)
            mul *= a.second;

    return mul;
}

int p1(vector<Rule> &rules, vector<Ticket> &tickets) {
    int sum = 0;

    for (int i = 1; i < tickets.size(); i++) {
        for (int field: tickets[i].fields) {
            auto lambda = [&](Rule &rule) { return is_in_range(rule, field); };
            if (!count_if(rules.begin(), rules.end(), lambda)) {
                sum += field;
                tickets.erase(tickets.begin() + i--);
            }
        }
    }
    return sum;
}

int main() {
    vector<Rule> rules;
    vector<Ticket> tickets;

    for (string line; getline(cin, line);) {
        smatch m;

        if (regex_match(line, m, regex("(.+): (\\d+)-(\\d+) or (\\d+)-(\\d+)"))) {
            Rule r(m[1], {stoi(m[2]), stoi(m[3])}, {stoi(m[4]), stoi(m[5])});
            rules.push_back(r);
        }

        else if (line.length() && !regex_match(line, m, regex("your ticket:|nearby tickets:"))) {
            stringstream ss(line);
            vector<int> fields;

            for (string token; getline(ss, token, ',');)
                fields.push_back(stoi(token));

            tickets.push_back(Ticket(fields));
        }
    }

    cout << "p1: " << p1(rules, tickets) << endl;
    cout << "p2: " << p2(rules, tickets) << endl;
}