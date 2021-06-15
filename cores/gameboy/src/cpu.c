#include "cpu.h"
#include <stdlib.h>
#include "instructions.h"

CPU *cpu_new() {
    return (CPU *)malloc(sizeof(CPU));
}

void cpu_destroy(CPU *cpu) {
    free(cpu);
}

u8 cpu_read(CPU *cpu, u16 address) {
    return 0x0000;  // TODO: implement this
}

u8 cpu_read_next_u8(CPU *cpu) {
    return 0x0000;  // TODO: implement this
}

void cpu_write(CPU *cpu, u16 address, u8 value) {
    // TODO: implement this
}

#define A  cpu->a
#define BC cpu->bc
#define DE cpu->de
#define HL cpu->hl
#define SP cpu->sp
#define B  ((cpu->bc >> 8) & 0x00FF)
#define C  (cpu->bc & 0x00FF)
#define D  ((cpu->de >> 8) & 0x00FF)
#define E  (cpu->de & 0x00FF)
#define H  ((cpu->hl >> 8) & 0x00FF)
#define L  (cpu->hl & 0x00FF)

#define MEMORY    cpu_read(cpu, cpu->hl)
#define NEXT_BYTE cpu_read_next_u8(cpu)

#pragma clang diagnostic push
#pragma ide diagnostic   ignored "OCUnusedMacroInspection"

#define SET_A(x) (cpu->a = (x))
#define SET_B(x) (cpu->bc |= ((x) << 8) & 0xFF00)
#define SET_C(x) (cpu->bc |= (x)&0x00FF)
#define SET_D(x) (cpu->de |= ((x) << 8) & 0xFF00)
#define SET_E(x) (cpu->de |= (x)&0x00FF)
#define SET_H(x) (cpu->hl |= ((x) << 8) & 0xFF00)
#define SET_L(x) (cpu->hl |= (x)&0x00FF)

#define SET_MEMORY(x) cpu_write(cpu, cpu->hl, x)

#pragma clang diagnostic pop

// 8-bit Arithmetic and Logic Instructions
#define ADC(x)  _adc(cpu, x)
#define ADD8(x) _add8(cpu, x)
#define AND(x)  _and(cpu, x)
#define CP(x)   _cp(cpu, x)
#define DEC(x)  SET_##x(_dec(cpu, x))
#define INC(x)  SET_##x(_inc(cpu, x))
#define OR(x)   _or(cpu, x)
#define SBC(x)  _sbc(cpu, x)
#define SUB(x)  _sub(cpu, x)
#define XOR(x)  _xor(cpu, x)

// 16-bit Arithmetic Instructions
#define ADD16(x) _add16(cpu, x)

#define CASE(id, instruction) \
    case id: {                \
        instruction;          \
        break;                \
    }

