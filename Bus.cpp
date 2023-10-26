//
// Created by Niccko on 25.09.2023.
//

#include <iostream>
#include "Bus.h"

void Bus::write(uint16_t addr, uint16_t data) {
    if (addr >= 0x0000 and addr <= 0xFFFF)
        ram[addr] = data;
}

uint16_t Bus::read(uint16_t addr) {
    if (addr >= 0x0000 and addr <= 0xFFFF)
        return ram[addr];
    return 0;
}

Bus::Bus() {
    for (auto &i: ram) i = 0x00000000;
    cpu.connectBus(this);
}

Bus::~Bus() = default;
