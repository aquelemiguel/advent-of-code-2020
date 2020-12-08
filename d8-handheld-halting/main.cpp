#include <bits/stdc++.h>
using namespace std;

enum OPCODE {ACC, JMP, NOP};

static map<string, OPCODE> opcode_table = {
    { "acc", OPCODE::ACC },
    { "jmp", OPCODE::JMP },
    { "nop", OPCODE::NOP }
};

struct INSTR {
    OPCODE opcode;
    int value;
    
    INSTR(string name, int value) {
        this->opcode = opcode_table[name];
        this->value = value;
    }
};

struct Program {
    int acc = 0;
    
    bool run(vector<INSTR> instrs) {
        set<int> idx;

        for (int i = 0; i < instrs.size(); i++) {
            if (idx.find(i) != idx.end())
                return false;

            idx.insert(i);

            switch (instrs[i].opcode) {
                case OPCODE::ACC:
                    acc += instrs[i].value;
                    break;

                case OPCODE::JMP:
                    i += instrs[i].value - 1;
                    break;
                
                default:
                    break;
            }  
        }
        return true;
    }
};

int p2(vector<INSTR> instrs) {
    vector<INSTR> copy = instrs;

    for (int i = 0; i < instrs.size(); i++) {
        Program p;

        switch (instrs[i].opcode) {
            case OPCODE::NOP:
                instrs[i].opcode = OPCODE::JMP;
                if (p.run(instrs)) return p.acc;
                break;

            case OPCODE::JMP:
                instrs[i].opcode = OPCODE::NOP;
                if (p.run(instrs)) return p.acc;
                break;
            
            default:
                break;
        }
        instrs = copy;
    }
    return INT_MAX;
}

int p1(vector<INSTR> instrs) {
    Program p;
    p.run(instrs);
    return p.acc;
}

int main() {
    vector<INSTR> instrs;

    for (string line; getline(cin, line);) {
        stringstream ss(line);
        vector<string> tokens;
    
        for (string token; getline(ss, token, ' ');)
            tokens.push_back(token);

        instrs.push_back(INSTR(tokens[0], stoi(tokens[1])));
    }

    cout << p1(instrs) << endl;
    cout << p2(instrs) << endl;
}