#pragma once

using Byte = unsigned char;
using Word = unsigned short;

using Signed = signed char;

using Bit = bool;

struct Location {
    
    Word address;
    bool valid;

    Location() 
    {
        address = 0x0000;
        valid = false;
    };

    Location(Word location_) 
    {
        address = location_;
        valid = true;
    };

    bool operator==(Location loc) {
        return (address == loc.address && valid == loc.valid);
    }


};