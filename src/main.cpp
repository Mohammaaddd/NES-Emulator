#include <iostream>
#include <cassert>

#include "CPU.hpp"
#include "Bus.hpp"

int main(){
    Bus bus;
    CPU cpu(bus);

    bus.write(0x0000, 0xA9);
    bus.write(0x0001, 0x42);

    cpu.pc = 0x0000;

    cpu.step();

    assert(cpu.a == 0x42);
    assert(cpu.pc == 0x0002);
    
    assert(cpu.get_flag(CPU::Flag::Zero) == false);
    assert(cpu.get_flag(CPU::Flag::Negative) == false);

    std::cout << "LDA immediate test passed!\n";
}