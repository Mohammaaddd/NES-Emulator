#include "Bus.hpp"
#include "CPU.hpp"

#include <cassert>
#include <iostream>

int main()
{
    Bus bus;
    CPU cpu(bus);

    //LDA #$CA
    bus.write(0x0000, 0xA9);
    bus.write(0x0001, 0xCA);

    //AND #$A6
    bus.write(0x0002, 0x29);
    bus.write(0x0003, 0xA6);

    cpu.step();
    cpu.step();

    assert(cpu.a == 0x82);
    assert(!cpu.get_flag(CPU::Flag::Zero));
    assert(cpu.get_flag(CPU::Flag::Negative));
}