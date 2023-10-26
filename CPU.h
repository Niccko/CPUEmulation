//
// Created by Niccko on 25.09.2023.
//

#pragma once

#include <string>
#include <vector>
#include "cstdint"
#include "array"

class Bus;

class CPU {
public:
    CPU();

    ~CPU();

    void connectBus(Bus *b) { bus = b; }

    uint16_t read(uint16_t addr);

    void write(uint16_t addr, uint16_t data);

    void clock();

    uint16_t fetch();

public:
    std::array<uint16_t, 16> op_registers{};
    uint8_t a_reg_addr = 0x00;
    uint8_t b_reg_addr = 0x00;
    uint8_t x_reg_addr = 0x00;
    uint8_t status = 0x00; //Status register
    uint16_t pc = 0x0000; // Program counter

    enum FLAGS
    {
        C = (1 << 0),	// Carry Bit
        Z = (1 << 1),	// Zero
        I = (1 << 2),	// Disable Interrupts
        D = (1 << 3),	// Decimal Mode
        B = (1 << 4),	// Break
        U = (1 << 5),	// Unused
        V = (1 << 6),	// Overflow
        N = (1 << 7),	// Negative
    };
private:
    uint8_t getFlag(FLAGS f);
    void setFlag(FLAGS f, bool v);

    Bus *bus = nullptr;
    uint8_t opcode;
    uint8_t addr;

private:
    uint8_t LD();
    uint8_t CMP();
    uint8_t JMP();
    uint8_t STX();

    struct INSTRUCTION
    {
        std::string name;
        uint8_t     (CPU::*exec )(void) = nullptr;
    };

    std::vector<INSTRUCTION> op_table;

};
