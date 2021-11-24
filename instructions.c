#include "instructions.h"

/* Helper functions */
void validate_registers(Um_register r);
uint32_t validate_char(uint32_t i);

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

void addition(Registers reg, Um_register ra, Um_register rb, Um_register rc)
{
    assert(reg != NULL);
    validate_registers(ra);
    validate_registers(rb);
    validate_registers(rc);

    uint32_t val = get_register(reg, rb) + get_register(reg, rc);
    set_register(reg, ra, val);
}

void multiplication(Registers reg, Um_register ra, Um_register rb, Um_register rc)
{
    assert(reg != NULL);
    validate_registers(ra);
    validate_registers(rb);
    validate_registers(rc);
    //fprintf(stderr, "mult: %u, %u \n",get_register(reg, rb), get_register(reg, rc));
    uint32_t v1 = get_register(reg, rb);
    uint32_t v2 = get_register(reg, rc);
    uint32_t val = v1 * v2;  
    //fprintf(stderr, "mval: %x ", val);
    set_register(reg, ra, val);
    //fprintf(stderr, "got from reg: %u \n \n", get_register(reg, ra));
}
 
void division(Registers reg, Um_register ra, Um_register rb, Um_register rc){
    assert(reg != NULL);
    validate_registers(ra);
    validate_registers(rb);
    validate_registers(rc);
    
    //fprintf(stderr, "division: %x, %x \n", get_register(reg, rb), get_register(reg, rc));
    assert(get_register(reg, rc) != 0);
    uint32_t val = get_register(reg, rb) / get_register(reg, rc); 
    set_register(reg, ra, val);
}

void bitwise_nand(Registers reg, Um_register ra, Um_register rb, Um_register rc)
{
    assert(reg != NULL);
    validate_registers(ra);
    validate_registers(rb);
    validate_registers(rc);

    uint32_t val = ~(get_register(reg, rb) & get_register(reg, rc));
    set_register(reg, ra, val);
}

void halt(Memory mem, Registers reg)
{
    assert(mem != NULL);
    assert(reg != NULL);

    memory_free(mem);
    registers_free(reg);
    exit(EXIT_SUCCESS);
}

void map_segment(Memory mem, Registers reg, Um_register rb, Um_register rc)
{
    assert(mem != NULL);
    assert(reg != NULL);
    validate_registers(rc);

    uint32_t segmentID = map_segment_memory(mem, get_register(reg, rc));
    set_register(reg, rb, segmentID);
}

void unmap_segment(Memory mem, Registers reg, Um_register rc)
{
    assert(mem != NULL);
    assert(reg != NULL);
    validate_registers(rc);

    assert(get_register(reg, rc) != 0);
    unmap_segment_memory(mem, get_register(reg, rc));
}

void output(Registers res, Um_register rc)
{
    assert(res != NULL);
    validate_registers(rc);
    
    assert(get_register(res, rc) <= 255);
    fprintf(stdout, "%c", get_register(res, rc));
}

void input(Registers res, Um_register rc)
{
    uint32_t i = getc(stdin);
    uint32_t c = validate_char(i);
    set_register(res, rc, c);
}

uint32_t *load_program(Memory mem, Registers reg, uint32_t *pc, Um_register rb, Um_register rc)
{
    assert(mem != NULL);
    assert(reg != NULL);
    validate_registers(rb);
    validate_registers(rc);

    if (get_register(reg, rb) != 0) {
        // fprintf(stderr, "new from %d to %d\n", get_register(reg, rb), get_register(reg, rc));
        copy_segment(mem, get_register(reg, rb), 0);
    }

    // pc = set_counter(pc, get_register(reg, rc));
    *pc = get_register(reg, rc);
    // fprintf(stderr, "segmont 0 length: %d\nnew counter: %d\n", get_length_segment(mem, 0), *pc);

    assert(*pc < get_length_segment(mem, 0));

    return pc;
}

void load_value(Registers reg, Um_register ra, uint32_t value)
{
    assert(reg != NULL);
    validate_registers(ra);

    set_register(reg, ra, value);
}

void validate_registers(Um_register r)
{
    assert(r >= 0 && r <= 7);
}

uint32_t validate_char(uint32_t i)
{
    if (i == (uint32_t)EOF) {
        return ~(uint32_t)0x0;
    }
    assert(i <= 255);
    return (uint32_t) i;
}