#ifndef DATA_STRUCT_DECLARATION_H
#define DATA_STRUCT_DECLARATION_H


bool ordered_array_legal_p(s_ordered_array_t *ordered);
sint32 ordered_array_standard_compare(const void *a, const void *b);
struct ordered_array ordered_array_create(uint32 max_size, ordered_compare_t compare);
struct ordered_array ordered_array_place(void *addr, uint32 max_size, ordered_compare_t compare);
void * ordered_array_lookup(struct ordered_array *oa, uint32 idx);
void ordered_array_adjust(struct ordered_array *oa, uint32 idx);
void ordered_array_destroy(struct ordered_array *oa);
void ordered_array_insert(struct ordered_array *oa, void *val);
void ordered_array_remove(struct ordered_array *oa, uint32 idx);

#endif
