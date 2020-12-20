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

ull shunting_yard_v2(vector<char> tokens) {
    queue<char> q;
    stack<char> s;

    for (size_t i = 0; i < tokens.size(); i++) {
        if (isdigit(tokens[i]))
            q.push(tokens[i]);

        else if (tokens[i] == '(' || tokens[i] == '+')
            s.push(tokens[i]);

        else if (tokens[i] == '*') {
            while (!s.empty() && s.top() == '+') {
                q.push(s.top()); s.pop();
            }
            s.push(tokens[i]);
        }

        else if (tokens[i] == ')') {
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

ull shunting_yard_v1(vector<char> tokens) {
    queue<char> q;
    stack<char> s;

    for (size_t i = 0; i < tokens.size(); i++) {
        if (isdigit(tokens[i]))
            q.push(tokens[i]);

        else if (tokens[i] == '(')
            s.push(tokens[i]);

        else if (tokens[i] == '+' || tokens[i] == '*') {
            while (!s.empty() && (s.top() == '+' || s.top() == '*')) {
                q.push(s.top()); s.pop();
            }
            s.push(tokens[i]);
        }

        else if (tokens[i] == ')') {
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
    vector<vector<char>> exprs;

    ull p1 = 0, p2 = 0;
    
    for (string s; getline(cin, s);) {
        s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
        p1 += shunting_yard_v1(vector<char>(s.begin(), s.end()));
        p2 += shunting_yard_v2(vector<char>(s.begin(), s.end()));
    }

    printf("p1: %llu\np2: %llu\n", p1, p2);
}