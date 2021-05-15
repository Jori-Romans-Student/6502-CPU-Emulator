// ========== Types ==========

using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;

// Codes

#define AB 0x00
#define ABX 0x01
#define ABY 0x02
#define AC 0x03
#define ID 0x04
#define IDX 0x05
#define IDY 0x06
#define IMM 0x07
#define REL 0x08
#define ZP 0x09
#define ZPX 0x0A
#define ZPY 0x0B

// Instructions

#define LDA 0x00
#define LDX 0x01
#define LDY 0x02
#define STA 0x04
#define STX 0x05
#define STY 0x06
#define TAX 0x07
#define TAY 0x08
#define TSX 0x09
#define TXA 0x0A
#define TYA 0x0B