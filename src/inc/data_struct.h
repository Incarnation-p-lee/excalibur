#ifndef HAVE_DEFINED_ORDERED_ARRAY_H
#define HAVE_DEFINED_ORDERED_ARRAY_H

typedef sint32 (*ordered_compare_t)(const void *, const void *);

struct ordered_array {
    void              **array;
    uint32            size;
    uint32            max_size;
    ordered_compare_t compare;
};

#endif

