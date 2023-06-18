#include <iostream>
#include <ios>
#include <stdint.h>

#include "6502.hpp"
#include "buses.hpp"
#include "rom_kernel.hpp"
#include "emulator.hpp"

RAM ram;
Emulator *emulator_ptr;

/** It is the responsibility of the emulator class to interface memory and CPU
 *  
*/
Emulator::Emulator(CPU &cpu, RAM &ram, ROM &rom) : _cpu{cpu}, _ram{ram}, _rom{rom} {
        emulator_ptr = this;
        _cpu.reset();
}
    // have to map the cpu memory address to array indices
uint8_t Emulator::read(uint16_t adr) {
        uint16_t arrayIndex = adr - (uint16_t(0xFFFF) - uint16_t(romSize - 1));
        std::cout << "arrayIndex: " << std::hex << arrayIndex << "\n";
        std::cout << "rom[arrayIndex]: " << std::hex << int(_rom[arrayIndex]) << "\n";
        uint8_t val = (adr < uint16_t(ramSize)) ? _ram[adr] : _rom[arrayIndex];
        return val;
}

void Emulator::write(uint16_t adr, uint8_t data) {
        uint16_t arrayIndex = adr - (uint16_t(0xFFFF) - uint16_t(romSize - 1));
        if(adr < uint16_t(ramSize)) {
            _ram[adr] = data;
        } else {
            _rom[arrayIndex] = data;
        }
}

void Emulator::process() {
        _cpu.process();
}


/** Implements the buses interface */
uint8_t read( uint16_t adr) {
    return emulator_ptr->read(adr);
}
void write(uint16_t adr, uint8_t data) {
    emulator_ptr->write(adr, data);
}

int main() {
    CPU cpu6502{};

    Emulator emulator{cpu6502, ram, rom};
    emulator.process();
    emulator.process();
}