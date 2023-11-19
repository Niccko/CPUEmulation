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
    std::array<uint8_t, 3> arg_regs{};
    std::array<uint32_t , 8> gp_regs{};
    uint8_t status = 0x00; //Status register
    uint8_t pc = 0x00; // Program counter

    struct INSTRUCTION
    {
        std::string name;
        uint8_t     (CPU::*exec )(void) = nullptr;
    };

    std::vector<INSTRUCTION> op_table;

    enum FLAGS
    {
        Z = (1 << 0),	// Zero
        N = (1 << 1),	// Negative
    };
private:
    [[nodiscard]] uint8_t getFlag(FLAGS f) const;
    void setFlag(FLAGS f, bool v);

    Bus *bus = nullptr;
    uint8_t opcode;

private:
    // Commands
    uint8_t CMP();
    uint8_t CMPI();
    uint8_t JMN();
    uint8_t JM0();
    uint8_t JMP();
    uint8_t JMD0();
    uint8_t MOV();
    uint8_t MOVL();
    uint8_t MOVI();
    uint8_t INC();
    uint8_t ADDL();
    uint8_t ADD();
    uint8_t EMP();






};
