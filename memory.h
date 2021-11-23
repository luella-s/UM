#ifndef MEMORY_H_
#define MEMORY_H_

#include "seq.h"
#include "uarray.h"
#include "stdint.h"
#include <assert.h>
#include <stdlib.h>

typedef struct Memory *Memory;

Memory memory_new();
uint32_t map_segment_memory(Memory mem, uint32_t length);
void unmap_segment_memory(Memory mem, uint32_t segmentID);
void copy_segment(Memory mem, uint32_t fromID, uint32_t toID);
uint32_t get_word(Memory mem, uint32_t segmentID, uint32_t offset);
void set_word(Memory mem, uint32_t segmentID, uint32_t offset, uint32_t word);
uint32_t get_length_segment(Memory mem, uint32_t segmentID);
void memory_free(Memory mem);

#endif