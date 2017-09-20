#ifndef HAVE_DEFINED_ORDERED_ARRAY_H
#define HAVE_DEFINED_ORDERED_ARRAY_H

#define STACK_CAPACITY_SIZE  128

typedef sint32 (*ordered_compare_t)(void *, void *);

typedef struct ordered_array s_ordered_array_t;
typedef struct linked_list   s_linked_list_t;
typedef struct bitmap        s_bitmap_t;
typedef struct stack         s_stack_t;

struct ordered_array {
    void              **array;
    uint32            index;
    uint32            size;
    ordered_compare_t compare;
};

struct linked_list {
    s_linked_list_t *next;
    s_linked_list_t *prev;
};

struct stack {
    void **bp;
    void **sp;
    uint32 capacity;
};

struct bitmap {
    uint8  *array;
    uint32 array_size;
    uint32 map_size;
};

#endif