// clang-format off
void cpu_execute(CPU *cpu, u8 opcode) {
    switch (opcode) {
        //   LEGEND
        //   n8       8-bit integer constant.
        //   n16      16-bit integer constant.
        //   e8       8-bit offset (-128 to 127).
        //   u3       3-bit unsigned integer constant (0 to 7).
        //   cc       Condition codes:
        //                Z    Execute if Z is set.
        //                NZ   Execute if Z is not set.
        //                C    Execute if C is set.
        //                NC   Execute if C is not set.
        //   vec      One of the RST vectors (0x00, 0x08, 0x10, 0x18, 0x20, 0x28, 0x30, and 0x38).
        //
        //
        //   INSTRUCTIONS
        //   code  instruction             name        cycles    bytes    flags
        CASE(0x04, INC(B))              // INC B         1         1      Z N H -
        CASE(0x05, DEC(B))              // DEC B         1         1      Z N H -
        CASE(0x09, ADD16(BC))           // ADD HL,BC     2         1      - N H C
        CASE(0x0C, INC(C))              // INC C         1         1      Z N H -
        CASE(0x0D, DEC(C))              // DEC C         1         1      Z N H -
        CASE(0x14, INC(D))              // INC D         1         1      Z N H -
        CASE(0x15, DEC(D))              // DEC D         1         1      Z N H -
        CASE(0x19, ADD16(DE))           // ADD HL,DE     2         1      - N H C
        CASE(0x1C, INC(E))              // INC E         1         1      Z N H -
        CASE(0x1D, DEC(E))              // DEC E         1         1      Z N H -
        CASE(0x24, INC(H))              // INC H         1         1      Z N H -
        CASE(0x25, DEC(H))              // DEC H         1         1      Z N H -
        CASE(0x29, ADD16(HL))           // ADD HL,HL     2         1      - N H C
        CASE(0x2C, INC(L))              // INC L         1         1      Z N H -
        CASE(0x2D, DEC(L))              // DEC L         1         1      Z N H -
        CASE(0x34, INC(MEMORY))         // INC (HL)      3         1      Z N H -
        CASE(0x35, DEC(MEMORY))         // DEC (HL)      3         1      Z N H -
        CASE(0x39, ADD16(SP))           // ADD HL,SP     2         1      - N H C
        CASE(0x3C, INC(A))              // INC A         1         1      Z N H -
        CASE(0x3D, DEC(A))              // DEC A         1         1      Z N H -
        CASE(0x80, ADD8(B))             // ADD A,B       1         1      Z N H C
        CASE(0x81, ADD8(C))             // ADD A,C       1         1      Z N H C
        CASE(0x82, ADD8(D))             // ADD A,D       1         1      Z N H C
        CASE(0x83, ADD8(E))             // ADD A,E       1         1      Z N H C
        CASE(0x84, ADD8(H))             // ADD A,H       1         1      Z N H C
        CASE(0x85, ADD8(L))             // ADD A,L       1         1      Z N H C
        CASE(0x86, ADD8(MEMORY))        // ADD A,(HL)    2         1      Z N H C
        CASE(0x87, ADD8(A))             // ADD A,A       1         1      Z N H C
        CASE(0x88, ADC(B))              // ADC A,B       1         1      Z N H C
        CASE(0x89, ADC(C))              // ADC A,C       1         1      Z N H C
        CASE(0x8A, ADC(D))              // ADC A,D       1         1      Z N H C
        CASE(0x8B, ADC(E))              // ADC A,E       1         1      Z N H C
        CASE(0x8C, ADC(H))              // ADC A,H       1         1      Z N H C
        CASE(0x8D, ADC(L))              // ADC A,L       1         1      Z N H C
        CASE(0x8E, ADC(MEMORY))         // ADC A,(HL)    2         1      Z N H C
        CASE(0x8F, ADC(A))              // ADC A,A       1         1      Z N H C
        CASE(0x90, SUB(B))              // SUB A,B       1         1      Z N H C
        CASE(0x91, SUB(C))              // SUB A,C       1         1      Z N H C
        CASE(0x92, SUB(D))              // SUB A,D       1         1      Z N H C
        CASE(0x93, SUB(E))              // SUB A,E       1         1      Z N H C
        CASE(0x94, SUB(H))              // SUB A,H       1         1      Z N H C
        CASE(0x95, SUB(L))              // SUB A,L       1         1      Z N H C
        CASE(0x96, SUB(MEMORY))         // SUB A,(HL)    2         1      Z N H C
        CASE(0x97, SUB(A))              // SUB A,A       1         1      Z N H C
        CASE(0x98, SBC(B))              // SBC A,B       1         1      Z N H C
        CASE(0x99, SBC(C))              // SBC A,C       1         1      Z N H C
        CASE(0x9A, SBC(D))              // SBC A,D       1         1      Z N H C
        CASE(0x9B, SBC(E))              // SBC A,E       1         1      Z N H C
        CASE(0x9C, SBC(H))              // SBC A,H       1         1      Z N H C
        CASE(0x9D, SBC(L))              // SBC A,L       1         1      Z N H C
        CASE(0x9E, SBC(MEMORY))         // SBC A,(HL)    2         1      Z N H C
        CASE(0x9F, SBC(A))              // SBC A,A       1         1      Z N H C
        CASE(0xA0, AND(B))              // AND A,B       1         1      Z N H C
        CASE(0xA1, AND(C))              // AND A,C       1         1      Z N H C
        CASE(0xA2, AND(D))              // AND A,D       1         1      Z N H C
        CASE(0xA3, AND(E))              // AND A,E       1         1      Z N H C
        CASE(0xA4, AND(H))              // AND A,H       1         1      Z N H C
        CASE(0xA5, AND(L))              // AND A,L       1         1      Z N H C
        CASE(0xA6, AND(MEMORY))         // AND A,(HL)    2         1      Z N H C
        CASE(0xA7, AND(A))              // AND A,A       1         1      Z N H C
        CASE(0xA8, XOR(B))              // XOR A,B       1         1      Z N H C
        CASE(0xA9, XOR(C))              // XOR A,C       1         1      Z N H C
        CASE(0xAA, XOR(D))              // XOR A,D       1         1      Z N H C
        CASE(0xAB, XOR(E))              // XOR A,E       1         1      Z N H C
        CASE(0xAC, XOR(H))              // XOR A,H       1         1      Z N H C
        CASE(0xAD, XOR(L))              // XOR A,L       1         1      Z N H C
        CASE(0xAE, XOR(MEMORY))         // XOR A,(HL)    2         1      Z N H C
        CASE(0xAF, XOR(A))              // XOR A,A       1         1      Z N H C
        CASE(0xB0, OR(B))               // OR A,B        1         1      Z N H C
        CASE(0xB1, OR(C))               // OR A,C        1         1      Z N H C
        CASE(0xB2, OR(D))               // OR A,D        1         1      Z N H C
        CASE(0xB3, OR(E))               // OR A,E        1         1      Z N H C
        CASE(0xB4, OR(H))               // OR A,H        1         1      Z N H C
        CASE(0xB5, OR(L))               // OR A,L        1         1      Z N H C
        CASE(0xB6, OR(MEMORY))          // OR A,(HL)     2         1      Z N H C
        CASE(0xB7, OR(A))               // OR A,A        1         1      Z N H C
        CASE(0xB8, CP(B))               // CP A,B        1         1      Z N H C
        CASE(0xB9, CP(C))               // CP A,C        1         1      Z N H C
        CASE(0xBA, CP(D))               // CP A,D        1         1      Z N H C
        CASE(0xBB, CP(E))               // CP A,E        1         1      Z N H C
        CASE(0xBC, CP(H))               // CP A,H        1         1      Z N H C
        CASE(0xBD, CP(L))               // CP A,L        1         1      Z N H C
        CASE(0xBE, CP(MEMORY))          // CP A,(HL)     2         1      Z N H C
        CASE(0xBF, CP(A))               // CP A,A        1         1      Z N H C
        CASE(0xC6, ADD8(NEXT_BYTE))     // ADD A,n8      2         2      Z N H C
        CASE(0xCE, ADC(NEXT_BYTE))      // ADC A,n8      2         2      Z N H C
        default: exit(404);
    }
}
// clang-format on
