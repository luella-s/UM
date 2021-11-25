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

/*
 * Memory struct:
   Sequence holding segments, each element represents one segment ID
   Sequence holding available segment IDs
 */
typedef struct Memory {
   Seq_T seq;
   Seq_T freeIDs;
}*Memory;

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

/*
* Arguments: 
   Memory object,
   segment ID to free.
* Purpose: unmaps the given segment ID by adding the ID to the free_IDs 
   sequence, indicating it's available to write over.
* Fails:
   when mem is NULL,
   when segmentID isn't mapped,
   when segmentID is out of bounds.
* Returns: void.
*/
void unmap_segment_memory(Memory mem, uint32_t segmentID);

/*
* Arguments: 
   Memory object,
   segment ID to copy from,
   segment ID to copy to.
* Purpose: copies values of segment fromID to segment toID.
* Fails:
   when mem is NULL,
   when segment fromID isn't mapped,
   when fromID or toID is out of bounds.
* Returns: void.
*/
void copy_segment(Memory mem, uint32_t fromID, uint32_t toID);

/*
 * Arguments: 
   Memory object,
   segment ID to get a word from,
   Offset - position of word within segment.
 * Purpose: Finds a word in memory and returns the value stored
 * at that position. 
 * Fails:
   when mem is NULL,
   when segmentID is out of bounds.
   when segmentID isn't mapped,
   when offset is out of the bounds of the segment.
 * Returns: The value stored at the specified position.
 */
uint32_t get_word(Memory mem, uint32_t segmentID, uint32_t offset);

/*
* Arguments: 
   Memory object,
   segment ID to get a word from,
   Position of word within segment.
   a word to be loaded in that address in memory;
* Purpose: Finds an address in memory and sets a 
* given value there;
* Fails:
   when mem is NULL,
   when segmentID is out of bounds,
   when segmentID isn't mapped,
   when offset is out of the bounds of the segment.
* Returns: void.
*/
void set_word(Memory mem, uint32_t segmentID, uint32_t offset, uint32_t word);

/*
* Arguments: 
   Memory object,
   segment ID to get a length of.
* Purpose: Finds the length of a specified segment.
* Fails:
   when mem is NULL,
   when segmentID is out of bounds,
   when segmentID isn't mapped.
* Returns: void.
*/
uint32_t get_length_segment(Memory mem, uint32_t segmentID);

/*
* Arguments: 
   Memory object,
* Purpose: destructor for memory object.
* Fails:
   mem is NULL,
   mem's contents are NULL.
* Returns: void
*/
void memory_free(Memory mem);

#endif 