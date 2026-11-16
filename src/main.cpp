#include <iostream>
#include <cassert>

#include "CPU.hpp"
#include "Bus.hpp"

int main(){
    Bus bus;
    CPU cpu(bus);

    //LDA immediate: A = 0x99
    bus.write(0x0000, 0xA9);
    bus.write(0x0001, 0x99);

    //LDA zero page: A = memory[0x0042]
    bus.write(0x0002, 0xA5);
    bus.write(0x0003, 0x42);
    bus.write(0x0042, 0x55);

    //LDA absolute: A = memory[0x1234]
    bus.write(0x0004, 0xAD);
    bus.write(0x0005, 0x34);
    bus.write(0x0006, 0x12);
    bus.write(0x1234, 0x77);

    //STA zero page: memory[0x0050] = A
    bus.write(0x0007, 0x85);
    bus.write(0x0008, 0x50);

    cpu.pc = 0x0000;

    cpu.step();
    assert(cpu.a == 0x99);
    assert(cpu.pc == 0x0002);

    cpo.step();
    assert(cpu.a == 0x55);
    assert(cpu.pc == 0x0002);
    
    cpu.step();
    assert(cpu.a == 0x77);
    assert(cpu.pc == 0x0007);

    cpu.step();
    assert(bus.read(0x0050) == 0x77);
    assert(cpu.pc == 0x0009);

    std::cout << "addressing mode tests passed";
}