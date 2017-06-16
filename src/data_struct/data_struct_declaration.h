#ifndef SRC_DATA_STRUCT_DECLARATION_H
#define SRC_DATA_STRUCT_DECLARATION_H

bool ordered_array_illegal_p(s_ordered_array_t *ordered);
bool ordered_array_legal_p(s_ordered_array_t *ordered);
s_ordered_array_t * ordered_array_create(uint32 size, ordered_compare_t compare);
sint32 ordered_array_standard_compare(const void *a, const void *b);
static inline bool ordered_array_empty_p(s_ordered_array_t *ordered_array);
static inline bool ordered_array_full_p(s_ordered_array_t *ordered);
static inline bool ordered_array_illegal_ip(s_ordered_array_t *ordered);
static inline bool ordered_array_index_last_p(s_ordered_array_t *ordered_array, uint32 i);
static inline bool ordered_array_legal_ip(s_ordered_array_t *ordered);
static inline bool ordered_array_next_suitable_p(s_ordered_array_t *ordered_array, uint32 i);
static inline bool ordered_array_prev_suitable_p(s_ordered_array_t *ordered_array, uint32 i);
static inline bool ordered_array_suitable_p(s_ordered_array_t *ordered_array, uint32 i);
static inline uint32 ordered_array_index_last(s_ordered_array_t *ordered_array);
static inline uint32 ordered_array_limit(s_ordered_array_t *ordered_array);
static inline uint32 ordered_array_size(s_ordered_array_t *ordered_array);
static inline void * ordered_array_value_i(s_ordered_array_t *ordered_array, uint32 i);
static inline void ordered_array_adjust_i(s_ordered_array_t *ordered_array, uint32 i);
static inline void ordered_array_dec(s_ordered_array_t *ordered_array);
static inline void ordered_array_inc(s_ordered_array_t *ordered_array);
static inline void ordered_array_insert_i(s_ordered_array_t *ordered_array, void *val);
static inline void ordered_array_next_adjust(s_ordered_array_t *ordered_array, uint32 i);
static inline void ordered_array_prev_adjust(s_ordered_array_t *ordered_array, uint32 i);
static inline void ordered_array_remove_i(s_ordered_array_t *ordered_array, uint32 i);
static inline void ordered_array_value_append(s_ordered_array_t *ordered_array, void *val);
static inline void ordered_array_value_set(s_ordered_array_t *ordered_array, uint32 i, void *val);
void * ordered_array_value(s_ordered_array_t *ordered_array, uint32 i);
void ordered_array_adjust(s_ordered_array_t *ordered_array, uint32 i);
void ordered_array_destroy(s_ordered_array_t *oa);
void ordered_array_insert(s_ordered_array_t *ordered_array, void *val);
void ordered_array_remove(s_ordered_array_t *ordered_array, uint32 i);

#endif
