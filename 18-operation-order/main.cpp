#include <bits/stdc++.h>
#include <regex>
using namespace std;

typedef unsigned long long ull;

ull shunting_yard_v2(vector<char> tokens) {
    queue<char> q;
    stack<char> s;

    size_t i = 0;

    while (i < tokens.size()) {
        // cout << tokens[i] << endl;
        
        if (isdigit(tokens[i])) {
            // cout << "pushed to queue: " << tokens[i] << endl;
            q.push(tokens[i]);
        }

        else if (tokens[i] == '(' || tokens[i] == '+') {
            // cout << "pushed to stack: " << tokens[i] << endl;
            s.push(tokens[i]);
        }

        else if (tokens[i] == '*') {
            // cout << "pushed to stack: " << tokens[i] << endl;

            while (!s.empty() && s.top() == '+') {
                q.push(s.top());
                s.pop();
            }

            s.push(tokens[i]);
        }

        else if (tokens[i] == ')') {
            while (s.top() != '(') {
                // cout << "pushed to queue: " << tokens[i] << endl;
                q.push(s.top());
                s.pop();
            }
            s.pop();
        }
        i++;
    }

    while (!s.empty()) {
        q.push(s.top());
        s.pop();
    }

    
    // while (!q.empty()) {
    //     cout << q.front() << " ";
    //     q.pop();
    // }
    // cout << endl;

    stack<ull> res;

    while (!q.empty()) {
        // cout << q.front() << endl;

        if (isdigit(q.front())) {
            res.push(q.front() - '0');
            // cout << "converted: " << q.front() - '0' << endl;
        } 
        else {
            ull a = res.top();
            res.pop();
            ull b = res.top();
            res.pop();
            
            if (q.front() == '+') {
                res.push(a + b);
                // cout << "pushed to res: " << a << "+" << b << "=" << a+b << endl;
            }
            else {
                res.push(a * b);
                // cout << "pushed to res: " << a << "*" << b << "=" << a*b << endl;
            }
        }
        q.pop();
    }

    return res.top();
}

ull shunting_yard_v1(vector<char> tokens) {
    queue<char> q;
    stack<char> s;

    size_t i = 0;

    while (i < tokens.size()) {
        // cout << tokens[i] << endl;
        
        if (isdigit(tokens[i])) {
            // cout << "pushed to queue: " << tokens[i] << endl;
            q.push(tokens[i]);
        }

        else if (tokens[i] == '(') {
            // cout << "pushed to stack: " << tokens[i] << endl;
            s.push(tokens[i]);
        }

        else if (tokens[i] == '+' || tokens[i] == '*') {
            // cout << "pushed to stack: " << tokens[i] << endl;

            while (!s.empty() && (s.top() == '+' || s.top() == '*')) {
                q.push(s.top());
                s.pop();
            }

            s.push(tokens[i]);
        }

        else if (tokens[i] == ')') {
            while (s.top() != '(') {
                // cout << "pushed to queue: " << tokens[i] << endl;
                q.push(s.top());
                s.pop();
            }
            s.pop();
        }
        i++;
    }

    while (!s.empty()) {
        q.push(s.top());
        s.pop();
    }

    
    // while (!q.empty()) {
    //     cout << q.front() << " ";
    //     q.pop();
    // }
    // cout << endl;

    stack<ull> res;

    while (!q.empty()) {
        // cout << q.front() << endl;

        if (isdigit(q.front())) {
            res.push(q.front() - '0');
            // cout << "converted: " << q.front() - '0' << endl;
        } 
        else {
            ull a = res.top();
            res.pop();
            ull b = res.top();
            res.pop();
            
            if (q.front() == '+') {
                res.push(a + b);
                // cout << "pushed to res: " << a << "+" << b << "=" << a+b << endl;
            }
            else {
                res.push(a * b);
                // cout << "pushed to res: " << a << "*" << b << "=" << a*b << endl;
            }
        }
        q.pop();
    }

    return res.top();
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