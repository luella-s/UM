#ifndef UM_H_
#define UM_H_

#include "registers.h"
#include "memory.h"
#include "unpack.h"
#include "read_file.h"
#include "instructions.h"
<<<<<<< HEAD
=======
#include "program_counter.h"
>>>>>>> 86e2dbe488427b3d44c65fedec351b350d99f077
#include "um-dis.h"
#include <stdio.h>

void run_program(Memory mem, Registers reg, uint32_t *pc);
void execute(Memory mem, Registers reg, Unpacked *u, uint32_t *pc);

int main(int argc, char *argv[])
{
    (void)argc;

    Memory mem = memory_new();
    Registers reg = registers_new();
<<<<<<< HEAD
=======
    uint32_t *pc = malloc(sizeof(*pc));
    *pc = 0;
>>>>>>> 86e2dbe488427b3d44c65fedec351b350d99f077

    /* Read file into 0 segment */
    read_file(mem, argv[1]);

    /* Initialize program counter */
<<<<<<< HEAD
    uint32_t *pc = malloc(sizeof(*pc));
    *pc = 0;
=======
>>>>>>> 86e2dbe488427b3d44c65fedec351b350d99f077

    /* Run program */
    run_program(mem, reg, pc);

    /* Deallocate memory */
    memory_free(mem);
    registers_free(reg);
    free(pc);

    return EXIT_SUCCESS;
}

void run_program(Memory mem, Registers reg, uint32_t *pc)
{
    while (*pc < get_length_segment(mem, 0)) {
        uint32_t word = get_word(mem, 0, *pc);
        Unpacked *u = unpack(word);
        *pc += 1;
        execute(mem, reg, u, pc);
        free(u);
    }
}

void execute(Memory mem, Registers reg, Unpacked *u, uint32_t *pc)
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
        halt(mem, reg, pc, u);
    } else if (u->op == ACTIVATE) {
        map_segment(mem, reg, u->rb, u->rc);
    } else if (u->op == INACTIVATE) {
        unmap_segment(mem, reg, u->rc);
    } else if (u->op == OUT) {
        output(reg, u->rc);
    } else if (u->op == IN) {
        input(reg, u->rc);
    } else if (u->op == LOADP) {
        *pc = load_program(mem, reg, u->rb, u->rc);
    } else if (u->op == LV) {
        load_value(reg, u->ra, u->value);
    }
}

#endif