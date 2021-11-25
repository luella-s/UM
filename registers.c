/**************************************************************
 *
 *                     registers.c
 *
 *     Assignment: COMP40 Homework 6 - UM
 *     Authors:  Luella Sugiman (lsugim01), Unnathy Nellutla (unellu01)
 *     Date:     11/24/21
 *
 *     Implementation of Memory module - implements the 8 32-bit registers
 *     data structure.
 *
 **************************************************************/

#include "registers.h"

/* Helper functions */
static inline void validate_reg(Um_register reg);

/*
 * Registers struct:
    UArray of size 8 representing 8 registers, each containing 32-bit words
 */
struct Registers {
    UArray_T arr;
};

/*
 * Arguments: N/A
 * Purpose: instantiates Registers
 * Fails:
   when memory allocation fails.
 * Returns: incomplete pointer to Registers struct
 */
Registers registers_new()
{
   Registers res = malloc(sizeof(*res));
   assert(res != NULL);
   res->arr = UArray_new(8, sizeof(uint32_t));
   assert(res->arr != NULL);

   return res;
}

/*
 * Arguments: 
    Registers object,
    Register ID to set,
    32-bit word to set register to.
 * Purpose: sets register of indicated ID to the word value.
 * Fails:
    when res is NULL,
    when register ID is out of bounds.
 * Returns: void
 */
void set_register(Registers res, Um_register rg, uint32_t word)
{
    assert(res != NULL);
    validate_reg(rg);
    //fprintf(stderr, "Storing: %u \n", word);
    *((uint32_t *)UArray_at(res->arr, rg)) = word;
}

/*
 * Arguments: 
    Registers object,
    Register ID to read from.
 * Purpose: gets the value at the register of indicated ID
 * Fails:
    when res is NULL,
    when register ID is out of bounds.
 * Returns: 32-bit word in the register.
 */
uint32_t get_register(Registers res, Um_register rg)
{
    assert(res != NULL);
    validate_reg(rg);
    return *((uint32_t *)UArray_at(res->arr, rg));
}

/*
 * Arguments: 
    Registers object.
 * Purpose: deallocates memory of Registers.
 * Fails:
    when res is NULL,
    when any variables in res are NULL.
 * Returns: void
 */
void registers_free(Registers res){
    assert(res != NULL);
    assert(res->arr != NULL);
    UArray_free(&(res->arr));
    free(res);
}

/*
 * Arguments: 
    register ID.
 * Purpose: validates register ID (ensures it's between 0 and 7).
 * Fails:
    when register ID is out of bounds.
 * Returns: void
 */
void validate_reg(Um_register reg)
{
    assert(reg >= 0 && reg <= 7);
}
