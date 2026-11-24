#include "Bus.hpp"
#include "CPU.hpp"

#include <cassert>
#include <iostream>

int main()
{
    Bus bus;
    CPU cpu(bus);

    // LDA #$10
    bus.write(0x0000, 0xA9);
    bus.write(0x0001, 0x10);

    // SBC #$20
    bus.write(0x0002, 0xE9);
    bus.write(0x0003, 0x20);

    cpu.set_flag(CPU::Flag::Carry, true);

    cpu.step();
    cpu.step();

    assert(cpu.a == 0xF0);
    assert(!cpu.get_flag(CPU::Flag::Carry));
    assert(cpu.get_flag(CPU::Flag::Negative));
}