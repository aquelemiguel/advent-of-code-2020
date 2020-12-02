#include <bits/stdc++.h>
using namespace std;

struct Policy {
    int lower, upper;
    char letter;
    char password[32];
};

int part_one(vector<Policy> policies) {
    return count_if(policies.begin(), policies.end(), [=](const Policy &p) {
        vector<char> filter;

        copy_if(p.password, p.password + strlen(p.password), back_inserter(filter), [p](const char &c) {
            return c == p.letter; 
        });

        return filter.size() >= p.lower && filter.size() <= p.upper;
    });
}

int part_two(vector<Policy> policies) {
    return count_if(policies.begin(), policies.end(), [=](const Policy &p) {
        return p.password[p.lower-1] == p.letter ^ p.password[p.upper-1] == p.letter;
    });
}

int main() {
    vector<Policy> policies;
    Policy p;

    while (scanf("%d-%d %c: %s\n", &p.lower, &p.upper, &p.letter, &p.password) > 0)
        policies.push_back(p);

    cout << part_one(policies) << endl << part_two(policies) << endl;
}