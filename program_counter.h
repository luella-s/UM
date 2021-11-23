#ifndef PROGRAM_COUNTER_H_
#define PROGRAM_COUNTER_H_

#include "stdint.h"
#include "memory.h"
#include "registers.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct Program_counter {
    uint32_t count;
}*Program_counter;

Program_counter counter_new();
Program_counter increment_counter(Program_counter pc);
Program_counter decrement_counter(Program_counter pc);
Program_counter set_counter(Program_counter pc, uint32_t val);
uint32_t get_counter(Program_counter pc);
void counter_free(Program_counter pc);

#endif