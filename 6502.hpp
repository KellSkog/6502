#pragma once
#include <stdint.h>

struct CPU {
    void reset();
    void process();

    uint16_t PC;
    uint16_t SP;
    uint8_t Acc;
    uint8_t X;
    uint8_t Y;
    uint8_t IR;
    uint8_t C : 1; // Bit 0 - Carry: Set when an unsigned addition or subtraction results in an overflow
    uint8_t Z : 1; // Bit 1 - Zero: Set when an operation results in a zero
    uint8_t I : 1; // Bit 2 - Interrupt Mask: When set, interrupt requests are ignored
    uint8_t D : 1; // Bit 3 - Decimal Mode: When set, certain instructions operate in decimal rather than binary mode
    uint8_t B : 1; // Bit 4 - Break: Set when a BRK instruction is executed
                // Bit 5, unused
    uint8_t V : 1; // Bit 6 - Overflow: Set when a signed addition or subtraction results in an overflow
    uint8_t N : 1; // Bit 7 - Negative: Set when an operation results in a negative number
};