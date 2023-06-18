#include <iostream>
#include <ios>
#include <array>
#include <functional>

#include "6502.hpp"
#include "buses.hpp"
#include "instructions.hpp"

/**
 * Instruction decoding is done by getting an index from decoder[IR]
 * decoder is sparse array of indices (uint8_t).
 * The executor[index] is a function pointer to the function executing the instruction. (100% side effects)
 * executor is a dense array.
 * The function pointed to, reads the parameters it need, writes the result, update flags and step PC
 * it need full access to read/write physical bus as well as all internal registers.
*/
namespace detail {
    // Each position corresponds to an opcode and holds an index into executor
    // decoder is a sparse array with all possible 8 bit opcodes
    std::array<uint8_t, 0x100> decoder { 
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 0 - 0x0F
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 0x10 -
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 0x50 -
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0x21,0,0,
        0,0,0x51,0,0,0,0,0,0,0,0,0,0,0,0,0, // 0xA0 -
        0,0,0,0,0,0,0,0,0,0,0,0,0,0x4B,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    };
    constexpr std::size_t NumberOfOpCodes = 150;
    // Each position holds a pointer to a function for each op code in lexical order
    // executor is a dense array
    std::array<std::function<void (CPU *)>, NumberOfOpCodes> executor {
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, // 0 - 7
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, // 0x8 - 0x1F
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, // 0x10 -
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, // 0x20 -
        STAXIA, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, // 0x30 -
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, // 0x40 -
        nullptr, nullptr, nullptr, LDAXIA, nullptr, nullptr, nullptr, nullptr,
        nullptr, LDXI, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
        };
}

enum class State{fetch, decode, process, };

void CPU::reset() {
    PC = read(uint16_t(0xFFFD)) << 8 | read(uint16_t(0xFFFC));
    SP = uint16_t(0);
    IR = uint8_t(0);
}

void CPU::process() {
    // Emit PC, read from rom into IR
    // Decode instruction in IR, IR indexes into an array of functionpointers.
    IR = read(PC);
    std::cout << "PC: " << std::hex << PC << ", IR: " << std::hex << int(IR) << "\n";
    auto index = detail::decoder[IR];
    auto instr = detail::executor[index];
    instr(this);
}





