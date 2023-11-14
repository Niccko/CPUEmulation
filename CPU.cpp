//
// Created by Niccko on 25.09.2023.
//

#include <iostream>
#include "CPU.h"
#include "Bus.h"

CPU::CPU() {
    for (auto &i: registers) i = 0x00000000;
    op_table = {
            {"CMP", &CPU::CMP, &CPU::MEM},
            {"LDR", &CPU::LDR, &CPU::MEM},
            {"LDR", &CPU::LDR, &CPU::DIR},
            {"STR", &CPU::STR, &CPU::MEM},
            {"STR", &CPU::STR, &CPU::DIR},
            {"JMN", &CPU::JMN, &CPU::DIR}
    };
};

CPU::~CPU() = default;

void CPU::write(uint8_t addr, uint32_t data) {
    bus->write(addr, data);
}

uint32_t CPU::read(uint8_t addr) {
    return bus->read(addr);
}

void CPU::clock() {
    uint32_t command = fetch();
    opcode = command >> 24;
    registers[0] = (command & 0x00FF0000) >> 16;
    registers[1] = (command & 0x0000FF00) >> 8;
    registers[2] = (command & 0x000000FF) >> 16;
    (this->*op_table[opcode].addr_mode)();
    (this->*op_table[opcode].exec)();
}

uint8_t CPU::getFlag(CPU::FLAGS f) {
    return ((status & f) > 0) ? 1 : 0;
}

void CPU::setFlag(CPU::FLAGS f, bool v) {
    if (v)
        status |= f;
    else
        status &= ~f;
}

uint32_t CPU::fetch() {
    return read(pc++);
}

// Commands
uint8_t CPU::LDR() {
    registers[registers[0]] = registers[1];
    return 0;
}


uint8_t CPU::CMP() {
    uint32_t t = registers[3] - registers[4];
    setFlag(FLAGS::N, t & 0x80000000);
    setFlag(FLAGS::Z, t == 0);
    return 0;
}

uint8_t CPU::JMN() {
    if (getFlag(FLAGS::N)) {
        pc = registers[3];
    }
    return 0;
}

uint8_t CPU::STR() {
//    uint16_t a = read(pc++);
//    std::cout << "MOV " + std::to_string(op_registers[a_reg_addr]) + " -> MEM[" << std::hex << a << "]" << std::endl;
//    write(a, op_registers[a_reg_addr]);
    write(registers[3], registers[registers[4]]);
    return 0;
}


//Addressing modes
void CPU::DIR() {
    registers[3] = registers[0];
    registers[4] = registers[1];
    registers[5] = registers[2];
}

void CPU::IMP() {

}

void CPU::MEM() {
    registers[3] = read(registers[0]);
    registers[4] = read(registers[1]);
    registers[5] = read(registers[2]);
}

