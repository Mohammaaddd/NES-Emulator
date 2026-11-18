#pragma once

#include <cstdint>

#include "Bus.hpp"

class CPU
{

public:
    //General purpose registers
    std::uint8_t a{0};
    std::uint8_t x{0};
    std::uint8_t y{0};

    //sprcial registers
    std::uint16_t pc{0};
    std::uint8_t sp{0};

    //actual CPU status flags
    enum class Flag : std::uint8_t
    {
        Carry = 0x01,
        Zero = 0x02,
        InterruptDisable = 0x04,
        Decimal = 0x08,
        Overflow = 0x40,
        Negative = 0x80
    };

    explicit CPU(Bus& bus);

    void step();

    //madify a status flag
    void set_flag(Flag flag, bool value);

    //Read a status flag
    [[nodiscard]] bool get_flag(Flag flag) const;

    //void update_zero_and_negative_flags(std::uint8_t value);
    
private:
    std::uint8_t status_{0};
    Bus& bus_;


    std::uint8_t fetch_byte();
    std::uint8_t fetch_zero_page_address();
    std::uint16_t fetch_absolute_address();
    void update_zero_and_negative_flags(std::uint8_t value);
};

