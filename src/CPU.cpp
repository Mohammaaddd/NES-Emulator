 #include "CPU.hpp"

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

 