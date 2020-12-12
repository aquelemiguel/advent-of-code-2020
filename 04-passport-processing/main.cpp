#include <bits/stdc++.h>
#include <regex>
using namespace std;

int p1(vector<string> &passports) {
    vector<string> keys = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

    return count_if(passports.begin(), passports.end(), [=](string passport) {
        return count_if(keys.begin(), keys.end(), [=](string key) {
            return passport.find(key) != string::npos;
        }) == 7;
    });
}

int p2(vector<string> &passports) {
    vector<string> exprs = {
        "byr:(19[2-9]\\d|200[0-2])",
        "iyr:(20(1\\d|20))",
        "eyr:(20(2\\d|30))",
        "hgt:(1[5-8]\\dcm|19[0-3]cm|59in|6\\din|7[0-6]in)",
        "hcl:#([a-f\\d]{6})",
        "ecl:(amb|blu|brn|gry|grn|hzl|oth)",
        "pid:(\\d{9})(?:\\n|\\s|$)"
    };
    
    return count_if(passports.begin(), passports.end(), [=](string passport) {
        return count_if(exprs.begin(), exprs.end(), [=](string expr) {
            return regex_search(passport, regex(expr));
        }) == exprs.size();
    });
}

int main() {
    string line;
    vector<string> lines;
    vector<string> passports;

    stringstream ss;

    while (getline(cin, line))
        if (line.size() == 0) ss << '\n';
        else ss << ' ' << line;

    while (getline(ss, line))
        passports.push_back(line);

    cout << p1(passports) << endl;
    cout << p2(passports) << endl;
}
