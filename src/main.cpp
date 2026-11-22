#include "Bus.hpp"
#include "CPU.hpp"

#include <cassert>
#include <iostream>

int main()
{
    Bus bus;
    CPU cpu(bus);

    // LDY #$02
    bus.write(0x0000, 0xA0);
    bus.write(0x0001, 0x02);

    // LDX $1234,Y
    bus.write(0x0002, 0xBE);
    bus.write(0x0003, 0x34);
    bus.write(0x0004, 0x12);
    bus.write(0x1236, 0x55);

    // LDX #$03
    bus.write(0x0005, 0xA2);
    bus.write(0x0006, 0x03);

    // LDY $2000,X
    bus.write(0x0007, 0xBC);
    bus.write(0x0008, 0x00);
    bus.write(0x0009, 0x04);
    bus.write(0x0403, 0x77);

    // STX $1200,Y
    bus.write(0x000A, 0x9E);
    bus.write(0x000B, 0x00);
    bus.write(0x000C, 0x12);

    // STY $1300,X
    bus.write(0x000D, 0x9C);
    bus.write(0x000E, 0x00);
    bus.write(0x000F, 0x13);

    cpu.pc = 0x0000;

    // Execute LDY
    cpu.step();
    assert(cpu.y == 0x02);

    // Execute LDX absolute,Y
    cpu.step();
    assert(cpu.x == 0x55);

    // Execute LDX immediate
    cpu.step();
    assert(cpu.x == 0x03);

    // Execute LDY absolute,X
    cpu.step();
    assert(cpu.y == 0x77);

    // Execute STX absolute,Y
    cpu.step();
    assert(bus.read(0x1277) == 0x03);

    // Execute STY absolute,X
    cpu.step();
    assert(bus.read(0x1303) == 0x77);

    std::cout << "Indexed instruction tests passed!!!!!!\n";

    return 0;
}