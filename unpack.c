#include "unpack.h"
#include <stdio.h> //FOR TESTING

#define OP_BITS 4
#define REG_BITS 3

/* Helper functions */
Unpacked *unpack_rest(uint32_t word);
Unpacked *unpack_loadval(uint32_t word);
void validate_op(Um_opcode op);
static inline void validate_reg(Um_register reg);

Unpacked *unpack(uint32_t word)
{
    if (Bitpack_getu(word, OP_BITS, 32 - OP_BITS) == LV) {
        return unpack_loadval(word);
    }
    return unpack_rest(word);
}

Unpacked *unpack_rest(uint32_t word)
{
    Unpacked *u = malloc(sizeof(*u));
    assert(u != NULL);

    u->op = Bitpack_getu(word, OP_BITS, 32 - OP_BITS);
    validate_op(u->op);

    u->ra = Bitpack_getu(word, REG_BITS, REG_BITS * 2);
    u->rb = Bitpack_getu(word, REG_BITS, REG_BITS);
    u->rc = Bitpack_getu(word, REG_BITS, 0);

    validate_reg(u->ra);
    validate_reg(u->rb);
    validate_reg(u->rc);

    return u;
}

Unpacked *unpack_loadval(uint32_t word)
{
    Unpacked *u = malloc(sizeof(*u));
    assert(u != NULL);

    u->op = LV;
    u->ra = Bitpack_getu(word, REG_BITS, 32 - OP_BITS - REG_BITS);
    u->value = (uint32_t) Bitpack_getu(word, 32 - OP_BITS - REG_BITS, 0);
    validate_reg(u->ra);

    return u;
}

void validate_op(Um_opcode op)
{
    assert(op >= 0 && op <= 13);
}

void validate_reg(Um_register reg)
{
    assert(reg >= 0 && reg <= 7);
}