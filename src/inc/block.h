#ifndef HAVE_DEFINE_BLOCK_H
#define HAVE_DEFINE_BLOCK_H

typedef struct block_buffer        s_block_buf_t;

struct block_buffer {
    uint8  *array;
    uint32 index;
    uint32 size;
};

#endif

