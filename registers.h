/**************************************************************
 *
 *                     registers.h
 *
 *     Assignment: COMP40 Homework 6 - UM
 *     Authors:  Luella Sugiman (lsugim01), Unnathy Nellutla (unellu01)
 *     Date:     11/24/21
 *
 *     Interface of Registers module - defines public functions of the
 *     8 32-bit registers data structure.
 *
 **************************************************************/

#ifndef REGISTERS_H_
#define REGISTERS_H_

#include "uarray.h"
#include "stdint.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef enum Um_register { r0 = 0, r1, r2, r3, r4, r5, r6, r7 } Um_register;
typedef struct Registers *Registers;

/*
 * Arguments: N/A
 * Purpose: instantiates Registers.
 * Returns: Registers object.
 */
Registers registers_new();

/*
 * Arguments: 
    Registers object,
    Register ID to set,
    word to set register to.
 * Purpose: sets register of indicated ID to the word value.
 * Returns: void
 */
void set_register(Registers res, Um_register rg, uint32_t word);

/*
 * Arguments: 
    Registers object,
    Register ID to read from.
 * Purpose: gets the value at the register of indicated ID.
 * Returns: word in the register.
 */
uint32_t get_register(Registers res, Um_register rg);

/*
 * Arguments: 
    Registers object.
 * Purpose: deallocates memory of Registers.
 * Returns: void
 */
void registers_free(Registers res);

#endif
