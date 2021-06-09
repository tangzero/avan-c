#include "cpu.h"
#include "instructions.h"
#include <stdlib.h>

#define A  cpu->a
#define B  ((cpu->bc >> 8) & 0x00FF)
#define C  (cpu->bc & 0x00FF)
#define D  ((cpu->de >> 8) & 0x00FF)
#define E  (cpu->de & 0x00FF)
#define H  ((cpu->hl >> 8) & 0x00FF)
#define L  (cpu->hl & 0x00FF)
#define HL cpu_read(cpu, cpu->hl)
#define U8 cpu_read_next_u8(cpu)

#define set_A(value)  cpu->a = value
#define set_B(value)  cpu->bc |= (value << 8) & 0xFF00
#define set_C(value)  cpu->bc |= value & 0x00FF
#define set_D(value)  cpu->de |= (value << 8) & 0xFF00
#define set_E(value)  cpu->de |= value & 0x00FF
#define set_H(value)  cpu->hl |= (value << 8) & 0xFF00
#define set_L(value)  cpu->hl |= value & 0x00FF
#define set_HL(value) cpu_write(cpu, cpu->hl, value)

#define ADC(value) ADC(cpu, value)
#define ADD(value) ADD(cpu, value)
#define AND(value) AND(cpu, value)
#define CP(value)  CP(cpu, value)
#define INC(value) set_##value(INC(cpu, value))
#define DEC(value) set_##value(DEC(cpu, value))

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

void cpu_write(CPU *cpu, u16 address, u8 value)
{
    // TODO: implement this
}

void cpu_execute(CPU *cpu, u8 opcode)
{
    switch (opcode)
    {
        // clang-format off
        instruction(0x04, INC(B))
        instruction(0x05, DEC(B))
        instruction(0x0C, INC(C))
        instruction(0x0D, DEC(C))
        instruction(0x14, INC(D))
        instruction(0x15, DEC(D))
        instruction(0x1C, INC(E))
        instruction(0x1D, DEC(E))
        instruction(0x24, INC(H))
        instruction(0x25, DEC(H))
        instruction(0x2C, INC(L))
        instruction(0x2D, DEC(L))
        instruction(0x34, INC(HL))
        instruction(0x35, DEC(HL))
        instruction(0x3C, INC(A))
        instruction(0x3D, DEC(A))
        instruction(0x80, ADD(B))
        instruction(0x81, ADD(C))
        instruction(0x82, ADD(D))
        instruction(0x83, ADD(E))
        instruction(0x84, ADD(H))
        instruction(0x85, ADD(L))
        instruction(0x86, ADD(HL))
        instruction(0x87, ADD(A))
        instruction(0x88, ADC(B))
        instruction(0x89, ADC(C))
        instruction(0x8A, ADC(D))
        instruction(0x8B, ADC(E))
        instruction(0x8C, ADC(H))
        instruction(0x8D, ADC(L))
        instruction(0x8E, ADC(HL))
        instruction(0x8F, ADC(A))
        instruction(0xA0, AND(B))
        instruction(0xA1, AND(C))
        instruction(0xA2, AND(D))
        instruction(0xA3, AND(E))
        instruction(0xA4, AND(H))
        instruction(0xA5, AND(L))
        instruction(0xA6, AND(HL))
        instruction(0xA7, AND(A))
        instruction(0xB8, CP(B))
        instruction(0xB9, CP(C))
        instruction(0xBA, CP(D))
        instruction(0xBB, CP(E))
        instruction(0xBC, CP(H))
        instruction(0xBD, CP(L))
        instruction(0xBE, CP(HL))
        instruction(0xBF, CP(A))
        instruction(0xC6, ADD(U8))
        instruction(0xCE, ADC(U8))
        // clang-format on
    }
}