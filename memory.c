/**************************************************************
 *
 *                     memory.c
 *
 *     Assignment: COMP40 Homework 6 - UM
 *     Authors:  Luella Sugiman (lsugim01), Unnathy Nellutla (unellu01)
 *     Date:     11/24/21
 *
 *     Implementation of Memory module - implements segmented memory
 *     data structure.
 *
 **************************************************************/

#include "memory.h"
#include <stdio.h>

/*
 * Memory struct:
   Sequence holding segments, each element represents one segment ID
   Sequence holding available segment IDs
 */
struct Memory {
   Seq_T seq;
   Seq_T freeIDs;
};

/* Helper functions */
void validate_seg(Memory mem, uint32_t segmentID);
uint32_t segment_mapped(Memory mem, uint32_t segmentID);
void validate_offset(Memory mem, uint32_t segmentID, uint32_t offset);

/*
 * Arguments: N/A
 * Purpose: instantiates Memory.
 * Fails:
    when memory allocation fails.
 * Returns: incomplete pointer to Memory struct
 */
Memory memory_new()
{
   Memory mem = malloc(sizeof(*mem));
   assert(mem != NULL);
   mem->seq = Seq_new(0);
   assert(mem->seq != NULL);
   mem->freeIDs = Seq_new(0);
   assert(mem->freeIDs != NULL);

   return mem;
}

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
uint32_t map_segment_memory(Memory mem, uint32_t length)
{
   assert(mem != NULL);
   
   uint32_t segmentID = 0;
   if (Seq_length(mem->freeIDs) == 0) {
      /* Insert into the next available spot in the Memory Sequence */
      UArray_T arr = UArray_new(length, sizeof(uint32_t));
      assert(arr != NULL);

      for (int i = 0; i < (int)length; i++) {
         *((uint32_t *)UArray_at(arr, i)) = (uint32_t)0x0;
      }

      segmentID = Seq_length(mem->seq);
      Seq_addhi(mem->seq, (void *)arr);
      // fprintf(stderr, "NEW segment length: %d\n", UArray_length(arr));
   } else {
      /* Free removed ID in freeIDs */
      uint32_t *idPtr = (uint32_t *)Seq_remhi(mem->freeIDs);
      segmentID = *idPtr;
      free(idPtr);

      /* Overwrite free segment with 0s */
      UArray_T tmp_arr = (UArray_T)Seq_get(mem->seq, segmentID);
      UArray_free(&tmp_arr);
      UArray_T arr = UArray_new(length, sizeof(uint32_t));
      Seq_put(mem->seq, segmentID, (void *)arr);
      // fprintf(stderr, "NEW segment length: %d\n", UArray_length(arr));
   }

   return segmentID;
}

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
void unmap_segment_memory(Memory mem, uint32_t segmentID)
{
   assert(mem != NULL);
   validate_seg(mem, segmentID);
   uint32_t mapped = segment_mapped(mem, segmentID);
   assert(mapped == 1);

   /* Insert unmapped ID into Sequence of available IDs */
   uint32_t *ID = malloc(sizeof(*ID));
   *ID = segmentID;
   Seq_addhi(mem->freeIDs, (void *)ID);
}

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
void copy_segment(Memory mem, uint32_t fromID, uint32_t toID)
{
   assert(mem != NULL);
   validate_seg(mem, fromID);
   uint32_t mapped = segment_mapped(mem, fromID);
   assert(mapped == 1);
   validate_seg(mem, toID);
   mapped = segment_mapped(mem, toID);
   assert(mapped == 1);

   /* Copy elements of segment fromID to segment toID */
   UArray_T from_arr = (UArray_T)Seq_get(mem->seq, fromID);
   uint32_t length = UArray_length(from_arr);
   // fprintf(stderr, "SUPPOSED COPIED segment length: %d\n", length);

   // UArray_T to_arr = (UArray_T)Seq_get(mem->seq, toID);
   // UArray_free(&to_arr); //?

   *((UArray_T *)Seq_get(mem->seq, toID)) = *((UArray_T *)UArray_copy(from_arr, length));
   // fprintf(stderr, "COPIED segment length: %d\n", UArray_length((UArray_T)Seq_get(mem->seq, toID)));
}

