#include "cpu.h"
#include <stdlib.h>
#include "instructions.h"

CPU *cpu_new() { return (CPU *)malloc(sizeof(CPU)); }

void cpu_destroy(CPU *cpu) { free(cpu); }

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
#define INC(x)  SET_##x(_inc(cpu, x))
#define DEC(x)  SET_##x(_dec(cpu, x))
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

void cpu_execute(CPU *cpu, u8 opcode) {
    switch (opcode) {
        // clang-format off
        CASE(0x04, INC(B))
        CASE(0x05, DEC(B))
        CASE(0x09, ADD16(BC))
        CASE(0x0C, INC(C))
        CASE(0x0D, DEC(C))
        CASE(0x14, INC(D))
        CASE(0x15, DEC(D))
        CASE(0x19, ADD16(DE))
        CASE(0x1C, INC(E))
        CASE(0x1D, DEC(E))
        CASE(0x24, INC(H))
        CASE(0x25, DEC(H))
        CASE(0x29, ADD16(HL))
        CASE(0x2C, INC(L))
        CASE(0x2D, DEC(L))
        CASE(0x34, INC(MEMORY))
        CASE(0x35, DEC(MEMORY))
        CASE(0x39, ADD16(SP))
        CASE(0x3C, INC(A))
        CASE(0x3D, DEC(A))
        CASE(0x80, ADD8(B))
        CASE(0x81, ADD8(C))
        CASE(0x82, ADD8(D))
        CASE(0x83, ADD8(E))
        CASE(0x84, ADD8(H))
        CASE(0x85, ADD8(L))
        CASE(0x86, ADD8(MEMORY))
        CASE(0x87, ADD8(A))
        CASE(0x88, ADC(B))
        CASE(0x89, ADC(C))
        CASE(0x8A, ADC(D))
        CASE(0x8B, ADC(E))
        CASE(0x8C, ADC(H))
        CASE(0x8D, ADC(L))
        CASE(0x8E, ADC(MEMORY))
        CASE(0x8F, ADC(A))
        CASE(0x90, SUB(B))
        CASE(0x91, SUB(C))
        CASE(0x92, SUB(D))
        CASE(0x93, SUB(E))
        CASE(0x94, SUB(H))
        CASE(0x95, SUB(L))
        CASE(0x96, SUB(MEMORY))
        CASE(0x97, SUB(A))
        CASE(0x98, SBC(B))
        CASE(0x99, SBC(C))
        CASE(0x9A, SBC(D))
        CASE(0x9B, SBC(E))
        CASE(0x9C, SBC(H))
        CASE(0x9D, SBC(L))
        CASE(0x9E, SBC(MEMORY))
        CASE(0x9F, SBC(A))
        CASE(0xA0, AND(B))
        CASE(0xA1, AND(C))
        CASE(0xA2, AND(D))
        CASE(0xA3, AND(E))
        CASE(0xA4, AND(H))
        CASE(0xA5, AND(L))
        CASE(0xA6, AND(MEMORY))
        CASE(0xA7, AND(A))
        CASE(0xA8, XOR(B))
        CASE(0xA9, XOR(C))
        CASE(0xAA, XOR(D))
        CASE(0xAB, XOR(E))
        CASE(0xAC, XOR(H))
        CASE(0xAD, XOR(L))
        CASE(0xAE, XOR(MEMORY))
        CASE(0xAF, XOR(A))
        CASE(0xB0, OR(B))
        CASE(0xB1, OR(C))
        CASE(0xB2, OR(D))
        CASE(0xB3, OR(E))
        CASE(0xB4, OR(H))
        CASE(0xB5, OR(L))
        CASE(0xB6, OR(MEMORY))
        CASE(0xB7, OR(A))
        CASE(0xB8, CP(B))
        CASE(0xB9, CP(C))
        CASE(0xBA, CP(D))
        CASE(0xBB, CP(E))
        CASE(0xBC, CP(H))
        CASE(0xBD, CP(L))
        CASE(0xBE, CP(MEMORY))
        CASE(0xBF, CP(A))
        CASE(0xC6, ADD8(NEXT_BYTE))
        CASE(0xCE, ADC(NEXT_BYTE))
        default: exit(404);
            // clang-format on
    }
}
