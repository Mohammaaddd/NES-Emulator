#include <iostream>
#include <cassert>

#include "CPU.hpp"
#include "Bus.hpp"

int main(){
    Bus bus;
    CPU cpu(bus);

    //LDX #$02
    bus.write(0x0000, 0xA2);
    bus.write(0x0001, 0x02);

    // LDA $40,X
    bus.write(0x0002, 0xB5);
    bus.write(0x0003, 0x40);


    // LDY #$02
    bus.write(0x0004, 0xA0);
    bus.write(0x0005, 0x02);

    // LDA $1234,Y
    bus.write(0x0006, 0xB9);
    bus.write(0x0007, 0x34);
    bus.write(0x0008, 0x12);

    // STA $50,X
    bus.write(0x0009, 0x95);
    bus.write(0x000A, 0x50);

    // Data
    bus.write(0x0042, 0x55);
    bus.write(0x1236, 0x77);

    cpu.pc = 0x0000;

    // Execute LDX
    cpu.step();
    assert(cpu.x == 0x02);

    // Execute LDA zero page,X
    cpu.step();
    assert(cpu.a == 0x55);

    // Execute LDY
    cpu.step();
    assert(cpu.y == 0x02);

    // Execute LDA absolute,Y
    cpu.step();
    assert(cpu.a == 0x77);

    // Execute STA zero page,X
    cpu.step();
    assert(bus.read(0x0052) == 0x77);

    std::cout << "Indexed addressing tests passed!\n";
}