#pragma once

#include <array>
#include <cstdint>

class Bus
{
public:
    //read a byte from a CPU memory address
    std::uint8_t read(std::uint16_t address);

    //write a byte to a CPU memory address
    void write(std::uint16_t address, std::uint8_t value);

private:
    //nes internal RAM is 2 KB
    static constexpr std::uint16_t RAM_SIZE = 0x0800;

    //actual physical RAM storage
    std::array<std::uint8_t, RAM_SIZE> ram_{};

};