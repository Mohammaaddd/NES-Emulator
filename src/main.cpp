#include <iostream>
#include <cassert>

#include "CPU.hpp"
#include "Bus.hpp"

int main(){
    Bus bus;

    //write to the first ram region
    bus.write(0x0005, 0x42);

    //all ram mirrors should return the same value
    assert(bus.read(0x0005) == 0x42);
    assert(bus.read(0x0805) == 0x42);
    assert(bus.read(0x1005) == 0x42);
    assert(bus.read(0x1805) == 0x42);
    
    //write through a mirror
    bus.write(0x1005, 0x99);

    //the original address should now contain 0x99
    assert(bus.read(0x0005) == 0x99);

    //test the last physical RAM address
    bus.write(0x1FFF, 0xAB);

    assert(bus.read(0x07FF) == 0xAB);
    assert(bus.read(0x0FFF) == 0xAB);
    assert(bus.read(0x17FF) == 0xAB);
    assert(bus.read(0x1FFF) == 0xAB);

    std::cout << "All memory bus tests passed!\n";
}