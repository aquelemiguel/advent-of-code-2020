#include <bits/stdc++.h>
#include "GB.cpp"
using namespace std;

GB p1(vector<Instruction> instructions) {
    GB gameboy;
    set<int> ips;
    gameboy.instructions = instructions;

    while (ips.find(gameboy.ip) == ips.end() && !gameboy.exited) {
        ips.insert(gameboy.ip);
        gameboy.run();
    }

    return gameboy;
}

GB p2(vector<Instruction> instructions) {
    vector<Instruction> copy = instructions;

    for (int i = 0; i < instructions.size(); i++, instructions = copy) {
        switch (instructions[i].opcode) {
            case OpCode::NOP:
                instructions[i].opcode = OpCode::JMP;
                break;
            
            case OpCode::JMP:
                instructions[i].opcode = OpCode::NOP;
                break;

            default:
                break;
        }

        GB gameboy = p1(instructions);
        if (gameboy.exited) return gameboy;
    }
}

int main() {
    vector<Instruction> instructions;

    for (string line; getline(cin, line);) {
        stringstream ss(line);
        vector<string> tokens;
    
        for (string token; getline(ss, token, ' ');)
            tokens.push_back(token);

        Instruction i = Instruction(tokens[0], stoi(tokens[1]));
        instructions.push_back(i);
    }

    cout << p1(instructions).accumulator << endl;
    cout << p2(instructions).accumulator << endl;
}
