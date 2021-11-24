#include "instructions.h"
#include <stdio.h>

void test_cond_move(Registers reg);
void test_seg_load(Memory mem, Registers reg);
void test_add(Registers reg);
void test_seg_store(Memory mem, Registers reg);
void test_multiply(Registers reg);
void test_div(Registers reg);
void test_bitwise_nand(Registers reg);
void test_halt(Memory mem, Registers reg);
void test_map_segment(Memory mem, Registers reg);
void test_unmap_segment(Memory mem, Registers reg);
void test_input_output(Registers reg);
void test_load_program(Memory mem, Registers reg);
void test_load_val(Registers reg);
void test_freeIDs(Memory mem, Registers reg);

int main() 
{
    Registers reg = registers_new();
    Memory mem = memory_new();
    // map_segment_memory(mem, 8);
    // set_word(mem, 0, 0, 589);
    
    /*test_cond_move(reg);
    test_seg_load(mem, reg);
    test_seg_store(mem, reg);
    test_add(reg);
    test_multiply(reg);
    test_div(reg);
    test_bitwise_nand(reg);
    test_map_segment(mem, reg);
    test_unmap_segment(mem, reg);
    test_input_output(reg); */
    test_load_program(mem, reg);
    /*test_load_val(reg);
    test_halt(mem, reg); */

    //test_freeIDs(mem, reg);
    halt(mem, reg);
}

void test_freeIDs(Memory mem, Registers reg)
{
    //map 0 segment
    set_register(reg, r2, 8);
    map_segment(mem, reg, r3, r2);  //r3 = 0
    printf("Mapped: %d\n", get_register(reg, r3));

    //map 1 segment
    set_register(reg, r2, 6);
    map_segment(mem, reg, r4, r2);  //r4 = 1
    printf("Mapped: %d\n", get_register(reg, r4));

    //unmap 1
    printf("Unmapping: %d\n", get_register(reg, r4));
    unmap_segment(mem, reg, r4);

    //remap 1
    map_segment(mem, reg, r5, r2);  //r5 = r4 = 1

    printf("Newly mapped segment ID (should be 1): %d\n", get_register(reg, r5));
}

void test_cond_move(Registers reg) {
    set_register(reg, r1, 3); //rb = 3
    set_register(reg, r2, 2); //rc != 0
    conditional_move(reg, r0, r1, r2);
    
    printf("Conditional Move:\nra: %u\n\n", get_register(reg, r1));
}

void test_seg_load(Memory mem, Registers reg) {
    set_register(reg, r0, 0);
    set_register(reg, r1, 0);
    segmented_load(mem, reg, r4, r0, r1);
    printf("Segmented Load:\nra: %u\n\n", get_register(reg, r4));
}

void test_seg_store(Memory mem, Registers reg) {
    set_register(reg, r0, 0);
    set_register(reg, r1, 0);
    segmented_store(mem, reg, r0, r1, r2);
    printf("Segmented Store:\nrc: %u\n\n", get_register(reg, r2));
    
}

void test_add(Registers reg)
{
    set_register(reg, r1, 72847);
    set_register(reg, r2, 56665);
    addition(reg, r0, r1, r2);
    printf("Addition:\nra: %u\n\n", get_register(reg, r0));
}

void test_multiply(Registers reg)
{
    set_register(reg, r1, 47);
    set_register(reg, r2, 10);
    multiplication(reg, r0, r1, r2);
    printf("Multiplication:\nra: %u\n\n", get_register(reg, r0));
}

void test_div(Registers reg) 
{
    set_register(reg, r1, 144);
    set_register(reg, r2, 12);
    division(reg, r0, r1, r2);
    printf("Division:\nra: %u\n\n", get_register(reg, r0));
}

void test_bitwise_nand(Registers reg)
{
    set_register(reg, r1, 0xFFFFFFFF); //1111...
    set_register(reg, r2, 1); //...0001
    bitwise_nand(reg, r0, r1, r2);
    printf("Bitwise NAND:\nra: %u\n\n", get_register(reg, r0));
}

void test_halt(Memory mem, Registers reg)
{
    halt(mem, reg);
}

void test_map_segment(Memory mem, Registers reg){
    set_register(reg, r1, 3);
    map_segment(mem, reg, r2, r1);
    printf("Map Segment:\nrb: %u\n\n", get_register(reg, r2));
}

void test_unmap_segment(Memory mem, Registers reg)
{
    // set_register(reg, r2, 1);
    unmap_segment(mem, reg, r2);
    // printf("Unmap Segment:\nrc: %u\nsegment mapped? %d\n\n", get_register(reg, r2), segment_mapped(mem, 3));
}

void test_input_output(Registers reg){
    input(reg, r6);
    printf("Output: ");
    output(reg, r6);
}

void test_load_program(Memory mem, Registers reg)
{
    load_value(reg, r1, 8);
    map_segment(mem, reg, r2, r1);
    //map seg 0 r2 = 0
    load_value(reg, r4, 10);
    map_segment(mem, reg, r3, r4);
    // map seg 1 r3 = 1
    
    
    load_value(reg, r7, 2);
    load_value(reg, r6, 70);
    segmented_store(mem, reg, r3, r7, r6);
    //store value in r6 at 1, 2
    
    load_program(mem, reg, r3, r7);
    //load segmetn 1 into segment 0
    
    //load value at 0, 2 into r0
    segmented_load(mem, reg, r5, r3, r7);
    output(reg, r5);

    printf("Load Program: At (0, 2): %u\n\n", get_word(mem, 0, 2));
    printf("Load Program: At (1, 2): %u\n\n", get_word(mem, 1, 2));
}

void test_load_val(Registers reg){
    load_value(reg, r5, 56);
    printf("Load Value:\nrb: %u\n\n", get_register(reg, r5));
}