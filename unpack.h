/**************************************************************
  *
  *                     unpack.h
  *
  *     Assignment: COMP40 Homework 6 - UM
  *     Authors:  Luella Sugiman (lsugim01), Unnathy Nellutla (unellu01)
  *     Date:     11/24/21
  *
  *     Interface of Unpack module - defines public functions that
  *     unpacks a 32-bit UM instruction into its constituent components.
  *
  **************************************************************/
  
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

/*
  * Unpacked struct:
     Operation code,
     UM register a,
     UM register b,
     UM register c,
     word value.
  */
typedef struct Unpacked {
    Um_opcode op;
    Um_register ra;
    Um_register rb;
    Um_register rc;
    uint32_t value;
} Unpacked;

/*
  * Arguments: 
     32-bit word to unpack.
  * Purpose: unpacks UM instruction into its op code, UM register IDs and value.
  * Returns: pointer to Unpacked struct containing unpacked components
*/
  
Unpacked *unpack(uint32_t word);

#endif