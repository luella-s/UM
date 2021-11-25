/**************************************************************
 *
 *                     instructions.c
 *
 *     Assignment: COMP40 Homework 6 - UM
 *     Authors:  Luella Sugiman (lsugim01), Unnathy Nellutla (unellu01)
 *     Date:     11/24/21
 *
 *     Implementation of Instructions module - implements functions
 *     that execute UM instructions.
 *
 **************************************************************/

#include "instructions.h"

/* Helper functions */
void validate_registers(Um_register r);
uint32_t validate_char(uint32_t i);

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
void conditional_move(Registers reg, Um_register ra, Um_register rb, Um_register rc) 
{
    assert(reg != NULL);
    validate_registers(ra);
    validate_registers(rb);
    validate_registers(rc);
    
    if (get_register(reg, rc) != 0) {
        set_register(reg, ra, get_register(reg, rb));
    }
}

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
void segmented_load(Memory mem, Registers reg, Um_register ra, Um_register rb, Um_register rc)
{ 
    assert(mem != NULL);
    assert(reg != NULL);
    validate_registers(ra);
    validate_registers(rb);
    validate_registers(rc);

    uint32_t new_word = get_word(mem, get_register(reg, rb), get_register(reg, rc));
    set_register(reg, ra, new_word);
}

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
void segmented_store(Memory mem, Registers reg, Um_register ra, Um_register rb, Um_register rc)
{ 
    assert(mem != NULL);
    assert(reg != NULL);
    validate_registers(ra);
    validate_registers(rb);
    validate_registers(rc);
    
    uint32_t val = get_register(reg, rc);
    set_word(mem, get_register(reg, ra), get_register(reg, rb), val);
}

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
void addition(Registers reg, Um_register ra, Um_register rb, Um_register rc)
{
    assert(reg != NULL);
    validate_registers(ra);
    validate_registers(rb);
    validate_registers(rc);

    uint32_t v1 = get_register(reg, rb);
    uint32_t v2 = get_register(reg, rc);
    uint32_t val = v1 + v2;  
    set_register(reg, ra, val);
}

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
void multiplication(Registers reg, Um_register ra, Um_register rb, Um_register rc)
{
    assert(reg != NULL);
    validate_registers(ra);
    validate_registers(rb);
    validate_registers(rc);

    uint32_t v1 = get_register(reg, rb);
    uint32_t v2 = get_register(reg, rc);
    uint32_t val = v1 * v2;  
    set_register(reg, ra, val);
}
 
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
void division(Registers reg, Um_register ra, Um_register rb, Um_register rc){
    assert(reg != NULL);
    validate_registers(ra);
    validate_registers(rb);
    validate_registers(rc);

    uint32_t v1 = get_register(reg, rb);
    uint32_t v2 = get_register(reg, rc);
    assert(v2 != 0);
    uint32_t val = v1 / v2; 
    set_register(reg, ra, val);
}

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
void bitwise_nand(Registers reg, Um_register ra, Um_register rb, Um_register rc)
{
    assert(reg != NULL);
    validate_registers(ra);
    validate_registers(rb);
    validate_registers(rc);
    
    uint32_t v1 = get_register(reg, rb);
    uint32_t v2 = get_register(reg, rc);
    
    uint32_t val = ~(v1 & v2);
    set_register(reg, ra, val);
}

/*
 * Arguments: 
    Memory object,
    Registers object,
 * Purpose: executes the halt instruction - stops computation, frees memory
    and exits the program.
 * Fails:
    when mem is NULL,
    when reg is NULL.
 * Returns: void.
 */
void halt(Memory mem, Registers reg)
{
    assert(mem != NULL);
    assert(reg != NULL);

    memory_free(mem);
    registers_free(reg);
    exit(EXIT_SUCCESS);
}

/*
 * Arguments: 
    Memory object,
    Registers object,
    2 UM register IDs.
 * Purpose: executes the map segment instruction - maps a new segment of 'rc'
    length and sets rb = the recently mapped segment ID.
 * Fails:
    when mem is NULL,
    when reg is NULL,
    when register IDs are invalid.
 * Returns: void.
 */
void map_segment(Memory mem, Registers reg, Um_register rb, Um_register rc)
{
    assert(mem != NULL);
    assert(reg != NULL);
    validate_registers(rb);
    validate_registers(rc);

    uint32_t segmentID = map_segment_memory(mem, get_register(reg, rc));
    set_register(reg, rb, segmentID);
}

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
void unmap_segment(Memory mem, Registers reg, Um_register rc)
{
    assert(mem != NULL);
    assert(reg != NULL);
    validate_registers(rc);

    assert(get_register(reg, rc) != 0);
    unmap_segment_memory(mem, get_register(reg, rc));
}

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
void output(Registers reg, Um_register rc)
{
    assert(reg != NULL);
    validate_registers(rc);
    
    assert(get_register(reg, rc) <= 255);
    fprintf(stdout, "%c", get_register(reg, rc));
}

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
void input(Registers reg, Um_register rc)
{
    assert(reg != NULL);
    validate_registers(rc);

    uint32_t i = getc(stdin);
    uint32_t c = validate_char(i);
    set_register(reg, rc, c);
}

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
uint32_t load_program(Memory mem, Registers reg, Um_register rb, Um_register rc)
{
    assert(mem != NULL);
    assert(reg != NULL);
    validate_registers(rb);
    validate_registers(rc);

    /* If the segment to load isn't the 0 segment, load into the 0 segment */
    uint32_t pc_val;
    if (get_register(reg, rb) != 0) {
        copy_segment(mem, get_register(reg, rb), 0);
    }

    /* Set the program counter */
    pc_val = get_register(reg, rc);
    assert(pc_val < get_length_segment(mem, 0));

    return pc_val;
}

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
void load_value(Registers reg, Um_register ra, uint32_t value)
{
    assert(reg != NULL);
    validate_registers(ra);

    set_register(reg, ra, value);
}

/*
 * Arguments: 
    UM register ID.
 * Purpose: validates that the ID is within bounds.
 * Fails:
    when the register ID is not valid.
 * Returns: void.
 */
void validate_registers(Um_register r)
{
    assert(r >= 0 && r <= 7);
}

/*
 * Arguments: 
    UM register ID.
 * Purpose: validates that the integer i is an ASCII character.
 * Fails:
    when i isn't an ACSII character (more than 254).
 * Returns: word of 'i', or 32-bit EOF if 'i' is the EOF character.
 */
uint32_t validate_char(uint32_t i)
{
    if (i == (uint32_t)EOF) {
        return ~(uint32_t)0x0;
    }
    assert(i <= 255);
    return (uint32_t) i;
}