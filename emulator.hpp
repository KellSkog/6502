#include <array>

#include "6502.hpp"

constexpr int ramSize = 1024;
using RAM = std::array<uint8_t, ramSize>;

class Emulator {
public:
    Emulator(CPU &cpu, RAM &ram, ROM &rom);
    // have to map the cpu memory address to array indices
    uint8_t read(uint16_t adr);

    void write(uint16_t adr, uint8_t data);

    void process();
    private:
    CPU &_cpu;
    RAM &_ram;
    ROM &_rom;
};