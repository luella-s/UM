#include "registers.h"

struct Registers {
    UArray_T arr;
};

Registers registers_constructor()
{
    Registers res = malloc(sizeof(*res));
    res->arr = UArray_new(8, sizeof(uint32_t));
    return res;
}

void set_register(Registers res, Um_register rg, uint32_t word)
{
    *((uint32_t *)UArray_at(res->arr, rg)) = word;
}

uint32_t get_register(Registers res, Um_register rg)
{
    return *((uint32_t *)UArray_at(res->arr, rg));
}

void registers_destructor(Registers res){
    UArray_free(&(res->arr));
}