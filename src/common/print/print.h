#ifndef HAVE_DEFINED_PRINT_H
#define HAVE_DEFINED_PRINT_H

#define PRINT_BUF_SIZE      4096

typedef struct print_buffer s_print_buffer_t;

struct print_buffer {
    char   buf[PRINT_BUF_SIZE];
    uint32 start;
    uint32 index;
};

static s_print_buffer_t print_buf = {
    {0,}, 0, 0,
};

#endif

