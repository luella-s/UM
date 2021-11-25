/*
 * umlab.c
 *
 * Functions to generate UM unit tests. Once complete, this module
 * should be augmented and then linked against umlabwrite.c to produce
 * a unit test writing program.
 *  
 * A unit test is a stream of UM instructions, represented as a Hanson
 * Seq_T of 32-bit words adhering to the UM's instruction format.  
 * 
 * Any additional functions and unit tests written for the lab go
 * here. 
 *  
 */


#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <seq.h>
#include <bitpack.h>


typedef uint32_t Um_instruction;
typedef enum Um_opcode {
        CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
        NAND, HALT, ACTIVATE, INACTIVATE, OUT, IN, LOADP, LV
} Um_opcode;


/* Functions that return the two instruction types */

Um_instruction three_register(Um_opcode op, int ra, int rb, int rc)
{
        uint32_t word = 0x0;
        word = Bitpack_newu(word, 4, 28, op);
        word = Bitpack_newu(word, 3, 6, ra);
        word = Bitpack_newu(word, 3, 3, rb);
        word = Bitpack_newu(word, 3, 0, rc);
        return word;
}


Um_instruction loadval(unsigned ra, unsigned val)
{
        uint32_t word = 0x0;
        word = Bitpack_newu(word, 4, 28, LV);
        word = Bitpack_newu(word, 3, 25, ra);
        word = Bitpack_newu(word, 25, 0, (uint32_t)val);
        return word;
}


/* Wrapper functions for each of the instructions */

typedef enum Um_register { r0 = 0, r1, r2, r3, r4, r5, r6, r7 } Um_register;

static inline Um_instruction conditional_move(Um_register a, Um_register b, Um_register c) 
{
        return three_register(CMOV, a, b, c);
}

static inline Um_instruction segmented_load(Um_register a, Um_register b, Um_register c) 
{
        return three_register(SLOAD, a, b, c);
}

static inline Um_instruction segmented_store(Um_register a, Um_register b, Um_register c) 
{
        return three_register(SSTORE, a, b, c);
}

static inline Um_instruction add(Um_register a, Um_register b, Um_register c) 
{
        return three_register(ADD, a, b, c);
}

static inline Um_instruction multiply(Um_register a, Um_register b, Um_register c) 
{
        return three_register(MUL, a, b, c);
}

static inline Um_instruction divide(Um_register a, Um_register b, Um_register c) 
{
        return three_register(DIV, a, b, c);
}

static inline Um_instruction bitwise_nand(Um_register a, Um_register b, Um_register c) 
{
        return three_register(NAND, a, b, c);
}

static inline Um_instruction halt(void) 
{
        return three_register(HALT, 0, 0, 0);
}

static inline Um_instruction map_segment(Um_register b, Um_register c) 
{
        return three_register(ACTIVATE, 0, b, c);
}

static inline Um_instruction unmap_segment(Um_register c) 
{
        return three_register(INACTIVATE, 0, 0, c);
}

static inline Um_instruction output(Um_register c) 
{
        return three_register(OUT, 0, 0, c);
}

static inline Um_instruction input(Um_register c) 
{
        return three_register(IN, 0, 0, c);
}

static inline Um_instruction load_program(Um_register b, Um_register c) 
{
        return three_register(LOADP, 0, b, c);
}



/* Functions for working with streams */

static inline void append(Seq_T stream, Um_instruction inst)
{
        assert(sizeof(inst) <= sizeof(uintptr_t));
        Seq_addhi(stream, (void *)(uintptr_t)inst);
}

const uint32_t Um_word_width = 32;

void Um_write_sequence(FILE *output, Seq_T stream)
{
        assert(output != NULL && stream != NULL);
        int stream_length = Seq_length(stream);
        for (int i = 0; i < stream_length; i++) {
                Um_instruction inst = (uintptr_t)Seq_remlo(stream);
                for (int lsb = Um_word_width - 8; lsb >= 0; lsb -= 8) { //big-Endian write
                        fputc(Bitpack_getu(inst, 8, lsb), output);
                }
        }
}


/* Unit tests for the UM */

void build_halt_test(Seq_T stream)
{
        append(stream, halt());
}

void build_output_load_val_test(Seq_T stream)
{
        append(stream, loadval(r1, 'B'));
        append(stream, output(r1));
        append(stream, loadval(r1, 'a'));
        append(stream, output(r1));
        append(stream, loadval(r1, 'd'));
        append(stream, output(r1));
        append(stream, loadval(r1, '!'));
        append(stream, output(r1));
        append(stream, loadval(r1, '\n'));
        append(stream, output(r1));
        append(stream, halt());
}

