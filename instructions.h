#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

#include "seq.h"
#include "uarray.h"
#include "stdint.h"
#include "registers.h"
#include "memory.h"
#include "program_counter.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void conditional_move(Registers reg, Um_register ra, Um_register rb, Um_register rc); 
void segmented_load(Memory mem, Registers reg, Um_register ra, Um_register rb, Um_register rc);
void segmented_store(Memory mem, Registers reg, Um_register ra, Um_register rb, Um_register rc);
void addition(Registers reg, Um_register ra, Um_register rb, Um_register rc);
void multiplication(Registers reg, Um_register ra, Um_register rb, Um_register rc);
void division(Registers reg, Um_register ra, Um_register rb, Um_register rc);
void bitwise_nand(Registers reg, Um_register ra, Um_register rb, Um_register rc);
void halt(Memory mem, Registers reg);
void map_segment(Memory mem, Registers reg, Um_register rb, Um_register rc);
void unmap_segment(Memory mem, Registers reg, Um_register rc);
void output(Registers reg, Um_register rc);
void input(Registers reg, Um_register rc);
uint32_t load_program(Memory mem, Registers reg, Um_register rb, Um_register rc);
void load_value(Registers reg, Um_register ra, uint32_t value);

#endif