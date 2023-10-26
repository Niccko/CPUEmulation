//
// Created by Niccko on 25.09.2023.
//

#include <iostream>
#include "CPU.h"
#include "Bus.h"

CPU::CPU() {
    for (auto &i: op_registers) i = 0x0000;

    op_table = {
            {"CMP", &CPU::CMP},
            {"LD",  &CPU::LD},
            {"MOV", &CPU::STX}
    };
};

CPU::~CPU() = default;

void CPU::write(uint16_t addr, uint16_t data) {
    bus->write(addr, data);
}

uint16_t CPU::read(uint16_t addr) {
    return bus->read(addr);
}

void CPU::clock() {
    uint16_t command = read(pc);
    pc++;
    opcode = command >> 12;
    a_reg_addr = (command & 0x00F0) >> 4;
    b_reg_addr = (command & 0x000F);
    x_reg_addr = (command & 0x0F00) >> 8;
    (this->*op_table[opcode].exec)();
}

uint8_t CPU::LD() {
    uint16_t data = fetch();
    std::cout << "LD " + std::to_string(data) + " -> reg[" + std::to_string(a_reg_addr) + "]" << std::endl;
    op_registers[a_reg_addr] = data;
    return 0;
}


uint8_t CPU::CMP() {
    std::cout << "CMP " + std::to_string(op_registers[a_reg_addr]) +
                 " " + std::to_string(op_registers[b_reg_addr]) +
                 " -> reg[" + std::to_string(x_reg_addr) + "] " << std::endl;

    uint16_t t = op_registers[a_reg_addr] - op_registers[b_reg_addr];
    setFlag(FLAGS::Z, t == 0);
    setFlag(FLAGS::N, t & 0x8000);
    if (!getFlag(FLAGS::N)) {
        op_registers[x_reg_addr] = op_registers[a_reg_addr];
    } else {
        op_registers[x_reg_addr] = op_registers[b_reg_addr];
    }
    return 0;
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

uint16_t CPU::fetch() {
    uint16_t a = read(pc++);
    return read(a);
}

uint8_t CPU::JMP() {
    pc = fetch();
    return 0;
}

uint8_t CPU::STX() {
    uint16_t a = read(pc++);
    std::cout << "MOV " + std::to_string(op_registers[a_reg_addr]) + " -> MEM[" << std::hex << a << "]" << std::endl;
    write(a, op_registers[a_reg_addr]);
    return 0;
}


