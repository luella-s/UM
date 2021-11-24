/**************************************************************
 *
 *                     memory.h
 *
 *     Assignment: COMP40 Homework 6 - UM
 *     Authors:  Luella Sugiman (lsugim01), Unnathy Nellutla (unellu01)
 *     Date:     11/24/21
 *
 *     Interface of Memory module - defines public functions of the
 *     segmented memory data structure.
 *
 **************************************************************/

#ifndef MEMORY_H_
#define MEMORY_H_

#include "seq.h"
#include "uarray.h"
#include "stdint.h"
#include <assert.h>
#include <stdlib.h>

typedef struct Memory *Memory;

/*
 * Arguments: N/A
 * Purpose: instantiates Memory.
 * Fails:
    when memory allocation fails.
 * Returns: incomplete pointer to Memory struct
 */
Memory memory_new();

/*
 * Arguments: 
    Memory object,
    length of segments (number of 32-bit words in the input file).
 * Purpose: creates a new segment of 'length' words of 0s
 * Fails:
    when mem is NULL,
    when memory allocation fails.
 * Returns: segment ID segment is inserted into.
 */
uint32_t map_segment_memory(Memory mem, uint32_t length);


void unmap_segment_memory(Memory mem, uint32_t segmentID);


void copy_segment(Memory mem, uint32_t fromID, uint32_t toID);


uint32_t get_word(Memory mem, uint32_t segmentID, uint32_t offset);


void set_word(Memory mem, uint32_t segmentID, uint32_t offset, uint32_t word);


uint32_t get_length_segment(Memory mem, uint32_t segmentID);


void memory_free(Memory mem);

#endif