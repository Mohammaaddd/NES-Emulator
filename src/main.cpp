#include <iostream>
#include <cassert>

#include "CPU.hpp"
#include "Bus.hpp"

int main(){
    Bus bus;
    CPU cpu(bus);

    //LDX immediate: X = 0x25
    bus.write(0x0000, 0xA2);
    bus.write(0x0001, 0x25);

    //LDY zero page: Y = memory[0x0040]
    bus.write(0x0002, 0xA4);
    bus.write(0x0003, 0x40);
    bus.write(0x0040, 0x80);

    //LDA absolute A = memory[0x1234]
    bus.write(0x0004, 0xAD);
    bus.write(0x0005, 0x34);
    bus.write(0x0006, 0x12);
    bus.write(0x1234, 0x00);

    cpu.pc = 0x0000;

    //execute LDX
    cpu.step();

    assert(cpu.x == 0x25);
    assert(cpu.get_flag(CPU::Flag::Zero) == false);
    assert(cpu.get_flag(CPU::Flag::Negative) == false);

    //execute LDY
    cpu.step();

    assert(cpu.y == 0x80);
    assert(cpu.get_flag(CPU::Flag::Zero) == false);
    assert(cpu.get_flag(CPU::Flag::Negative) == true);

    //execute LDA
    cpu.step();

    assert(cpu.a == 0x00);
    assert(cpu.get_flag(CPU::Flag::Zero) == true);
    assert(cpu.get_flag(CPU::Flag::Negative) == false);

    std::cout << "registers loading tests passed";
}