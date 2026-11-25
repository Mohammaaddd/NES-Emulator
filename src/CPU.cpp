 #include "CPU.hpp"

 #include <stdexcept>

 //public
 CPU::CPU(Bus& bus) : bus_(bus)
 {
 }

 void CPU::step()
 {
    std::uint8_t opcode = fetch_byte();

    switch(opcode)
    {
        case 0xA9: //load insturction
        {
            std::uint8_t value = fetch_byte();

            a = value;
    
            set_flag(Flag::Zero, a == 0);
            set_flag(Flag::Negative, (a & 0x80) != 0);
    
            break;
    
        }

        case 0xA5: //zero page LDA
        {
            std::uint8_t address = fetch_byte();

            a = bus_.read(address);

            update_zero_and_negative_flags(a);

            break;
        }

        case 0xAD: //absolute LDA
        {
            std::uint16_t address = fetch_absolute_address();

            a = bus_.read(address);

            update_zero_and_negative_flags(a);
            break;
        }

        case 0x85: //STA zero page (write)
        {
            std::uint8_t address = fetch_byte();

            bus_.write(address, a);

            break;
        }

        case 0x8D: //STA(store accumulator) absolute (write)
        {
            std::uint16_t address = fetch_absolute_address();

            bus_.write(address, a);
            
            break;
        }

        case 0xA2: //LDX
        {
            x = fetch_byte();

            update_zero_and_negative_flags(x);
            break;
        }

        case 0xA0: //LDY
        {
            y = fetch_byte();

            update_zero_and_negative_flags(y);
            break;
        }

        case 0xA6: //LDX zero page
        {
            std::uint8_t address = fetch_zero_page_address();

            x = bus_.read(address);

            update_zero_and_negative_flags(x);
            break;
        }

        case 0xAE: //LDX absolute
        {
            std::uint16_t address = fetch_absolute_address();

            x = bus_.read(address);

            update_zero_and_negative_flags(x);
            break;
        }

        case 0xA4: //LDY zero page
        {
            std::uint8_t address = fetch_zero_page_address();

            y = bus_.read(address);

            update_zero_and_negative_flags(y);
            break;
        }

        case 0xAC: //LDY absolute
        {
            std::uint16_t address = fetch_absolute_address();

            y = bus_.read(address);

            update_zero_and_negative_flags(y);

            break;
        }

        case 0x86: //STX zero page
        {
            std::uint8_t address = fetch_zero_page_address();

            bus_.write(address, x);
            break;
        }

        case 0x84: //STY zero page
        {
            std::uint8_t address = fetch_zero_page_address();

            bus_.write(address, y);
            break;
        }

        case 0xB5: //LDA zero page, X
        {
            std::uint8_t base_address = fetch_zero_page_address();

            std::uint8_t address = base_address + x;

            a = bus_.read(address);

            update_zero_and_negative_flags(a);

            break;
        }

        case 0xB9: //LDA absolute,Y
        {
            std::uint16_t base_address = fetch_absolute_address();

            std::uint16_t address = base_address + y;

            a = bus_.read(address);

            update_zero_and_negative_flags(a);

            break;
        }

        case 0x95: //STA zero page, X
        {
            std::uint8_t base_address = fetch_zero_page_address();

            std::uint8_t address = base_address + x;

            bus_.write(address, a);

            break;
        }

        case 0xBD: // LDA absolute,X
        {
            std::uint16_t base_address = fetch_absolute_address();

            std::uint16_t address = base_address + x;

            a = bus_.read(address);

            update_zero_and_negative_flags(a);

            break;
        }

        case 0xBE: //LDX absolute, Y
        {
            std::uint16_t base_address = fetch_absolute_address();

            std::uint16_t address = base_address + y;

            x = bus_.read(address);

            update_zero_and_negative_flags(x);

            break;
        }

        case 0xBC: //LDY absolute, X
        {
            std::uint16_t base_address = fetch_absolute_address();

            std::uint16_t address = base_address + x;

            y = bus_.read(address);

            update_zero_and_negative_flags(y);

            break;
        }

        case 0x9E: //STX absolute,  Y
        {
            std::uint16_t base_address = fetch_absolute_address();

            std::uint16_t address = base_address + y;

            bus_.write(address, x);

            break;
        }

        case 0x9C: //STY absolute, X
        {
            std::uint16_t base_address = fetch_absolute_address();

            std::uint16_t address = base_address + x;

            bus_.write(address, y);

            break;
        }

        case 0xB6: //LDX zero page, Y
        {
            std::uint8_t base_address = fetch_zero_page_address();

            std::uint8_t address = base_address + y;

            x = bus_.read(address);

            update_zero_and_negative_flags(x);

            break;
        }

        case 0xB4: //LDY zero page, X
        {
            std::uint8_t base_address = fetch_zero_page_address();

            std::uint8_t address = base_address + x;

            y = bus_.read(address);

            update_zero_and_negative_flags(y);

            break;
        }

        case 0x69: //ADC immediate
        {
            const std::uint8_t value = fetch_byte();

            const std::uint8_t old_a = a;

            const std::uint16_t sum = static_cast<std::uint16_t>(a) + value + (get_flag(Flag::Carry) ? 1 : 0);

            a = static_cast<std::uint8_t>(sum);

            set_flag(Flag::Carry, sum > 0xFF);

            set_flag(Flag::Overflow, (~(old_a ^ value) & (old_a ^ a) & 0x80) != 0);

            update_zero_and_negative_flags(a);

            break;
        }

        case 0xE9: //SBC immediate
        {
            const std::uint8_t value = fetch_byte();

            const std::uint8_t old_a = a;

            const std::uint16_t sum = static_cast<std::uint16_t>(a) + static_cast<std::uint8_t>(~value) + (get_flag(Flag::Carry) ? 1 : 0);

            a = static_cast<std::uint8_t>(sum);

            set_flag(Flag::Carry, sum > 0xFF);

            set_flag(Flag::Overflow, ((old_a^ a)& (old_a^ value) & 0x80) != 0);

            update_zero_and_negative_flags(a);

            break;
        }

        case 0xC9: //CMP immediate
        {
            const std::uint8_t value = fetch_byte();

            const std::uint16_t result = static_cast<std::uint16_t>(a) - value;

            set_flag(Flag::Carry, a >= value);

            set_flag(Flag::Zero, a == value);

            set_flag(Flag::Negative, (result & 0x80) != 0);

            break;
        }

        case 0xE0: //CPX immediate
        {
            const std::uint8_t value = fetch_byte();

            const std::uint16_t result = static_cast<std::uint16_t>(x) - value;

            set_flag(Flag::Carry, x >= value);

            set_flag(Flag::Zero, x >= value);

            set_flag(Flag::Negative, (result & 0x80) != 0);

            break;
        }

        case 0xC0: //CPX immediate
        {
            const std::uint8_t value = fetch_byte();

            const std::uint16_t result = static_cast<std::uint16_t>(y) - value;

            set_flag(Flag::Carry, y >= value);

            set_flag(Flag::Zero, y >= value);

            set_flag(Flag::Negative, (result & 0x80) != 0);

            break;
        }

        default:
        throw std::runtime_error("Unknown CPU opcode");

    }
 }

 void CPU::set_flag(Flag flag, bool value)
 {
    //convert the flag into its numaric bit mark
    const std::uint8_t mask = static_cast<std::uint8_t>(flag);

    if(value)
    {
        //turn the selected bit on
        status_ = static_cast<std::uint8_t>(status_ | mask);
    }
    else
    {
        //tuen the selected bit off
        status_ = static_cast<std::uint8_t>(status_ & static_cast<std::uint8_t>(~mask));
    }
 }

 bool CPU::get_flag(Flag flag) const
 {
    //convert the flag into its numaric bit mask
    const std::uint8_t mask = static_cast<std::uint8_t>(flag);

    //check whether the selected bit is on
    return (status_ & mask) != 0;
 }



 //private
 std::uint8_t CPU::fetch_byte()
 {
    std::uint8_t value = bus_.read(pc);
    pc++;

    return value;
 }

 std::uint8_t CPU::fetch_zero_page_address()
 {
    return fetch_byte();
 }

 std::uint16_t CPU::fetch_absolute_address()
 {
    std::uint8_t low = fetch_byte();
    std::uint8_t high = fetch_byte();

    return static_cast<std::uint16_t>(low) | (static_cast<std::uint16_t>(high) << 8);
 }

 void CPU::update_zero_and_negative_flags(std::uint8_t value)
 {
    set_flag(Flag::Zero, value == 0);
    set_flag(Flag::Negative, (value & 0x80) != 0);
 }