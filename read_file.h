#ifndef READ_FILE_H_
#define READ_FILE_H_

#include "stdint.h"
#include "memory.h"
#include <bitpack.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*
 * Arguments:
    Memory 
   file name obtained throught the command line,
   mode to use for fopen.
 * Purpose: Read information from input file and store it 
 * in memory. 
 * Error cases:
    If the file isn't successfully opened, we exit with CRE.
 * Returns: void
 */
void read_file(Memory mem, char *filename);

#endif