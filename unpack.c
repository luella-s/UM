/**************************************************************
 *
 *                     unpack.c
 *
 *     Assignment: COMP40 Homework 6 - UM
 *     Authors:  Luella Sugiman (lsugim01), Unnathy Nellutla (unellu01)
 *     Date:     11/24/21
 *
 *     Implementation of Instructions module - implements functions
 *     that unpacks a 32-bit UM instruction into its constituent components.
 *
 **************************************************************/

#include "unpack.h"

#define OP_BITS 4
#define REG_BITS 3

/* Helper functions */
Unpacked *unpack_rest(uint32_t word);
Unpacked *unpack_loadval(uint32_t word);
void validate_op(Um_opcode op);
static inline void validate_reg(Um_register reg);

/*
 * Arguments: 
    32-bit word to unpack.
 * Purpose: unpacks UM instruction into its op code, UM register IDs and value.
 * Returns: pointer to Unpacked struct containing unpacked components
 */
Unpacked *unpack(uint32_t word)
{
    if (Bitpack_getu(word, OP_BITS, 32 - OP_BITS) == LV) {
        return unpack_loadval(word);
    }
    return unpack_rest(word);
}

/*
 * Arguments: 
    32-bit word to unpack.
 * Purpose: unpacks UM instruction into its op code and 3 UM register IDs.
 * Fails:
    when memory allocation fails,
    when UM instruction contract is violated (invalid op code or register ID).
 * Returns: pointer to Unpacked struct containing unpacked components
 */
Unpacked *unpack_rest(uint32_t word)
{
    Unpacked *u = malloc(sizeof(*u));
    assert(u != NULL);

    /* Unpack & validate op code */
    u->op = Bitpack_getu(word, OP_BITS, 32 - OP_BITS);
    validate_op(u->op);

    /* Unpack & validate UM register IDs */
    u->ra = Bitpack_getu(word, REG_BITS, REG_BITS * 2);
    u->rb = Bitpack_getu(word, REG_BITS, REG_BITS);
    u->rc = Bitpack_getu(word, REG_BITS, 0);

    validate_reg(u->ra);
    validate_reg(u->rb);
    validate_reg(u->rc);

    return u;
}

/*
 * Arguments: 
    32-bit word to unpack.
 * Purpose: unpacks UM instruction into its op code, UM register ID and value.
 * Fails:
    when memory allocation fails,
    when UM instruction contract is violated (invalid op code or register ID).
 * Returns: pointer to Unpacked struct containing unpacked components
 */
Unpacked *unpack_loadval(uint32_t word)
{
    Unpacked *u = malloc(sizeof(*u));
    assert(u != NULL);

    /* Unpack & validate op code & register ID */
    u->op = LV;
    u->ra = Bitpack_getu(word, REG_BITS, 32 - OP_BITS - REG_BITS);
    u->value = (uint32_t) Bitpack_getu(word, 32 - OP_BITS - REG_BITS, 0);
    validate_reg(u->ra);

    return u;
}

/*
 * Arguments: 
    op code to validate
 * Purpose: validates op code is in the range of UM instruction codes.
 * Fails:
    when op code is not valid.
 * Returns: void.
 */
void validate_op(Um_opcode op)
{
    assert(op >= 0 && op <= 13);
}

/*
 * Arguments: 
    register ID to validate
 * Purpose: validates register ID is in the range of register IDs.
 * Fails:
    when register ID is not valid.
 * Returns: void.
 */
void validate_reg(Um_register reg)
{
    assert(reg >= 0 && reg <= 7);
}