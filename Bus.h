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
    std::array<uint16_t , 64 * 1024> ram{};

    void write(uint16_t addr, uint16_t data);
    uint16_t read(uint16_t addr);
};


#endif //CPU_BUS_H
