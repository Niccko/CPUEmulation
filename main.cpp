#include "Bus.h"
#include "CPU.h"
#include "XASM.h"

using namespace std;

int main() {
    Bus bus;
    CPU *cpu = &bus.cpu;
    XASM xasm(cpu);

    xasm.parse("../program.xasm");

    for (int i = 0; i < 3000; ++i) {
        cpu->clock();
    }

    cout << cpu->read(0x11)<<endl;

    return 0;
}
