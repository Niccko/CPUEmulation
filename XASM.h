//
// Created by maksim.shekhanin on 11/19/2023.
//

#ifndef CPU_XASM_H
#define CPU_XASM_H
using namespace std;
#include "CPU.h"
#include <fstream>
#include <iostream>
#include <regex>

class XASM {
public:
    explicit XASM(CPU *cpu);

    void parse(const string& path);
private:
    CPU* cpu;

    void writeDirective(const string& com, uint8_t *com_addr);
};


#endif //CPU_XASM_H
