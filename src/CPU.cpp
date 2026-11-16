 #include "CPU.hpp"

 #include <stdexcept>

 //public
 CPU::CPU(Bus& bus) : bus_(bus)
 {
 }

 void CPU::step()
 {
    std::uint8_t opcode = fetch_bytes();

    switch(opcode)
    {
        case 0xA9: //load insturction
        {
            std::uint8_t value = fetch_bytes();

            a = value;
    
            set_flag(Flag::Zero, a == 0);
            set_flag(Flag::Negative, (a & 0x80) != 0);
    
            break;
    
        }

        case 0xA5: //zero page LDA
        {
            std::uint8_t address = fetch_bytes();

            a = bus_.read(address);

            set_flag(Flag::Zero, a == 0);
            set_flag(Flag::Negative, (a & 0x80) != 0);

            break;
        }

        case 0xAD: //absolute LDA
        {
            std::uint8_t low = fetch_bytes();
            std::uint8_t high = fetch_bytes();

            std::uint16_t address = static_cast<std::uint16_t>(low) | (static_cast<std::uint16_t>(high) << 8);

            a = bus_.read(address);

            set_flag(Flag::Zero, a == 0);
            set_flag(Flag::Negative, (a & 0x80) != 0);

            break;
        }

        case 0x85: //STA zero page (write)
        {
            std::uint8_t address = fetch_bytes();

            bus_.write(address, a);

            break;
        }

        case 0x8D: //STA absolute (write)
        {
            std::uint8_t low = fetch_bytes();
            std::uint8_t high = fetch_bytes();

            std::uint16_t address = static_cast<std::uint16_t>(low) | (static_cast<std::uint16_t>(high) << 8);

            bus_.write(address, a);
            
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
 std::uint8_t CPU::fetch_bytes()
 {
    std::uint8_t value = bus_.read(pc);
    pc++;

    return value;
 }

 