#include <functional>

#include "buses.hpp"
#include "6502.hpp"

namespace detail
{
    void STAXIA(CPU *self) { // Store Accumulator in Memory X-Indexed Absolute 0x9D
        auto adr = read(uint16_t(self->PC + 2)) << 8 | read(uint16_t(self->PC + 1));
        self->PC += 3;
        write(adr + self->X, self->Acc);
    }
    std::function<void(CPU *self)> LDXI = [](CPU *self) // Load Index Register X From Memory Immediate 0xA2
    {
        self->X = read(self->PC + 1);
        self->PC += 2;
        self->Z = (self->X == 0) ? 0b0 : 0b1;
        self->N = (self->X & 0b1000'0000) ? 0b1 : 0b0;
    };
    void LDAXIA(CPU *self) { // LDA - Load Accumulator with Memory X-indexed Absolute 0xBD
        auto adr = read(uint16_t(self->PC + 2)) << 8 | read(uint16_t(self->PC + 1));
        self->PC += 3;
        self->Acc = read(adr + self->X);
    }
}
/* 150 op codes!




ADC #$nn	$69	2
ADC $nnnn	$6D	3
ADC $nnnn,X	$7D	3
ADC $nnnn,Y	$79	3
ADC $nn	$65	2
ADC $nn,X	$75	2
ADC ($nn,X)	$61	2
ADC ($nn),Y	$71	2
AND #$nn	$29	2
AND $nnnn	$2D	3
AND $nnnn,X	$3D	3
AND $nnnn,Y	$39	3
AND $nn	$25	2
AND $nn,X	$35	2
AND ($nn,X)	$21	2
AND ($nn),Y	$31	2
ASL A	$0A	1
ASL $nnnn	$0E	3
ASL $nnnn,X	$1E	3
ASL $nn	$06	2
ASL $nn,X	$16	2
BCS $nnnn	$B0	2
BEQ $nnnn	$F0	2
BIT $nnnn	$2C	3
BIT $nn	$24	2
BMI $nnnn	$30	2
BNE $nnnn	$D0	2
BPL $nnnn	$10	2
BRK	$00	1
BVC $nnnn	$50	2
BVS $nnnn	$70	2
CLC	$18	1
CLD	$D8	1
CLI	$58	1
CLV	$B8	1
CMP #$nn	$C9	2
CMP $nnnn	$CD	3
CMP $nnnn,X	$DD	3
CMP $nnnn,Y	$D9	3
CMP $nn	$C5	2
CMP $nn,X	$D5	2
CMP ($nn,X)	$C1	2
CMP ($nn),Y	$D1	2
CPX #$nn	$E0	2
CPX $nnnn	$EC	3
CPX $nn	$E4	2
CPY #$nn	$C0	2
CPY $nnnn	$CC	3
CPY $nn	$C4	2
DEC $nnnn	$CE	3
DEC $nnnn,X	$DE	3
DEC $nn	$C6	2
DEC $nn,X	$D6	2
DEX	$CA	1
DEY	$88.00	1
EOR #$nn	$49	2
EOR $nnnn	$4D	3
EOR $nnnn,X	$5D	3
EOR $nnnn,Y	$59	3
EOR $nn	$45	2
EOR $nn,X	$55	2
EOR ($nn,X)	$41	2
EOR ($nn),Y	$51	2
INC $nnnn	$EE	3
INC $nnnn,X	$FE	3
INC $nn	$E6	2
INC $nn,X	$F6	2
INX	$E8	1
INY	$C8	1
JMP $nnnn	$4C	3
JMP ($nnnn)	$6C	3
JSR $nnnn	$20	3
LDA #$nn	$A9	2
LDA $nnnn	$AD	3
LDA $nnnn,X	$BD	3
LDA $nnnn,Y	$B9	3
LDA $nn	$A5	2
LDA $nn,X	$B5	2
LDA ($nn,X)	$A1	2
LDA ($nn),Y	$B1	2
LDX #$nn	$A2	2
LDX $nnnn	$AE	3
LDX $nnnn,Y	$BE	3
LDX $nn	$A6	2
LDX $nn,Y	$B6	2
LDY #$nn	$A0	2
LDY $nnnn	$AC	3
LDY $nnnn,X	$BC	3
LDY $nn	$A4	2
LDY $nn,X	$B4	2
LSR A	$4A	1
LSR $nnnn	$4E	3
LSR $nnnn,X	$5E	3
LSR $nn	$46	2
LSR $nn,X	$56	2
NOP	$EA	1
ORA #$nn	$09	2
ORA $nnnn	$0D	3
ORA $nnnn,X	$1D	3
ORA $nnnn,Y	$19	3
ORA $nn	$05	2
ORA $nn,X	$15	2
ORA ($nn,X)	$01	2
ORA ($nn),Y	$11	2
PHA	$48	1
PHP	$08	1
PLA	$68	1
PLP	$28	1
ROL A	$2A	1
ROL $nnnn	$2E	3
ROL $nnnn,X	$3E	3
ROL $nn	$26	2
ROL $nn,X	$36	2
ROR A	$6A	1
ROR $nnnn	$6E	3
ROR $nnnn,X	$7E	3
ROR $nn	$66	2
ROR $nn,X	$76	2
RTI	$40	1
RTS	$60	1
SBC #$nn	$E9	2
SBC $nnnn	$ED	3
SBC $nnnn,X	$FD	3
SBC $nnnn,Y	$F9	3
SBC $nn	$E5	2
SBC $nn,X	$F5	2
SBC ($nn,X)	$E1	2
SBC ($nn),Y	$F1	2
SEC	$38	1
SED	$F8	1
SEI	$78	1
STA $nnnn	$8D	3
STA $nnnn,X	$9D	3
STA $nnnn,Y	$99	3
STA $nn	$85	2
STA $nn,X	$95	2
STA ($nn,X)	$81	2
STA ($nn),Y	$91	2
STX $nnnn	$8E	3
STX $nn	$86	2
STX $nn,Y	$96	2
STY $nnnn	$8C	3
STY $nn	$84	2
STY $nn,X	$94	2
TAX	$AA	1
TAY	$A8	1
TSX	$BA	1
TXA	$8A	1
TXS	$9A	1
TYA	$98	1

*/