#include "cpu.h"
#include <stdlib.h>

CPU *new_gameboy_cpu()
{
    return (CPU *)malloc(sizeof(CPU));
}

void destroy_gameboy_cpu(CPU *cpu)
{
    free(cpu);
}
