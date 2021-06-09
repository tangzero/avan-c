#include "cpu.h"
#include "instructions.h"
#include <stdlib.h>

#define A (cpu->a)
#define B ((cpu->bc >> 8) & 0x00FF)
#define set_b(cpu, value) cpu->bc |= (value << 8) & 0xFF00
#define C (cpu->bc & 0x00FF)
#define set_c(cpu, value) cpu->bc |= value & 0x00FF
#define D ((cpu->de >> 8) & 0x00FF)
#define set_d(cpu, value) cpu->de |= (value << 8) & 0xFF00
#define E (cpu->de & 0x00FF)
#define set_e(cpu, value) cpu->de |= value & 0x00FF
#define H ((cpu->hl >> 8) & 0x00FF)
#define set_h(cpu, value) cpu->hl |= (value << 8) & 0xFF00
#define L (cpu->hl & 0x00FF)
#define set_l(cpu, value) cpu->hl |= value & 0x00FF

#define HL cpu_read(cpu, cpu->hl)
#define U8 cpu_read_next_u8(cpu)

#define ADC(value) ADC(cpu, value)
#define ADD(value) ADD(cpu, value)
#define AND(value) AND(cpu, value)
#define CP(value) CP(cpu, value)

#define instruction(id, code)                                                                                          \
    case id: {                                                                                                         \
        code;                                                                                                          \
        break;                                                                                                         \
    }

CPU *cpu_new()
{
    return (CPU *)malloc(sizeof(CPU));
}

void cpu_destroy(CPU *cpu)
{
    free(cpu);
}

u8 cpu_read(CPU *cpu, u16 address)
{
    return 0x0000; // TODO: implement this
}

u8 cpu_read_next_u8(CPU *cpu)
{
    return 0x0000; // TODO: implement this
}

void cpu_execute(CPU *cpu, u8 opcode)
{
    switch (opcode)
    {
        instruction(0x80, ADD(B));  // ADD A, B
        instruction(0x81, ADD(C));  // ADD A, C
        instruction(0x82, ADD(D));  // ADD A, D
        instruction(0x83, ADD(E));  // ADD A, E
        instruction(0x84, ADD(H));  // ADD A, H
        instruction(0x85, ADD(L));  // ADD A, L
        instruction(0x86, ADD(HL)); // ADD A, (HL)
        instruction(0x87, ADD(A));  // ADD A, A
        instruction(0x88, ADC(B));  // ADC A, B
        instruction(0x89, ADC(C));  // ADC A, C
        instruction(0x8A, ADC(D));  // ADC A, D
        instruction(0x8B, ADC(E));  // ADC A, E
        instruction(0x8C, ADC(H));  // ADC A, H
        instruction(0x8D, ADC(L));  // ADC A, L
        instruction(0x8E, ADC(HL)); // ADC A, (HL)
        instruction(0x8F, ADC(A));  // ADC A, A
        instruction(0xA0, AND(B));  // AND A, B
        instruction(0xA1, AND(C));  // AND A, C
        instruction(0xA2, AND(D));  // AND A, D
        instruction(0xA3, AND(E));  // AND A, E
        instruction(0xA4, AND(H));  // AND A, H
        instruction(0xA5, AND(L));  // AND A, L
        instruction(0xA6, AND(HL)); // AND A, (HL)
        instruction(0xA7, AND(A));  // AND A, A
        instruction(0xB8, CP(B));   // CP A, B
        instruction(0xB9, CP(C));   // CP A, C
        instruction(0xBA, CP(D));   // CP A, D
        instruction(0xBB, CP(E));   // CP A, E
        instruction(0xBC, CP(H));   // CP A, H
        instruction(0xBD, CP(L));   // CP A, L
        instruction(0xBE, CP(HL));  // CP A, (HL)
        instruction(0xBF, CP(A));   // CP A, A
        instruction(0xC6, ADD(U8)); // ADD A, U8
        instruction(0xCE, ADC(U8)); // ADC A, U8
    }
}