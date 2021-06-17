#include "cpu.h"
#include "instructions.h"
#include <memory.h>
#include <stdlib.h>

CPU *cpu_new() {
    CPU *cpu = (CPU *)malloc(sizeof(CPU));
    memset(cpu, 0, sizeof(CPU)); // clear all the junk this memory section could have
    return cpu;
}

void cpu_destroy(CPU *cpu) {
    free(cpu);
}

u8 cpu_read(CPU *cpu, u16 address) {
    return 0x0000; // TODO: implement this
}

u8 cpu_read_next_byte(CPU *cpu) {
    return 0x0000; // TODO: implement this
}

void cpu_write(CPU *cpu, u16 address, u8 value) {
    // TODO: implement this
}

#define EXECUTE_CB cpu_execute_cb(cpu, cpu_read_next_byte(cpu))

#define CASE(id, instruction)                                                                                          \
    case id: {                                                                                                         \
        instruction;                                                                                                   \
        break;                                                                                                         \
    }

// clang-format off
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
        CASE(0x86, RES(0, MEMORY))      // RES 0,(HL)    4         2      Z N H -
        CASE(0x87, RES(0, A))           // RES 0,A       2         2      Z N H -
        CASE(0x88, RES(1, B))           // RES 1,B       2         2      Z N H -
        CASE(0x89, RES(1, C))           // RES 1,C       2         2      Z N H -
        CASE(0x8A, RES(1, D))           // RES 1,D       2         2      Z N H -
        CASE(0x8B, RES(1, E))           // RES 1,E       2         2      Z N H -
        CASE(0x8C, RES(1, H))           // RES 1,H       2         2      Z N H -
        CASE(0x8D, RES(1, L))           // RES 1,L       2         2      Z N H -
        CASE(0x8E, RES(1, MEMORY))      // RES 1,(HL)    4         2      Z N H -
        CASE(0x8F, RES(1, A))           // RES 1,A       2         2      Z N H -
        CASE(0x90, RES(2, B))           // RES 2,B       2         2      Z N H -
        CASE(0x91, RES(2, C))           // RES 2,C       2         2      Z N H -
        CASE(0x92, RES(2, D))           // RES 2,D       2         2      Z N H -
        CASE(0x93, RES(2, E))           // RES 2,E       2         2      Z N H -
        CASE(0x94, RES(2, H))           // RES 2,H       2         2      Z N H -
        CASE(0x95, RES(2, L))           // RES 2,L       2         2      Z N H -
        CASE(0x96, RES(2, MEMORY))      // RES 2,(HL)    4         2      Z N H -
        CASE(0x97, RES(2, A))           // RES 2,A       2         2      Z N H -
        CASE(0x98, RES(3, B))           // RES 3,B       2         2      Z N H -
        CASE(0x99, RES(3, C))           // RES 3,C       2         2      Z N H -
        CASE(0x9A, RES(3, D))           // RES 3,D       2         2      Z N H -
        CASE(0x9B, RES(3, E))           // RES 3,E       2         2      Z N H -
        CASE(0x9C, RES(3, H))           // RES 3,H       2         2      Z N H -
        CASE(0x9D, RES(3, L))           // RES 3,L       2         2      Z N H -
        CASE(0x9E, RES(3, MEMORY))      // RES 3,(HL)    4         2      Z N H -
        CASE(0x9F, RES(3, A))           // RES 3,A       2         2      Z N H -
        CASE(0xA0, RES(4, B))           // RES 4,B       2         2      Z N H -
        CASE(0xA1, RES(4, C))           // RES 4,C       2         2      Z N H -
        CASE(0xA2, RES(4, D))           // RES 4,D       2         2      Z N H -
        CASE(0xA3, RES(4, E))           // RES 4,E       2         2      Z N H -
        CASE(0xA4, RES(4, H))           // RES 4,H       2         2      Z N H -
        CASE(0xA5, RES(4, L))           // RES 4,L       2         2      Z N H -
        CASE(0xA6, RES(4, MEMORY))      // RES 4,(HL)    4         2      Z N H -
        CASE(0xA7, RES(4, A))           // RES 4,A       2         2      Z N H -
        CASE(0xA8, RES(5, B))           // RES 5,B       2         2      Z N H -
        CASE(0xA9, RES(5, C))           // RES 5,C       2         2      Z N H -
        CASE(0xAA, RES(5, D))           // RES 5,D       2         2      Z N H -
        CASE(0xAB, RES(5, E))           // RES 5,E       2         2      Z N H -
        CASE(0xAC, RES(5, H))           // RES 5,H       2         2      Z N H -
        CASE(0xAD, RES(5, L))           // RES 5,L       2         2      Z N H -
        CASE(0xAE, RES(5, MEMORY))      // RES 5,(HL)    4         2      Z N H -
        CASE(0xAF, RES(5, A))           // RES 5,A       2         2      Z N H -
        CASE(0xB0, RES(6, B))           // RES 6,B       2         2      Z N H -
        CASE(0xB1, RES(6, C))           // RES 6,C       2         2      Z N H -
        CASE(0xB2, RES(6, D))           // RES 6,D       2         2      Z N H -
        CASE(0xB3, RES(6, E))           // RES 6,E       2         2      Z N H -
        CASE(0xB4, RES(6, H))           // RES 6,H       2         2      Z N H -
        CASE(0xB5, RES(6, L))           // RES 6,L       2         2      Z N H -
        CASE(0xB6, RES(6, MEMORY))      // RES 6,(HL)    4         2      Z N H -
        CASE(0xB7, RES(6, A))           // RES 6,A       2         2      Z N H -
        CASE(0xB8, RES(7, B))           // RES 7,B       2         2      Z N H -
        CASE(0xB9, RES(7, C))           // RES 7,C       2         2      Z N H -
        CASE(0xBA, RES(7, D))           // RES 7,D       2         2      Z N H -
        CASE(0xBB, RES(7, E))           // RES 7,E       2         2      Z N H -
        CASE(0xBC, RES(7, H))           // RES 7,H       2         2      Z N H -
        CASE(0xBD, RES(7, L))           // RES 7,L       2         2      Z N H -
        CASE(0xBE, RES(7, MEMORY))      // RES 7,(HL)    4         2      Z N H -
        CASE(0xBF, RES(7, A))           // RES 7,A       2         2      Z N H -
        CASE(0xC0, SET(0, B))           // SET 0,B       2         2      Z N H -
        CASE(0xC1, SET(0, C))           // SET 0,C       2         2      Z N H -
        CASE(0xC2, SET(0, D))           // SET 0,D       2         2      Z N H -
        CASE(0xC3, SET(0, E))           // SET 0,E       2         2      Z N H -
        CASE(0xC4, SET(0, H))           // SET 0,H       2         2      Z N H -
        CASE(0xC5, SET(0, L))           // SET 0,L       2         2      Z N H -
        CASE(0xC6, SET(0, MEMORY))      // SET 0,(HL)    4         2      Z N H -
        CASE(0xC7, SET(0, A))           // SET 0,A       2         2      Z N H -
        CASE(0xC8, SET(1, B))           // SET 1,B       2         2      Z N H -
        CASE(0xC9, SET(1, C))           // SET 1,C       2         2      Z N H -
        CASE(0xCA, SET(1, D))           // SET 1,D       2         2      Z N H -
        CASE(0xCB, SET(1, E))           // SET 1,E       2         2      Z N H -
        CASE(0xCC, SET(1, H))           // SET 1,H       2         2      Z N H -
        CASE(0xCD, SET(1, L))           // SET 1,L       2         2      Z N H -
        CASE(0xCE, SET(1, MEMORY))      // SET 1,(HL)    4         2      Z N H -
        CASE(0xCF, SET(1, A))           // SET 1,A       2         2      Z N H -
        CASE(0xD0, SET(2, B))           // SET 2,B       2         2      Z N H -
        CASE(0xD1, SET(2, C))           // SET 2,C       2         2      Z N H -
        CASE(0xD2, SET(2, D))           // SET 2,D       2         2      Z N H -
        CASE(0xD3, SET(2, E))           // SET 2,E       2         2      Z N H -
        CASE(0xD4, SET(2, H))           // SET 2,H       2         2      Z N H -
        CASE(0xD5, SET(2, L))           // SET 2,L       2         2      Z N H -
        CASE(0xD6, SET(2, MEMORY))      // SET 2,(HL)    4         2      Z N H -
        CASE(0xD7, SET(2, A))           // SET 2,A       2         2      Z N H -
        CASE(0xD8, SET(3, B))           // SET 3,B       2         2      Z N H -
        CASE(0xD9, SET(3, C))           // SET 3,C       2         2      Z N H -
        CASE(0xDA, SET(3, D))           // SET 3,D       2         2      Z N H -
        CASE(0xDB, SET(3, E))           // SET 3,E       2         2      Z N H -
        CASE(0xDC, SET(3, H))           // SET 3,H       2         2      Z N H -
        CASE(0xDD, SET(3, L))           // SET 3,L       2         2      Z N H -
        CASE(0xDE, SET(3, MEMORY))      // SET 3,(HL)    4         2      Z N H -
        CASE(0xDF, SET(3, A))           // SET 3,A       2         2      Z N H -
        CASE(0xE0, SET(4, B))           // SET 4,B       2         2      Z N H -
        CASE(0xE1, SET(4, C))           // SET 4,C       2         2      Z N H -
        CASE(0xE2, SET(4, D))           // SET 4,D       2         2      Z N H -
        CASE(0xE3, SET(4, E))           // SET 4,E       2         2      Z N H -
        CASE(0xE4, SET(4, H))           // SET 4,H       2         2      Z N H -
        CASE(0xE5, SET(4, L))           // SET 4,L       2         2      Z N H -
        CASE(0xE6, SET(4, MEMORY))      // SET 4,(HL)    4         2      Z N H -
        CASE(0xE7, SET(4, A))           // SET 4,A       2         2      Z N H -
        CASE(0xE8, SET(5, B))           // SET 5,B       2         2      Z N H -
        CASE(0xE9, SET(5, C))           // SET 5,C       2         2      Z N H -
        CASE(0xEA, SET(5, D))           // SET 5,D       2         2      Z N H -
        CASE(0xEB, SET(5, E))           // SET 5,E       2         2      Z N H -
        CASE(0xEC, SET(5, H))           // SET 5,H       2         2      Z N H -
        CASE(0xED, SET(5, L))           // SET 5,L       2         2      Z N H -
        CASE(0xEE, SET(5, MEMORY))      // SET 5,(HL)    4         2      Z N H -
        CASE(0xEF, SET(5, A))           // SET 5,A       2         2      Z N H -
        CASE(0xF0, SET(6, B))           // SET 6,B       2         2      Z N H -
        CASE(0xF1, SET(6, C))           // SET 6,C       2         2      Z N H -
        CASE(0xF2, SET(6, D))           // SET 6,D       2         2      Z N H -
        CASE(0xF3, SET(6, E))           // SET 6,E       2         2      Z N H -
        CASE(0xF4, SET(6, H))           // SET 6,H       2         2      Z N H -
        CASE(0xF5, SET(6, L))           // SET 6,L       2         2      Z N H -
        CASE(0xF6, SET(6, MEMORY))      // SET 6,(HL)    4         2      Z N H -
        CASE(0xF7, SET(6, A))           // SET 6,A       2         2      Z N H -
        CASE(0xF8, SET(7, B))           // SET 7,B       2         2      Z N H -
        CASE(0xF9, SET(7, C))           // SET 7,C       2         2      Z N H -
        CASE(0xFA, SET(7, D))           // SET 7,D       2         2      Z N H -
        CASE(0xFB, SET(7, E))           // SET 7,E       2         2      Z N H -
        CASE(0xFC, SET(7, H))           // SET 7,H       2         2      Z N H -
        CASE(0xFD, SET(7, L))           // SET 7,L       2         2      Z N H -
        CASE(0xFE, SET(7, MEMORY))      // SET 7,(HL)    4         2      Z N H -
        CASE(0xFF, SET(7, A))           // SET 7,A       2         2      Z N H -
    }
}

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
        CASE(0xCB, EXECUTE_CB)          // execute instructions prefixed with 0xCB
        CASE(0xC6, ADD8(BYTE))          // ADD A,n8      2         2      Z N H C
        CASE(0xCE, ADC(BYTE))           // ADC A,n8      2         2      Z N H C
        default: exit(404);
    }
}
// clang-format on
