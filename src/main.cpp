#include <iostream>
#include <cassert>

#include "CPU.hpp"

int main(){
    CPU cpu;

    //check initial register values

    assert(cpu.a == 0);
    assert(cpu.x == 0);
    assert(cpu.y == 0);
    assert(cpu.pc == 0);
    assert(cpu.sp == 0);

    //enable carry
    cpu.set_flag(CPU::Flag::Carry, true);

    assert(cpu.get_flag(CPU::Flag::Carry));
    assert(!cpu.get_flag(CPU::Flag::Zero));

    //Disable carry
    cpu.set_flag(CPU::Flag::Carry, false);

    assert(!cpu.get_flag(CPU::Flag::Carry));
    assert(!cpu.get_flag(CPU::Flag::Zero));

    //enable negative
    cpu.set_flag(CPU::Flag::Negative, true);

    //enable Overflow
    cpu.set_flag(CPU::Flag::Overflow, true);
    
    //disable negative
    cpu.set_flag(CPU::Flag::Negative, false);

    assert(cpu.get_flag(CPU::Flag::Overflow));
    assert(!cpu.get_flag(CPU::Flag::Negative));

    std::cout << "all CPU register tests passed!\n";
}