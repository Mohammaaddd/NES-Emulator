#include "Bus.hpp"

#include <stdexcept>

std::uint8_t Bus::read(std::uint16_t address)
{
    //internat RAM and its mirrors
    if(address <= 0x1FFF)
    {
        const std::uint16_t ramAddress = address & 0x07FF;

        return ram_[ramAddress];
    }

    //this address region has not been implemented yet
    throw std::out_of_range("cpu address memory not implemented");
}

void Bus::write(std::uint16_t address, std::uint8_t value)
{
    //internal RAM and its mirrors
    if(address <= 0x1FFF)
    {
        const std::uint16_t ramAddress = address & 0x07FF;

        ram_[ramAddress] = value;

        return;
    }

    throw std::out_of_range("cpu memory address not implemented");
}