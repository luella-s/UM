#ifndef MEMORY_H_
#define MEMORY_H_
#include "seq.h"
#include "stack.h"
#include "registers.h"

typedef struct Memory *Memory;

void map_segment(int segmentID, uint32_t word);
void unmap_segment(int segmentID);
void copy_segment(int fromID, int toID);
void add_to_segment(int segmentID, uint32_t word);
uint32_t get_word(int segmentID, int offset);
void set_word(int segmentID, int offset, uint32_t word);
void halt();

#endif