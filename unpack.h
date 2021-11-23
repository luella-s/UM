#ifndef UNPACK_H_
#define UNPACK_H_

#include "stdint.h"
#include "registers.h"
#include <assert.h>
#include <stdlib.h>
#include <bitpack.h>

typedef enum Um_opcode {
    CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
    NAND, HALT, ACTIVATE, INACTIVATE, OUT, IN, LOADP, LV
} Um_opcode;

typedef struct Unpacked {
    Um_opcode op;
    Um_register ra;
    Um_register rb;
    Um_register rc;
    uint32_t value;
} Unpacked;

Unpacked *unpack(uint32_t word);

#endif