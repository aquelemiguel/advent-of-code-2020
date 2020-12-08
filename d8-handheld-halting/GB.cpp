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

    Instruction(string opcode, int value) {
        this->opcode = opcode_table[opcode];
        this->value = value; 
    }
};

struct GB {
    int accumulator = 0, ip = 0;
    vector<Instruction> instructions;
    bool exited = false;

    GB(vector<Instruction> instructions) {
        this->instructions = instructions;
    }

    void step() {
        Instruction inst = this->instructions[this->ip];

        switch (inst.opcode) {
            case OpCode::ACC:
                this->accumulator += inst.value;
                break;

            case OpCode::JMP:
                this->ip += inst.value - 1;
                break;
        
            default:
                break;
        }

        if (++ip >= instructions.size())
            this->exited = true;
    }
};
