#include "program_counter.h"

Program_counter counter_new()
{
    Program_counter pc = malloc(sizeof(*pc));
    pc->count = 0;
    return pc;
}

Program_counter increment_counter(Program_counter pc)
{
    pc->count += 1;
    return pc;
}

Program_counter set_counter(Program_counter pc, uint32_t val)
{
    pc->count = val;
    return pc;
}

uint32_t get_counter(Program_counter pc)
{
    return pc->count;
}

void counter_free(Program_counter pc)
{
    free(pc);
}