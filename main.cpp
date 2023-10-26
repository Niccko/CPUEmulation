#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include "Bus.h"
#include "CPU.h"

using namespace std;

int main() {
    Bus bus;
    CPU *cpu = &bus.cpu;
    ifstream ifs;
    ifs.open("C:\\Users\\Niccko\\CLionProjects\\CPU\\program.txt");
    string line;
    int cycles = 0;
    if (ifs.is_open()) {
        int cnt = 0;
        while (getline(ifs, line)) {
            if (cnt == 0){
                cycles = stoul(line);
            }
            cpu->write(cnt, (uint16_t)stoul(line, nullptr, 16));
            cnt++;
        }
        ifs.close();
    }



    cpu->write(0x0100, 2);
    cpu->write(0x0101, 124);
    cpu->write(0x0102, 1222);
    cpu->write(0x0103, 23155);
    cpu->write(0x0104, 11);
    cpu->write(0x0105, 1);

    for (int i = 0; i < cycles; ++i) {
        cpu->clock();
    }
    cout << cpu->read(0x0106) << endl;



    return 0;
}
