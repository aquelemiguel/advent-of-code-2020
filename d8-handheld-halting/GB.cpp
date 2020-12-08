#include <bits/stdc++.h>
using namespace std;

enum OpCode {ACC, JMP, NOP};

static map<string, OpCode> opcode_table = {
    { "acc", OpCode::ACC },
    { "jmp", OpCode::JMP },
    { "nop", OpCode::NOP }
};

struct Instruction {
    OpCode opcode;
    int value;

    Instruction(string name, int value) {
        this->opcode = opcode_table[name];
        this->value = value; 
    }
};

struct GB {
    int accumulator = 0, ip = 0;
    vector<Instruction> instructions;
    bool exited = false;

    void run() {
        Instruction inst = this->instructions[this->ip];

        if (inst.opcode == OpCode::ACC) 
            this->accumulator += inst.value;

        if (inst.opcode == OpCode::JMP)
            this->ip += inst.value - 1;

        if (++ip >= instructions.size())
            this->exited = true;
    }
};