/*
* Arguments: 
   Memory object,
   segment ID to get a word from,
   Offset- position of word within segment.
* Purpose: Finds a word in memory and returns the value stored
* at that position. 
* Fails:
   when mem is NULL,
   when segmentID is out of bounds.
   when segmentID isn't mapped,
   when offset is out of the bounds of the segment.
* Returns: The value stored at the specified position.
*/
uint32_t get_word(Memory mem, uint32_t segmentID, uint32_t offset)
{
   assert(mem != NULL);
   validate_seg(mem, segmentID);
   uint32_t mapped = segment_mapped(mem, segmentID);
   assert(mapped == 1);
   validate_offset(mem, segmentID, offset);
   
   UArray_T tmp_arr = (UArray_T) Seq_get(mem->seq, segmentID);
   return *((uint32_t *)UArray_at(tmp_arr, offset));
}

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
void set_word(Memory mem, uint32_t segmentID, uint32_t offset, uint32_t word)
{
   assert(mem != NULL);
   validate_seg(mem, segmentID);
   uint32_t mapped = segment_mapped(mem, segmentID);
   assert(mapped == 1);
   validate_offset(mem, segmentID, offset);

   UArray_T tmp_arr = (UArray_T)Seq_get(mem->seq, segmentID);
   assert(tmp_arr != NULL);
   *((uint32_t *)UArray_at(tmp_arr, offset)) = word;
}

uint32_t get_length_segment(Memory mem, uint32_t segmentID)
{
   return UArray_length((UArray_T)Seq_get(mem->seq, segmentID));
}

/*
* Arguments: 
   Memory object,
* Purpose: destructor for memory object.
* Fails:
   memory is not freed by the end.
* Returns: void
*/
void memory_free(Memory mem)
{
   assert(mem != NULL);
   assert(mem->seq != NULL);
   assert (mem->freeIDs != NULL);
   
   uint32_t l = Seq_length(mem->seq);
   for(uint32_t i = 0; i < l; i++){
      UArray_T tmp_arr = (UArray_T)Seq_get(mem->seq, i);
      assert(tmp_arr != NULL);
      UArray_free(&(tmp_arr));
   }

   l = Seq_length(mem->freeIDs);
   for(uint32_t i = 0; i < l; i++){
      uint32_t *tmp = (uint32_t *)Seq_get(mem->freeIDs, i);
      free((void *)tmp);
   }

   Seq_free(&(mem->seq));
   Seq_free(&(mem->freeIDs));
   free(mem);
}

/*
* Arguments: 
   Memory object,
   segment ID to validate.
* Purpose: validates segment ID - ensures it's between 0 and the last index
   of the sequence.
* Fails:
   when segment ID is out of bounds.
* Returns: void
*/
void validate_seg(Memory mem, uint32_t segmentID)
{
   assert(segmentID < (uint32_t)Seq_length(mem->seq));
}

/*
* Arguments: 
   Memory object,
   segment ID to validate.
* Purpose: validates segment ID - ensures it's not an unmapped segment ID.
* Returns: 1 if segment is mapped, 0 otherwise.
*/
uint32_t segment_mapped(Memory mem, uint32_t segmentID) 
{
   for (uint32_t i = 0; i < (uint32_t)Seq_length(mem->freeIDs); i++) {
      if (*((uint32_t *)Seq_get(mem->freeIDs, i)) == segmentID) {
         return  0;
      }
   }
   return 1;
}

/*
* Arguments: 
   Memory object,
   offset to validate.
* Purpose: validates offset - ensures it's between 0 and the length of
   segments.
* Fails:
   when offset is out of bounds.
* Returns: void
*/
void validate_offset(Memory mem, uint32_t segmentID, uint32_t offset)
{
   assert(offset < (uint32_t)UArray_length((UArray_T)Seq_get(mem->seq, segmentID)));
}
