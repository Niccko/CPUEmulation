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

//    cpu->write(0x50, 3);
//    cpu->write(0x51, 2);
//    cpu->write(0x52, 15);
//    cpu->write(0x53, 14);
//
//    //MOV- Store size of array 0x10
//    cpu->write(0x00, 0x06501000);
//    //MOV Store first element in 0x11
//    cpu->write(0x01, 0x06511100);
//    //MOVL Pointer to first element of array
//    cpu->write(0x02, 0x07511200);
//    //MOVL Store pointer to changing max value func in 0x14
//    cpu->write(0x03, 0x070E1400);
//    //MOVL Store array index in 0x15
//    cpu->write(0x04, 0x07011500);
//
//    //MOVL Store start of a loop address in 0x13
//    cpu->write(0x05, 0x07061300);
//    //ADDL Add 1 to array pointer
//    cpu->write(0x06, 0x0A120100);
//    //CMPI Compare 0x11 and value in 0x12 pointer
//    cpu->write(0x07, 0x02111200);
//    //MOVL Store backpoint in 0x16
//    cpu->write(0x08, 0x070A1600);
//    //JMN JMN to reassign func
//    cpu->write(0x09, 0x03140000);
//    //CMP Compare counter with array size
//    cpu->write(0x0A, 0x01151000);
//    //JM0 Jump to end if zero
//    cpu->write(0x0B, 0x05300000);
//    //INC Inc array index
//    cpu->write(0x0C, 0x09150000);
//    //JMP Jump to start of the loop
//    cpu->write(0x0D, 0x04130000);
//
//
//
//
//    //MOVI MOV new value to 0x11
//    cpu->write(0x0E, 0x08121100);
//    //JMP Jump back
//    cpu->write(0x0F, 0x04160000);




    return 0;
}
