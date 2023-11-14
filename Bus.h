//
// Created by Niccko on 25.09.2023.
//

#ifndef CPU_BUS_H
#define CPU_BUS_H

#include "cstdint"
#include "array"
#include "CPU.h"


class Bus {
public:
    Bus();
    ~Bus();

public:
    CPU cpu;
public:
    std::array<uint32_t , 256> ram{};

    void write(uint8_t addr, uint32_t data);
    uint32_t read(uint8_t addr);
};


#endif //CPU_BUS_H
