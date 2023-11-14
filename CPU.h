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

    uint32_t read(uint8_t addr);

    void write(uint8_t addr, uint32_t data);

    void clock();

    uint32_t fetch();

public:
    std::array<uint32_t , 8> registers{};
    uint8_t status = 0x00; //Status register
    uint8_t pc = 0x00; // Program counter

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
    uint16_t fetched;

private:
    // Commands
    uint8_t LDR();
    uint8_t CMP();
    uint8_t JMN();
    uint8_t STR();

    //Addressing modes
    void DIR();
    void MEM();
    void IMP();

    struct INSTRUCTION
    {
        std::string name;
        uint8_t     (CPU::*exec )(void) = nullptr;
        void (CPU::*addr_mode )(void) = nullptr;
    };

    std::vector<INSTRUCTION> op_table;

};
