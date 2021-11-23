#include "unpack.h"
#include <stdio.h>

int main() {
    uint32_t word = 988856330;
    //op = 3
    //ra = 0
    //rb = 1
    //rc = 2
    Unpacked *u = unpack(word);
    printf("Op code: %d\n", u->op);
    printf("ra: %d\n", u->ra);
    printf("rb: %d\n", u->rb);
    printf("rc: %d\n", u->rc);
    printf("Value: %u\n", u->value);

    word = 3559223015;
    //op = 13
    //ra = 2
    //value = 2453223
    u = unpack(word);
    printf("Op code: %d\n", u->op);
    printf("ra: %d\n", u->ra);
    printf("rb: %d\n", u->rb);
    printf("rc: %d\n", u->rc);
    printf("Value: %u\n", u->value);
}