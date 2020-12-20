#include <bits/stdc++.h>
#include <regex>
using namespace std;

typedef unsigned long long ull;

ull calc_RPN(queue<char> q) {
    stack<ull> res;

    while (!q.empty()) {
        if (isdigit(q.front())) res.push(q.front() - '0');
        else {
            ull a = res.top(); res.pop();
            ull b = res.top(); res.pop();
            res.push(q.front() == '+' ? a+b : a*b);
        }
        q.pop();
    }
    return res.top();
}

ull shunting_yard(vector<char> tokens, bool equal_op) {
    queue<char> q;
    stack<char> s;

    for (char token : tokens) {
        if (isdigit(token))
            q.push(token);

        else if (token == '(' || (!equal_op && token == '+'))
            s.push(token);

        else if (token == '*' || (equal_op && token == '+')) {
            while (!s.empty() && (s.top() == '+' || (equal_op && s.top() == '*'))) {
                q.push(s.top()); s.pop();
            }
            s.push(token);
        }

        else if (token == ')') {
            while (s.top() != '(') {
                q.push(s.top()); s.pop();
            }
            s.pop();
        }
    }

    while (!s.empty()) {
        q.push(s.top()); s.pop();
    }
    return calc_RPN(q);
}

int main() {
    ull p1 = 0, p2 = 0;
    
    for (string s; getline(cin, s);) {
        s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
        vector<char> exprs(s.begin(), s.end());

        p1 += shunting_yard(exprs, true);
        p2 += shunting_yard(exprs, false);
    }
    printf("p1: %llu\np2: %llu\n", p1, p2);
}