void build_add_test(Seq_T stream)
{
        append(stream, loadval(r2, 32));
        append(stream, loadval(r3, 46));
        append(stream, add(r1, r2, r3));
        append(stream, output(r1));
        append(stream, output(r1));
        append(stream, output(r2));
        append(stream, output(r3));
         append(stream, halt());
}

void build_multiply_test(Seq_T stream)
{
        append(stream, loadval(r2, 10));
        append(stream, loadval(r3, 10));
        append(stream, multiply(r1, r2, r3));
        append(stream, output(r1));
        append(stream, halt());
}

void build_divide_test(Seq_T stream)
{
        append(stream, loadval(r2, 900));
        append(stream, loadval(r3, 10));
        append(stream, divide(r1, r2, r3));
        append(stream, output(r1));
        append(stream, halt());
}

void build_nand_test(Seq_T stream)
{
        append(stream, loadval(r2, 0)); //11111s
        append(stream, loadval(r0, 0));
        append(stream, bitwise_nand(r1, r2, r0));
        append(stream, bitwise_nand(r3, r1, r1));
        append(stream, output(r3)); //should be 0
}

void build_map_segment_test(Seq_T stream)
{
        append(stream, loadval(r3, 8));
        append(stream, map_segment(r2, r3));
        append(stream, output(r2)); //should be 0 (null)
        append(stream, halt());
}

void build_seg_load_test(Seq_T stream)
{
        append(stream, loadval(r1, 0));
        append(stream, loadval(r4, 8));
        append(stream, map_segment(r2, r4));
        append(stream, loadval(r3, 'c'));
        append(stream, segmented_store(r2, r1, r3));
        append(stream, segmented_load(r6, r2, r1));
        append(stream, segmented_load(r5, r2, r1));
        append(stream, output(r6)); //should be 'c'
        append(stream, output(r5));
        append(stream, halt());
}

void build_unmap_seg_test(Seq_T stream)
{
        append(stream, loadval(r3, 8));
        append(stream, map_segment(r2, r3));
        append(stream, unmap_segment(r2));
        append(stream, map_segment(r4, r3));
        append(stream, output(r2)); //r2 should be r4
        append(stream, output(r4));
        append(stream, halt());
}

//

void build_seg_store_test(Seq_T stream)
{
        append(stream, loadval(r3, 8));
        append(stream, map_segment(r2, r3));
        append(stream, loadval(r3, 'D'));
        append(stream, segmented_store(r2, r1, r3));
        append(stream, segmented_load(r6, r2, r1));
        
        append(stream, output(r6)); //should be D
        append(stream, halt());
}

void build_cond_move_test(Seq_T stream)
{
        append(stream, loadval(r3, '1'));
        append(stream, loadval(r2, 'd'));
        append(stream, conditional_move(r1, r2, r3));
        append(stream, output(r1)); //should be 'd'
        append(stream, halt());
}

void build_input_test(Seq_T stream)
{
        append(stream, input(r3));
        append(stream, output(r3)); //should be input
        append(stream, halt());
}

void build_load_program_test(Seq_T stream)
{
        append(stream, output(r2));
        append(stream, loadval(r5, 72));
        append(stream, loadval(r6, 75));
        //mapping 2 segments 1, and 2
        append(stream, map_segment(r1, r5));
        append(stream, unmap_segment(r1));
        append(stream, map_segment(r2, r6));
        append(stream, output(r2));
        append(stream, loadval(r3, 9));
        append(stream, conditional_move(r1, r2, r3));
        append(stream, output(r1));
        
        //storing a value in segment 1 pos 65
        append(stream, loadval(r3, 0xa00fff));
        append(stream, loadval(r7, 65));
        append(stream, segmented_store(r2, r7, r3));
        
        //load segment 2 to segment 0
        // with pc to point to 65
        append(stream, load_program(r2, r7));
        // get value at 0, 65 and output 
        append(stream, loadval(r5, 0));
        append(stream, segmented_load(r0, r5, r7));
        append(stream, output(r0));
        append(stream, halt());
}

void build_load_program_jump_test(Seq_T stream)
{
        append(stream, loadval(r0, 0));
        append(stream, loadval(r1, 7));
        append(stream, load_program(r0, r1));

        append(stream, loadval(r3, '1'));
        append(stream, loadval(r2, 'd'));
        append(stream, conditional_move(r1, r2, r3));
        append(stream, output(r1));

        append(stream, halt());
}

