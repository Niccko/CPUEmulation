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
//    ifstream ifs;
//    ifs.open("C:\\Users\\maksim.shekhanin\\CLionProjects\\CPUEmulation\\program.txt");
//    string line;
//    int cycles = 0;
//    if (ifs.is_open()) {
//        int cnt = 0;
//        while (getline(ifs, line)) {
//            if (cnt == 0){
//                cycles = stoul(line);
//            }
//            cpu->write(cnt, (uint16_t)stoul(line, nullptr, 16));
//            cnt++;
//        }
//        ifs.close();
//    }

    cpu->write(0x00, 0x0206FF00);
    cpu->write(0x01, 0x04F00600);
    cpu->clock();
    cpu->clock();

    cpu->write(0x10, 2);
    cpu->write(0x11, 124);
    cpu->write(0x12, 1222);
    cpu->write(0x13, 23155);
    cpu->write(0x14, 11);
    cpu->write(0x15, 1);

//    for (int i = 0; i < cycles; ++i) {
//        cpu->clock();
//    }
    cout << cpu->read(0xF0) << endl;



    return 0;
}
