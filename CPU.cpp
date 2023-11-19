//
// Created by Niccko on 25.09.2023.
//

#include <iostream>
#include "CPU.h"
#include "Bus.h"

CPU::CPU() {
    for (auto &i: gp_regs) i = 0x00000000;
    for (auto &i: arg_regs) i = 0x00;
    op_table = {
            {"EMP",  &CPU::EMP},   //0x00

            {"CMP",  &CPU::CMP},   //0x01
            {"CMPI", &CPU::CMPI},  //0x02

            {"JMN",  &CPU::JMN},   //0x03
            {"JMP",  &CPU::JMP},   //0x04
            {"JM0",  &CPU::JM0},   //0x05
            {"JMD0",  &CPU::JMD0},   //0x05

            {"MOV",  &CPU::MOV},   //0x06
            {"MOVL", &CPU::MOVL},  //0x07
            {"MOVI", &CPU::MOVI},  //0x08

            {"INC",  &CPU::INC},   //0x09
            {"ADDL", &CPU::ADDL},  //0x0A
            {"ADD",  &CPU::ADD},   //0x0B
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
    arg_regs[0] = (command & 0x00FF0000) >> 16;
    arg_regs[1] = (command & 0x0000FF00) >> 8;
    arg_regs[2] = (command & 0x000000FF);
    (this->*op_table[opcode].exec)();
}

uint8_t CPU::getFlag(CPU::FLAGS f) const {
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
uint8_t CPU::CMP() {
    uint32_t a = read(arg_regs[0]);
    uint32_t b = read(arg_regs[1]);
    printf("CMPI [%x (0x%x) - %x (0x%x)]\n", a, arg_regs[0], b, arg_regs[1]);
    uint32_t t = a - b;
    setFlag(FLAGS::N, t & 0x80000000);
    setFlag(FLAGS::Z, t == 0);
    return 0;
}

uint8_t CPU::CMPI() {
    uint32_t a = read(arg_regs[0]);
    uint32_t b = read(read(arg_regs[1]));
    printf("CMPI [%x (0x%x) - %x (0x%x)]\n", a, arg_regs[0], b, read(arg_regs[1]));
    uint32_t t = a - b;
    setFlag(FLAGS::N, t & 0x80000000);
    setFlag(FLAGS::Z, t == 0);
    return 0;
}


uint8_t CPU::JMN() {
    printf("JMN [%x (0x%x)]\n", read(arg_regs[0]), arg_regs[0]);
    if (getFlag(FLAGS::N)) {
        pc = read(arg_regs[0]);
    }
    return 0;
}


uint8_t CPU::JMP() {
    printf("JMP [%x (0x%x)]\n", read(arg_regs[0]), arg_regs[0]);
    pc = read(arg_regs[0]);
    return 0;
}


uint8_t CPU::JM0() {
    printf("JM0 [%x (0x%x)]\n", read(arg_regs[0]), arg_regs[0]);
    if (getFlag(FLAGS::Z)) {
        pc = read(arg_regs[0]);
    }
    return 0;
}

uint8_t CPU::MOV() {
    uint32_t t = read(arg_regs[0]);
    printf("MOV [0x%x <- %x (0x%x)]\n", arg_regs[1], t, arg_regs[0]);
    write(arg_regs[1], t);
    setFlag(FLAGS::Z, true);
    return 0;
}

uint8_t CPU::MOVI() {
    uint32_t t = read(read(arg_regs[0]));
    printf("MOVI [0x%x <- %x (0x%x)]\n", arg_regs[1], t, read(arg_regs[0]));
    write(arg_regs[1], t);
    setFlag(FLAGS::Z, true);
    return 0;
}

uint8_t CPU::MOVL() {
    printf("MOVL [0x%x <- %x]\n", arg_regs[1], arg_regs[0]);
    write(arg_regs[1], arg_regs[0]);
    setFlag(FLAGS::Z, true);
    return 0;
}

uint8_t CPU::INC() {
    uint32_t t = read(arg_regs[0]);
    printf("INC [%x (0x%x) ++]\n", t, arg_regs[0]);
    write(arg_regs[0], t + 1);
    return 0;
}

uint8_t CPU::ADDL() {
    uint32_t t = read(arg_regs[0]);
    printf("ADDL [%x (0x%x) + %x]\n", t, arg_regs[0], arg_regs[1]);
    write(arg_regs[0], t + arg_regs[1]);
    return 0;
}

uint8_t CPU::ADD() {
    uint32_t t = read(arg_regs[0]);
    uint32_t inc = read(arg_regs[1]);
    printf("ADD [%x (0x%x) + %x (0x%x)]\n", t, arg_regs[0], inc, arg_regs[1]);
    write(arg_regs[0], t + inc);
    return 0;
}

uint8_t CPU::EMP() {
    // Do nothing
    //printf("EMP []\n");
    return 0;
}

uint8_t CPU::JMD0() {
    if (getFlag(FLAGS::Z)){
        pc = arg_regs[0];
    }
    printf("JMD [%x]\n", arg_regs[0]);
    return 0;
}













