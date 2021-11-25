#ifndef REGISTERS_H_
#define REGISTERS_H_
#include "uarray.h"
#include "stdint.h"

typedef enum Um_register { r0 = 0, r1, r2, r3, r4, r5, r6, r7 } Um_register;

void set_register(Um_register register, uint32_t word);
uint32_t get_register(Um_register register);


#endif