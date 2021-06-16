#include "cpu.h"
#include <memory.h>
#include <stdlib.h>
#include "instructions.h"

CPU *cpu_new() {
    CPU *cpu = (CPU *)malloc(sizeof(CPU));
    memset(cpu, 0, sizeof(CPU));  // clear all the junk this memory section could have
    return cpu;
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
#define DEC8(x) SET_##x(_dec8(cpu, x))
#define INC8(x) SET_##x(_inc8(cpu, x))
#define OR(x)   _or(cpu, x)
#define SBC(x)  _sbc(cpu, x)
#define SUB(x)  _sub(cpu, x)
#define XOR(x)  _xor(cpu, x)

// 16-bit Arithmetic Instructions
#define ADD16(x) _add16(cpu, x)
#define DEC16(x) _dec16(cpu, x)
#define INC16(x) _inc16(cpu, x)

// Bit Operations Instructions
#define BIT(bit, x) _bit(cpu, bit, x)
#define RES(bit, x) _res(cpu, bit, x)

#define EXECUTE_CB cpu_execute_cb(cpu, cpu_read_next_u8(cpu))

#define CASE(id, instruction) \
    case id: {                \
        instruction;          \
        break;                \
    }

// clang-format off
void cpu_execute(CPU *cpu, u8 opcode) {
    switch (opcode) {
        //   INSTRUCTIONS
        //   code  instruction             mnemonic    cycles    bytes    flags
        CASE(0x03, INC16(BC))           // INC BC        2         1      - - - -
        CASE(0x04, INC8(B))             // INC B         1         1      Z N H -
        CASE(0x05, DEC8(B))             // DEC B         1         1      Z N H -
        CASE(0x09, ADD16(BC))           // ADD HL,BC     2         1      - N H C
        CASE(0x0B, DEC16(BC))           // DEC BC        2         1      - - - -
        CASE(0x0C, INC8(C))             // INC C         1         1      Z N H -
        CASE(0x0D, DEC8(C))             // DEC C         1         1      Z N H -
        CASE(0x13, INC16(DE))           // INC DE        2         1      - - - -
        CASE(0x14, INC8(D))             // INC D         1         1      Z N H -
        CASE(0x15, DEC8(D))             // DEC D         1         1      Z N H -
        CASE(0x19, ADD16(DE))           // ADD HL,DE     2         1      - N H C
        CASE(0x1B, DEC16(DE))           // DEC DE        2         1      - - - -
        CASE(0x1C, INC8(E))             // INC E         1         1      Z N H -
        CASE(0x1D, DEC8(E))             // DEC E         1         1      Z N H -
        CASE(0x23, INC16(HL))           // INC HL        2         1      - - - -
        CASE(0x24, INC8(H))             // INC H         1         1      Z N H -
        CASE(0x25, DEC8(H))             // DEC H         1         1      Z N H -
        CASE(0x29, ADD16(HL))           // ADD HL,HL     2         1      - N H C
        CASE(0x2B, DEC16(HL))           // DEC HL        2         1      - - - -
        CASE(0x2C, INC8(L))             // INC L         1         1      Z N H -
        CASE(0x2D, DEC8(L))             // DEC L         1         1      Z N H -
        CASE(0x33, INC16(SP))           // INC SP        2         1      - - - -
        CASE(0x34, INC8(MEMORY))        // INC (HL)      3         1      Z N H -
        CASE(0x35, DEC8(MEMORY))        // DEC (HL)      3         1      Z N H -
        CASE(0x39, ADD16(SP))           // ADD HL,SP     2         1      - N H C
        CASE(0x3B, DEC16(SP))           // DEC SP        2         1      - - - -
        CASE(0x3C, INC8(A))             // INC A         1         1      Z N H -
        CASE(0x3D, DEC8(A))             // DEC A         1         1      Z N H -
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
        CASE(0xCB, EXECUTE_CB)          // execute one instruction prefixed with 0xCB
        CASE(0xC6, ADD8(NEXT_BYTE))     // ADD A,n8      2         2      Z N H C
        CASE(0xCE, ADC(NEXT_BYTE))      // ADC A,n8      2         2      Z N H C
        default: exit(404);
    }
}

void cpu_execute_cb(CPU *cpu, u8 opcode) {
    switch (opcode) {
        //   INSTRUCTIONS
        //   code  instruction             mnemonic    cycles    bytes    flags
        CASE(0x40, BIT(0, B))           // BIT 0,B       2         2      Z N H -
        CASE(0x41, BIT(0, C))           // BIT 0,C       2         2      Z N H -
        CASE(0x42, BIT(0, D))           // BIT 0,D       2         2      Z N H -
        CASE(0x43, BIT(0, E))           // BIT 0,E       2         2      Z N H -
        CASE(0x44, BIT(0, H))           // BIT 0,H       2         2      Z N H -
        CASE(0x45, BIT(0, L))           // BIT 0,L       2         2      Z N H -
        CASE(0x46, BIT(0, MEMORY))      // BIT 0,(HL)    3         2      Z N H -
        CASE(0x47, BIT(0, A))           // BIT 0,A       2         2      Z N H -
        CASE(0x48, BIT(1, B))           // BIT 1,B       2         2      Z N H -
        CASE(0x49, BIT(1, C))           // BIT 1,C       2         2      Z N H -
        CASE(0x4A, BIT(1, D))           // BIT 1,D       2         2      Z N H -
        CASE(0x4B, BIT(1, E))           // BIT 1,E       2         2      Z N H -
        CASE(0x4C, BIT(1, H))           // BIT 1,H       2         2      Z N H -
        CASE(0x4D, BIT(1, L))           // BIT 1,L       2         2      Z N H -
        CASE(0x4E, BIT(1, MEMORY))      // BIT 1,(HL)    3         2      Z N H -
        CASE(0x4F, BIT(1, A))           // BIT 1,A       2         2      Z N H -
        CASE(0x50, BIT(2, B))           // BIT 2,B       2         2      Z N H -
        CASE(0x51, BIT(2, C))           // BIT 2,C       2         2      Z N H -
        CASE(0x52, BIT(2, D))           // BIT 2,D       2         2      Z N H -
        CASE(0x53, BIT(2, E))           // BIT 2,E       2         2      Z N H -
        CASE(0x54, BIT(2, H))           // BIT 2,H       2         2      Z N H -
        CASE(0x55, BIT(2, L))           // BIT 2,L       2         2      Z N H -
        CASE(0x56, BIT(2, MEMORY))      // BIT 2,(HL)    3         2      Z N H -
        CASE(0x57, BIT(2, A))           // BIT 2,A       2         2      Z N H -
        CASE(0x58, BIT(3, B))           // BIT 3,B       2         2      Z N H -
        CASE(0x59, BIT(3, C))           // BIT 3,C       2         2      Z N H -
        CASE(0x5A, BIT(3, D))           // BIT 3,D       2         2      Z N H -
        CASE(0x5B, BIT(3, E))           // BIT 3,E       2         2      Z N H -
        CASE(0x5C, BIT(3, H))           // BIT 3,H       2         2      Z N H -
        CASE(0x5D, BIT(3, L))           // BIT 3,L       2         2      Z N H -
        CASE(0x5E, BIT(3, MEMORY))      // BIT 3,(HL)    3         2      Z N H -
        CASE(0x5F, BIT(3, A))           // BIT 3,A       2         2      Z N H -
        CASE(0x60, BIT(4, B))           // BIT 4,B       2         2      Z N H -
        CASE(0x61, BIT(4, C))           // BIT 4,C       2         2      Z N H -
        CASE(0x62, BIT(4, D))           // BIT 4,D       2         2      Z N H -
        CASE(0x63, BIT(4, E))           // BIT 4,E       2         2      Z N H -
        CASE(0x64, BIT(4, H))           // BIT 4,H       2         2      Z N H -
        CASE(0x65, BIT(4, L))           // BIT 4,L       2         2      Z N H -
        CASE(0x66, BIT(4, MEMORY))      // BIT 4,(HL)    3         2      Z N H -
        CASE(0x67, BIT(4, A))           // BIT 4,A       2         2      Z N H -
        CASE(0x68, BIT(5, B))           // BIT 5,B       2         2      Z N H -
        CASE(0x69, BIT(5, C))           // BIT 5,C       2         2      Z N H -
        CASE(0x6A, BIT(5, D))           // BIT 5,D       2         2      Z N H -
        CASE(0x6B, BIT(5, E))           // BIT 5,E       2         2      Z N H -
        CASE(0x6C, BIT(5, H))           // BIT 5,H       2         2      Z N H -
        CASE(0x6D, BIT(5, L))           // BIT 5,L       2         2      Z N H -
        CASE(0x6E, BIT(5, MEMORY))      // BIT 5,(HL)    3         2      Z N H -
        CASE(0x6F, BIT(5, A))           // BIT 5,A       2         2      Z N H -
        CASE(0x70, BIT(6, B))           // BIT 6,B       2         2      Z N H -
        CASE(0x71, BIT(6, C))           // BIT 6,C       2         2      Z N H -
        CASE(0x72, BIT(6, D))           // BIT 6,D       2         2      Z N H -
        CASE(0x73, BIT(6, E))           // BIT 6,E       2         2      Z N H -
        CASE(0x74, BIT(6, H))           // BIT 6,H       2         2      Z N H -
        CASE(0x75, BIT(6, L))           // BIT 6,L       2         2      Z N H -
        CASE(0x76, BIT(6, MEMORY))      // BIT 6,(HL)    3         2      Z N H -
        CASE(0x77, BIT(6, A))           // BIT 6,A       2         2      Z N H -
        CASE(0x78, BIT(7, B))           // BIT 7,B       2         2      Z N H -
        CASE(0x79, BIT(7, C))           // BIT 7,C       2         2      Z N H -
        CASE(0x7A, BIT(7, D))           // BIT 7,D       2         2      Z N H -
        CASE(0x7B, BIT(7, E))           // BIT 7,E       2         2      Z N H -
        CASE(0x7C, BIT(7, H))           // BIT 7,H       2         2      Z N H -
        CASE(0x7D, BIT(7, L))           // BIT 7,L       2         2      Z N H -
        CASE(0x7E, BIT(7, MEMORY))      // BIT 7,(HL)    3         2      Z N H -
        CASE(0x7F, BIT(7, A))           // BIT 7,A       2         2      Z N H -
        CASE(0x80, RES(0, B))           // RES 0,B       2         2      Z N H -
        CASE(0x81, RES(0, C))           // RES 0,C       2         2      Z N H -
        CASE(0x82, RES(0, D))           // RES 0,D       2         2      Z N H -
        CASE(0x83, RES(0, E))           // RES 0,E       2         2      Z N H -
        CASE(0x84, RES(0, H))           // RES 0,H       2         2      Z N H -
        CASE(0x85, RES(0, L))           // RES 0,L       2         2      Z N H -
        CASE(0x86, RES(0, MEMORY))      // RES 0,(HL)    3         2      Z N H -
        CASE(0x87, RES(0, A))           // RES 0,A       2         2      Z N H -
        CASE(0x88, RES(1, B))           // RES 1,B       2         2      Z N H -
        CASE(0x89, RES(1, C))           // RES 1,C       2         2      Z N H -
        CASE(0x8A, RES(1, D))           // RES 1,D       2         2      Z N H -
        CASE(0x8B, RES(1, E))           // RES 1,E       2         2      Z N H -
        CASE(0x8C, RES(1, H))           // RES 1,H       2         2      Z N H -
        CASE(0x8D, RES(1, L))           // RES 1,L       2         2      Z N H -
        CASE(0x8E, RES(1, MEMORY))      // RES 1,(HL)    3         2      Z N H -
        CASE(0x8F, RES(1, A))           // RES 1,A       2         2      Z N H -
        CASE(0x90, RES(2, B))           // RES 2,B       2         2      Z N H -
        CASE(0x91, RES(2, C))           // RES 2,C       2         2      Z N H -
        CASE(0x92, RES(2, D))           // RES 2,D       2         2      Z N H -
        CASE(0x93, RES(2, E))           // RES 2,E       2         2      Z N H -
        CASE(0x94, RES(2, H))           // RES 2,H       2         2      Z N H -
        CASE(0x95, RES(2, L))           // RES 2,L       2         2      Z N H -
        CASE(0x96, RES(2, MEMORY))      // RES 2,(HL)    3         2      Z N H -
        CASE(0x97, RES(2, A))           // RES 2,A       2         2      Z N H -
        CASE(0x98, RES(3, B))           // RES 3,B       2         2      Z N H -
        CASE(0x99, RES(3, C))           // RES 3,C       2         2      Z N H -
        CASE(0x9A, RES(3, D))           // RES 3,D       2         2      Z N H -
        CASE(0x9B, RES(3, E))           // RES 3,E       2         2      Z N H -
        CASE(0x9C, RES(3, H))           // RES 3,H       2         2      Z N H -
        CASE(0x9D, RES(3, L))           // RES 3,L       2         2      Z N H -
        CASE(0x9E, RES(3, MEMORY))      // RES 3,(HL)    3         2      Z N H -
        CASE(0x9F, RES(3, A))           // RES 3,A       2         2      Z N H -
        CASE(0xA0, RES(4, B))           // RES 4,B       2         2      Z N H -
        CASE(0xA1, RES(4, C))           // RES 4,C       2         2      Z N H -
        CASE(0xA2, RES(4, D))           // RES 4,D       2         2      Z N H -
        CASE(0xA3, RES(4, E))           // RES 4,E       2         2      Z N H -
        CASE(0xA4, RES(4, H))           // RES 4,H       2         2      Z N H -
        CASE(0xA5, RES(4, L))           // RES 4,L       2         2      Z N H -
        CASE(0xA6, RES(4, MEMORY))      // RES 4,(HL)    3         2      Z N H -
        CASE(0xA7, RES(4, A))           // RES 4,A       2         2      Z N H -
        CASE(0xA8, RES(5, B))           // RES 5,B       2         2      Z N H -
        CASE(0xA9, RES(5, C))           // RES 5,C       2         2      Z N H -
        CASE(0xAA, RES(5, D))           // RES 5,D       2         2      Z N H -
        CASE(0xAB, RES(5, E))           // RES 5,E       2         2      Z N H -
        CASE(0xAC, RES(5, H))           // RES 5,H       2         2      Z N H -
        CASE(0xAD, RES(5, L))           // RES 5,L       2         2      Z N H -
        CASE(0xAE, RES(5, MEMORY))      // RES 5,(HL)    3         2      Z N H -
        CASE(0xAF, RES(5, A))           // RES 5,A       2         2      Z N H -
        CASE(0xB0, RES(6, B))           // RES 6,B       2         2      Z N H -
        CASE(0xB1, RES(6, C))           // RES 6,C       2         2      Z N H -
        CASE(0xB2, RES(6, D))           // RES 6,D       2         2      Z N H -
        CASE(0xB3, RES(6, E))           // RES 6,E       2         2      Z N H -
        CASE(0xB4, RES(6, H))           // RES 6,H       2         2      Z N H -
        CASE(0xB5, RES(6, L))           // RES 6,L       2         2      Z N H -
        CASE(0xB6, RES(6, MEMORY))      // RES 6,(HL)    3         2      Z N H -
        CASE(0xB7, RES(6, A))           // RES 6,A       2         2      Z N H -
        CASE(0xB8, RES(7, B))           // RES 7,B       2         2      Z N H -
        CASE(0xB9, RES(7, C))           // RES 7,C       2         2      Z N H -
        CASE(0xBA, RES(7, D))           // RES 7,D       2         2      Z N H -
        CASE(0xBB, RES(7, E))           // RES 7,E       2         2      Z N H -
        CASE(0xBC, RES(7, H))           // RES 7,H       2         2      Z N H -
        CASE(0xBD, RES(7, L))           // RES 7,L       2         2      Z N H -
        CASE(0xBE, RES(7, MEMORY))      // RES 7,(HL)    3         2      Z N H -
        CASE(0xBF, RES(7, A))           // RES 7,A       2         2      Z N H -
    }
}
// clang-format on
