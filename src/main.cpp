#include "Bus.hpp"
#include "CPU.hpp"

#include <cassert>
#include <iostream>

int main()
{
    Bus bus;
    CPU cpu(bus);

    // LDA #$C8
    bus.write(0x0000, 0xA9);
    bus.write(0x0001, 0xC8);

    // ADC #$64
    bus.write(0x0002, 0x69);
    bus.write(0x0003, 0x64);

    cpu.step(); // Execute LDA
    cpu.step(); // Execute ADC

    assert(cpu.a == 0x2C);
    assert(cpu.get_flag(CPU::Flag::Carry));
    assert(!cpu.get_flag(CPU::Flag::Zero));
    assert(!cpu.get_flag(CPU::Flag::Negative));
    assert(!cpu.get_flag(CPU::Flag::Overflow));
}