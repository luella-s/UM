#ifndef REGISTERS_H_
#define REGISTERS_H_

#include "uarray.h"
#include "stdint.h"
#include <stdlib.h>

typedef enum Um_register { r0 = 0, r1, r2, r3, r4, r5, r6, r7 } Um_register;
typedef struct Registers *Registers;

Registers registers_constructor();
void set_register(Registers res, Um_register rg, uint32_t word);
uint32_t get_register(Registers res, Um_register rg);
void registers_destructor(Registers res);

#endif