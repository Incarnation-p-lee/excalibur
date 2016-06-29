#ifndef DATA_STRUCT_DECLARATION_H
#define DATA_STRUCT_DECLARATION_H


bool ordered_array_legal_p(s_ordered_array_t *ordered);
s_ordered_array_t ordered_array_create(uint32 max_size, ordered_compare_t compare);
s_ordered_array_t ordered_array_place(void *addr, uint32 max_size, ordered_compare_t compare);
sint32 ordered_array_standard_compare(const void *a, const void *b);
void * ordered_array_lookup(s_ordered_array_t *oa, uint32 idx);
void ordered_array_adjust(s_ordered_array_t *oa, uint32 idx);
void ordered_array_destroy(s_ordered_array_t *oa);
void ordered_array_insert(s_ordered_array_t *oa, void *val);
void ordered_array_remove(s_ordered_array_t *oa, uint32 idx);

#endif
