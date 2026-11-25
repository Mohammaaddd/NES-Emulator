#include "Bus.hpp"
#include "CPU.hpp"

#include <cassert>
#include <iostream>

int main()
{
    Bus bus;
    CPU cpu(bus);

    // LDA #$20
    bus.write(0x0000, 0xA9);
    bus.write(0x0001, 0x20);

    // CMP #$20
    bus.write(0x0002, 0xC9);
    bus.write(0x0003, 0x20);

    cpu.step();
    cpu.step();

    assert(cpu.a == 0x20);
    assert(cpu.get_flag(CPU::Flag::Carry));
    assert(cpu.get_flag(CPU::Flag::Zero));
    assert(!cpu.get_flag(CPU::Flag::Negative));
}