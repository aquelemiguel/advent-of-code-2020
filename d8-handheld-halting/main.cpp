#include <bits/stdc++.h>
using namespace std;

typedef pair<string,int> Instr;

struct Program {
    int acc = 0;
    
    bool run(vector<Instr> instrs) {
        set<int> idx;

        for (int i = 0; i < instrs.size(); i++) {
            if (idx.find(i) != idx.end())
                return false;

            idx.insert(i);

            if (instrs[i].first == "acc")
                acc += instrs[i].second;

            if (instrs[i].first == "jmp")
                i += instrs[i].second - 1;
        }
        return true;
    }
};

int p2(vector<Instr> instrs) {
    vector<Instr> copy = instrs;

    for (int i = 0; i < instrs.size(); i++) {
        Program p;

        if (instrs[i].first == "nop") {
            instrs[i].first = "jmp";
            if (p.run(instrs)) return p.acc;
        }
        
        else if (instrs[i].first == "jmp") {
            instrs[i].first = "nop";
            if (p.run(instrs)) return p.acc;
        }
        instrs = copy;
    }
    return -1;
}

int p1(vector<Instr> instrs) {
    Program p;
    p.run(instrs);
    return p.acc;
}

int main() {
    vector<Instr> instrs;

    for (string line; getline(cin, line);) {
        stringstream ss(line);
        vector<string> tokens;
    
        for (string token; getline(ss, token, ' ');)
            tokens.push_back(token);

        instrs.push_back({tokens[0], stoi(tokens[1])});
    }

    cout << p1(instrs) << endl;
    cout << p2(instrs) << endl;
}