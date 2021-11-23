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

void read_file(Memory mem, char *filename);

#endif