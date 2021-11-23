#include "memory.h"
#include <stdio.h>

int main() 
{
   Memory new_mem = memory_new();
   int segmentID = map_segment_memory(new_mem, 8);
   // printf("segment ID: %d is mapped? %d\n", segmentID, segment_mapped(new_mem, segmentID));

   for (int i = 0; i < 8; i++) {
      set_word(new_mem, segmentID, i, (uint32_t)(i*34));
   }
   for (int i = 0; i < 8; i++) {
      //  printf("%u\n", get_word(new_mem, segmentID, i));
   }

   int segmentID2 = map_segment_memory(new_mem, 8);
   //  printf("segment ID: %d is mapped? %d\n", segmentID2, segment_mapped(new_mem, segmentID2));
   copy_segment(new_mem, segmentID, segmentID2);

   for (int i = 0; i < 8; i++) {
      //  printf("segmentID2: %u\n", get_word(new_mem, segmentID2, i));
   }
   
   unmap_segment_memory(new_mem, segmentID);
   // printf("segment ID: %d is mapped? %d\n", segmentID, segment_mapped(new_mem, segmentID));

   printf("after\n\n");
   
   int val = get_word(new_mem, segmentID2, 1); //should be 34                  //aborted
   printf("word at segment %d and offset %d is %d\n", segmentID2, 1, val);

   set_word(new_mem, segmentID2, 1, (uint32_t)2484);
   val = get_word(new_mem, segmentID2, 1); //should be 2484
   printf("word at segment %d and offset %d is %d\n", segmentID2, 1, val);

   memory_free(new_mem);
   /*
   int map_segment(Memory mem, int length);
   void unmap_segment(Memory mem, int segmentID);
   void copy_segment(Memory mem, int fromID, int toID);
   uint32_t get_word(Memory mem, int segmentID, int offset);
   void set_word(Memory mem, int segmentID, int offset, uint32_t word);
   void memory_destructor();
   */
}