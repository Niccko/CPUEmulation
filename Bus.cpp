//
// Created by Niccko on 25.09.2023.
//

#include <iostream>
#include "Bus.h"

void Bus::write(uint8_t addr, uint32_t data) {
    if (addr >= 0x00 and addr <= 0xFF)
        ram[addr] = data;
}

uint32_t Bus::read(uint8_t addr) {
    if (addr >= 0x00 and addr <= 0xFF)
        return ram[addr];
    return 0;
}

Bus::Bus() {
    for (auto &i: ram) i = 0x00000000;
    cpu.connectBus(this);
}

Bus::~Bus() = default;
