//
// Created by maksim.shekhanin on 11/19/2023.
//

#include <sstream>
#include "XASM.h"
#include "string"
#include <algorithm>

void XASM::parse(const string &path) {
    ifstream ifs;
    ifs.open(path);
    string line;
    if (ifs.is_open()) {
        while (getline(ifs, line)) {
            if (line.starts_with("//") or line.empty()) continue;
            program.push_back(line);
        }
        ifs.close();
    }
    uint8_t addr = 0;
    // Define jump points
    for (int i = 0; i < program.size(); i++) {
        if (program[i].starts_with("proc")){
            string proc_name = program[i].substr(5, program[i].length());
            procedures[proc_name] = addr;
            program.erase(program.begin() + i);
            i--;

        }

        if (!program[i].starts_with("MEM")) addr++;
    }
    // Write program to memory
    addr = 0;
    for (auto l: program) {
        writeDirective(l, &addr);

    }
}

void XASM::writeDirective(const string &com, uint8_t *com_addr) {
    string s;

    string op = com.substr(0, com.find(' '));
    string data = com.substr(com.find(' ') + 1, com.length());
    if (op == "MEM") {
        uint8_t addr = (uint8_t) stoul(data.substr(0, data.find(' ')), nullptr, 16);
        string seq = data.substr(data.find(' '), data.length());
        seq.erase(0, 1);
        erase(seq, '[');
        erase(seq, ']');
        erase(seq, ' ');

        stringstream ss(seq);

        int index = 0;
        while (getline(ss, s, ',')) {
            uint8_t current_addr = addr + index;
            auto v = static_cast<uint32_t>(std::stoul(s));
            cpu->write(current_addr, v);
            index++;
        }

    } else {
        auto it = std::find_if(
                cpu->op_table.begin(),
                cpu->op_table.end(),
                [&op](const CPU::INSTRUCTION& instruction) {
                    return instruction.name == op;
                });
        int op_index = std::distance(cpu->op_table.begin(), it);

        uint8_t a_op = 0;
        uint8_t b_op = 0;
        uint8_t c_op = 0;
        if ((op == "JMP" or op == "JMN" or op == "JM0" or op == "JMDN") && procedures.contains(data)){
            a_op = procedures[data];
        } else {
            stringstream ss(data);
            string a,b,c;
            getline(ss, a, ' ');
            getline(ss, b, ' ');
            getline(ss, c, ' ');

            a_op = (uint8_t) stoul(a, nullptr, 16);
            b_op = (uint8_t) stoul(b, nullptr, 16);
            c_op = (uint8_t) stoul(c, nullptr, 16);
        }



        cpu->write(*com_addr, op_index << 24 | a_op << 16 | b_op << 8 | c_op);

        (*com_addr)++;
    }
}

XASM::XASM(CPU *cpu) : cpu(cpu) {
    this->cpu = cpu;
}
