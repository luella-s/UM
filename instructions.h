/**************************************************************
  *
  *                     instructions.h
  *
  *     Assignment: COMP40 Homework 6 - UM
  *     Authors:  Luella Sugiman (lsugim01), Unnathy Nellutla (unellu01)
  *     Date:     11/24/21
  *
  *     Interface of Instructions module - defines public functions that
  *     execute UM instructions.
  *
  **************************************************************/
  
#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

#include "seq.h"
#include "uarray.h"
#include "stdint.h"
#include "registers.h"
#include "memory.h"
#include "unpack.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/*
  * Arguments: 
     Registers object,
     3 UM register IDs.
  * Purpose: executes the conditional move instruction - if rc != 0,
     sets ra to rb.
  * Fails:
     when reg is NULL,
     when register IDs are invalid.
  * Returns: void.
  */
void conditional_move(Registers reg, Um_register ra, \
     Um_register rb, Um_register rc); 
 /*
   * Arguments: 
      Memory object,
      Registers object,
      3 UM register IDs.
   * Purpose: executes the segmented laod instruction - loads $m[rb][rc]
      into ra.
   * Fails:
      when mem is NULL,
      when reg is NULL,
      when register IDs are invalid.
   * Returns: void.
   */
void segmented_load(Memory mem, Registers reg, Um_register ra,\
     Um_register rb, Um_register rc);
 /*
   * Arguments: 
      Memory object,
      Registers object,
      3 UM register IDs.
   * Purpose: executes the segmented store instruction - loads value rc into
      $m[ra][rb].
   * Fails:
      when mem is NULL,
      when reg is NULL,
      when register IDs are invalid.
   * Returns: void.
   */
void segmented_store(Memory mem, Registers reg, Um_register ra,\
     Um_register rb, Um_register rc);
 /*
   * Arguments: 
      Registers object,
      3 UM register IDs.
   * Purpose: executes the addition instruction - sets ra = rb + rc.
   * Fails:
      when reg is NULL,
      when register IDs are invalid.
   * Returns: void.
   */
void addition(Registers reg, Um_register ra, Um_register rb, Um_register rc);
/*
  * Arguments: 
     Registers object,
     3 UM register IDs.
  * Purpose: executes the multiplication instruction - sets ra = rb * rc.
  * Fails:
     when reg is NULL,
     when register IDs are invalid.
  * Returns: void.
  */
void multiplication(Registers reg, Um_register ra, Um_register rb,\
     Um_register rc);
 /*
   * Arguments: 
      Registers object,
      3 UM register IDs.
   * Purpose: executes the division instruction - sets ra = rb / rc.
   * Fails:
      when reg is NULL,
      when register IDs are invalid,
      if the value in rc is 0 (dividing by 0).
   * Returns: void.
   */
void division(Registers reg, Um_register ra, Um_register rb, Um_register rc);
/*
  * Arguments: 
     Registers object,
     3 UM register IDs.
  * Purpose: executes the division instruction - sets ra = ~(rb & rc).
  * Fails:
     when reg is NULL,
     when register IDs are invalid.
  * Returns: void.
  */
void bitwise_nand(Registers reg, Um_register ra, Um_register rb,\
     Um_register rc);
/*
 * Arguments: 
    Memory object,
    Registers object,
    program counterm
    Unpacked struct.
 * Purpose: executes the halt instruction - stops computation, frees memory
    and exits the program.
 * Fails:
    when mrm is NULL,
    when reg is NULL.
 * Returns: void.
 */
void halt(Memory mem, Registers reg, uint32_t *pc, Unpacked *u);

/*
  * Arguments: 
     Memory object,
     Registers object,
     3 UM register IDs.
  * Purpose: executes the map segment instruction - maps a new segment of 'rc'
     length and sets rb = the recently mapped segment ID.
  * Fails:
     when mem is NULL,
     when reg is NULL,
     when register IDs are invalid.
  * Returns: void.
  */
void map_segment(Memory mem, Registers reg, Um_register rb, Um_register rc);
/*
  * Arguments: 
     Memory object,
     Registers object,
     UM register ID.
  * Purpose: executes the unmap segment instruction - unmaps segemnt with 
     the ID 'rc'.
  * Fails:
     when mem is NULL,
     when reg is NULL,
     when register ID is invalid,
     when register ID is 0.
  * Returns: void.
  */
void unmap_segment(Memory mem, Registers reg, Um_register rc);
/*
  * Arguments: 
     Registers object,
     UM register ID.
  * Purpose: executes the output instruction - outputs the value in rc.
  * Fails:
     when reg is NULL,
     when register ID is invalid,
     when value to output is larger than 254 (non-ASCII character).
  * Returns: void.
  */
void output(Registers reg, Um_register rc);
/*
  * Arguments: 
     Registers object,
     UM register ID.
  * Purpose: executes the input instruction - stores input from the machine's 
     I/O device into rc. If the character read is EOF, stores 0xFFFF in rc.
  * Fails:
     when reg is NULL,
     when register ID is invalid,
     when value is larger than 254 (non-ASCII character).
  * Returns: void.
  */
void input(Registers reg, Um_register rc);
/*
  * Arguments: 
     Memory object,
     Registers object,
     2 UM register IDs.
  * Purpose: executes the load program instruction - loads the segment in ID 
     'rb' into segment 0, then sets the coutner to point to $m[0][rc].
  * Fails:
     when mem is NULL,
     when reg is NULL,
     when register IDs are invalid.
  * Returns: new program counter.
  */
uint32_t load_program(Memory mem, Registers reg, Um_register rb,\
     Um_register rc);
 /*
   * Arguments: 
      Registers object,
      word value.
   * Purpose: executes the load value instruction - loads value into ra.
   * Fails:
      when reg is NULL,
      when register IDs are invalid.
   * Returns: void.
   */
void load_value(Registers reg, Um_register ra, uint32_t value);

#endif