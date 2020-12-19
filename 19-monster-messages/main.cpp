#include <bits/stdc++.h>
#include <regex>
using namespace std;

bool has_digits(string rule) {
    return any_of(rule.begin(), rule.end(), ::isdigit);
}

ptrdiff_t count_matches(vector<string> &messages, string rule) {
    return count_if(messages.begin(), messages.end(), [&](const string& message) {
        smatch m;
        return regex_match(message, m, regex(rule));
    });
}

string unfold_rule(map<int,string> &rules, int idx) {
    string dup_rule = rules[idx];

    while (has_digits(dup_rule)) {
        smatch m;
        regex_search(dup_rule, m, regex("(\\d+)"));

        size_t pos = dup_rule.find(m[1]);
        dup_rule.replace(pos, m[1].length(), "(" + rules[stoi(m[1])] + ")");
    }

    dup_rule.erase(remove(dup_rule.begin(), dup_rule.end(), '"'), dup_rule.end());
    dup_rule.erase(remove(dup_rule.begin(), dup_rule.end(), ' '), dup_rule.end());

    return dup_rule; 
}

int p2(map<int,string> rules, vector<string> messages) {
    rules[8] = "(42)+";

    string left = "42", right = "31", fullstr = "42 31";

    for (int i = 0; i < 3; i++) {
        left += " 42"; right += " 31";
        fullstr += (" | " + (left + " " + right));
    }
    rules[11] = fullstr;

    rules[0] = unfold_rule(rules, 0);
    return count_matches(messages, rules[0]);
}

int p1(map<int,string> rules, vector<string> messages) {
    rules[0] = unfold_rule(rules, 0);
    return count_matches(messages, rules[0]);
}

int main() {
    vector<string> messages;
    map<int,string> rules;

    for (string line; getline(cin, line);) {
        smatch m;

        if (line.empty())
            continue;

        if (regex_match(line, m, regex("(\\d+): (.+)")))
            rules[stoi(m[1])] = m[2];

        else
            messages.push_back(line);
    }
    
    printf("p1: %d\np2: %d\n", p1(rules, messages), p2(rules, messages));
}