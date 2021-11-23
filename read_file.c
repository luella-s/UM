#include "read_file.h"

/* Helper functions */
uint32_t file_length(char *filename);
static FILE *open_or_abort(char *filename, char *mode);

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

void read_file(Memory mem, char *filename)
{
    FILE *input = open_or_abort(filename, "r");
    uint32_t length = file_length(filename);
    uint32_t segmentID = map_segment_memory(mem, length);

    for (uint32_t i = 0; i < length; i++) {
        uint32_t word = 0x0;
        for (int lsb = 24; lsb >= 0; lsb -= 8) { 
            word = Bitpack_newu(word, 8, lsb, getc(input));
        }
        set_word(mem, segmentID, i, word);
    }
}

/*
 * Arguments:
   file name obtained throught the command line,
   mode to use for fopen.
 * Purpose: open a file stream to a file obtained through the command line
    and check if it's successfully opened. if not, exit the program.
 * Error cases:
    If the file isn't successfully opened, we exit with CRE.
 * Returns: a pointer to the successfully opened file stream.
 */
static FILE *open_or_abort(char *filename, char *mode)
{
    FILE *fp = fopen(filename, mode);

    /*
     * Open a file stream to the given file. Then, check if the file is
     * successfully opened. If not, exit the program.
     */
    assert(fp != NULL);

    return fp;
}

/*
 * Arguments:
   file name obtained throught the command line.
 * Purpose: find the number of 32-bit words in the file.
 * Returns: the length of file.
 */
uint32_t file_length(char *filename)
{
    struct stat st;
    if (stat(filename, &st) == 0) {
        assert(st.st_size % 4 == 0);
        return (st.st_size / 4);
    }
    return 0;
}