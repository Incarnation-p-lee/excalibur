#ifndef HAVE_DEFINED_ORDERED_ARRAY_H
#define HAVE_DEFINED_ORDERED_ARRAY_H

typedef sint32 (*ordered_compare_t)(void *, void *);

typedef struct ordered_array s_ordered_array_t;

struct ordered_array {
    void              **array;
    uint32            index;
    uint32            size;
    ordered_compare_t compare;
};

#endif

