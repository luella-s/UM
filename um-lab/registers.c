#include <registers.h>

typedef struct Registers {
    UArray registers = UArray_new(8, sizeof(uint32_t));
} Registers;

void set_register(Um_register register, uint32_t word)
{
    Registers.register[register] = 0x0;
    Registers.register[register] = word;
}

uint32_t get_register(Um_register register)
{
    return Registers.registers[register];
}