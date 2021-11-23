#ifndef UM_H_
#define UM_H_

#include "registers.h"
#include "memory.h"
#include "unpack.h"
#include "read_file.h"
#include "instructions.h"
#include "program_counter.h"
#include <stdio.h>

void run_program(Memory mem, Registers reg, Program_counter pc);
void execute(Memory mem, Registers reg, Unpacked *u, Program_counter pc);

int main(int argc, char *argv[])
{
    (void)argc;

    Memory mem = memory_new();
    Registers reg = registers_new();
    Program_counter pc = counter_new();

    /* Read file into 0 segment */
    read_file(mem, argv[1]);

    /* Initialize program counter */
    set_counter(pc, 0);

    /* Run program */
    run_program(mem, reg, pc);

    /* Deallocate memory */
    memory_free(mem);
    registers_free(reg);
    counter_free(pc);

    return EXIT_SUCCESS;
}

void run_program(Memory mem, Registers reg, Program_counter pc)
{
    while (get_counter(pc) < get_length_segment(mem, 0)) {
        uint32_t word = get_word(mem, 0, get_counter(pc));
        Unpacked *u = unpack(word);
        execute(mem, reg, u, pc);
        free(u);
        pc = increment_counter(pc);
    }
}

void execute(Memory mem, Registers reg, Unpacked *u, Program_counter pc)
{
    if (u->op == CMOV) {
        conditional_move(reg, u->ra, u->rb, u->rc);

    } else if (u->op == SLOAD) {
        segmented_load(mem, reg, u->ra, u->rb, u->rc);
        
    } else if (u->op == SSTORE) {
        segmented_store(mem, reg, u->ra, u->rb, u->rc);
        
    } else if (u->op == ADD) {
        addition(reg, u->ra, u->rb, u->rc);
        
    } else if (u->op == MUL) {
        multiplication(reg, u->ra, u->rb, u->rc);
        
    } else if (u->op == DIV) {
        division(reg, u->ra, u->rb, u->rc);
        
    } else if (u->op == NAND) {
        bitwise_nand(reg, u->ra, u->rb, u->rc);
        
    } else if (u->op == HALT) {
        halt(mem, reg);
        
    } else if (u->op == ACTIVATE) {
        map_segment(mem, reg, u->rb, u->rc);
        
    } else if (u->op == INACTIVATE) {
        unmap_segment(mem, reg, u->rc);
        
    } else if (u->op == OUT) {
        output(reg, u->rc);
        
    } else if (u->op == IN) {
        input(reg, u->rc);
        
    } else if (u->op == LOADP) {
        load_program(mem, reg, pc, u->rb, u->rc);
        pc = decrement_counter(pc);
        
        
    } else if (u->op == LV) {
        load_value(reg, u->ra, u->value);
    }
}

#endif