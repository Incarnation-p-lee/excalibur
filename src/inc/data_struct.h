#ifndef HAVE_DEFINED_ORDERED_ARRAY_H
#define HAVE_DEFINED_ORDERED_ARRAY_H

typedef sint32 (*ordered_compare_t)(void *, void *);

struct ordered_array {
    void              **array;
    uint32            size;
    uint32            max_size;
    ordered_compare_t compare;
};
typedef struct ordered_array s_ordered_array_t;

#endif

