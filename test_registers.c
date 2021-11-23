#include "registers.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    Registers reg = registers_new();
    set_register(reg, r0, 4);
    uint32_t tmp = get_register(reg, r0);
    printf("%u\n", tmp);
    registers_free(reg);
    free(reg);
}