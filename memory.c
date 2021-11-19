#include "memory.h"

struct Memory {
    UArray_T arr;
    Stack_T free_indices;
};

Sequence_T copy_sequence(Sequence_T seq, int id);

Memory memory_constructor()
{
    Memory mem = malloc(sizeof(*mem));
    mem->arr = UArray_new(100, sizeof(Sequence_T));
    mem->freeIDs = Stack_new();
}

uint32_t map_segment(Memory mem, uint32_t size)
{
    
}

void unmap_segment(Memory mem, int segmentID)
{

}

void copy_segment(Memory mem, int fromID, int toID)
{

}

/* helper function */
Sequence_T copy_sequence(Sequence_T seq, int id)
{
}

void add_to_segment(Memory mem, int segmentID, uint32_t word)
{
}

uint32_t get_word(Memory mem, int segmentID, int offset)
{
}

void set_word(Memory mem, int segmentID, int offset, uint32_t word)
{

}

void memory_destructor(Memory mem)
{
    
}
