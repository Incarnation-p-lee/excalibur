#ifndef SRC_DATA_STRUCT_DECLARATION_H
#define SRC_DATA_STRUCT_DECLARATION_H

bool linked_list_head_p(s_linked_list_t *node);
bool linked_list_tail_p(s_linked_list_t *node);
bool ordered_array_illegal_p(s_ordered_array_t *ordered);
bool ordered_array_legal_p(s_ordered_array_t *ordered);
s_linked_list_t * linked_list_insert_after(s_linked_list_t *node, s_linked_list_t *inserted);
s_linked_list_t * linked_list_insert_before(s_linked_list_t *node, s_linked_list_t *inserted);
s_linked_list_t * linked_list_next(s_linked_list_t *linked_list);
s_linked_list_t * linked_list_prev(s_linked_list_t *linked_list);
s_linked_list_t * linked_list_remove(s_linked_list_t *node);
s_ordered_array_t * ordered_array_create(uint32 size, ordered_compare_t compare);
sint32 ordered_array_standard_compare(const void *a, const void *b);
static inline bool linked_list_head_ip(s_linked_list_t *node);
static inline bool linked_list_illegal_p(s_linked_list_t *linked_list);
static inline bool linked_list_legal_p(s_linked_list_t *linked_list);
static inline bool linked_list_tail_ip(s_linked_list_t *node);
static inline bool ordered_array_empty_p(s_ordered_array_t *ordered_array);
static inline bool ordered_array_full_p(s_ordered_array_t *ordered);
static inline bool ordered_array_illegal_ip(s_ordered_array_t *ordered);
static inline bool ordered_array_index_last_p(s_ordered_array_t *ordered_array, uint32 i);
static inline bool ordered_array_legal_ip(s_ordered_array_t *ordered);
static inline bool ordered_array_next_suitable_p(s_ordered_array_t *ordered_array, uint32 i);
static inline bool ordered_array_prev_suitable_p(s_ordered_array_t *ordered_array, uint32 i);
static inline bool ordered_array_suitable_p(s_ordered_array_t *ordered_array, uint32 i);
static inline s_linked_list_t * linked_list_insert_after_i(s_linked_list_t *node, s_linked_list_t *inserted);
static inline s_linked_list_t * linked_list_insert_before_i(s_linked_list_t *node, s_linked_list_t *inserted);
static inline s_linked_list_t * linked_list_next_i(s_linked_list_t *linked_list);
static inline s_linked_list_t * linked_list_prev_i(s_linked_list_t *linked_list);
static inline s_linked_list_t * linked_list_remove_i(s_linked_list_t *node);
static inline uint32 ordered_array_index_last(s_ordered_array_t *ordered_array);
static inline uint32 ordered_array_limit_i(s_ordered_array_t *ordered_array);
static inline uint32 ordered_array_size(s_ordered_array_t *ordered_array);
static inline uint32 ordered_array_value_index_find_i(s_ordered_array_t *ordered_array, void *val);
static inline void * ordered_array_value_i(s_ordered_array_t *ordered_array, uint32 i);
static inline void linked_list_initialize_i(s_linked_list_t *node);
static inline void ordered_array_adjust_i(s_ordered_array_t *ordered_array, uint32 i);
static inline void ordered_array_dec(s_ordered_array_t *ordered_array);
static inline void ordered_array_inc(s_ordered_array_t *ordered_array);
static inline void ordered_array_insert_i(s_ordered_array_t *ordered_array, void *val);
static inline void ordered_array_next_adjust(s_ordered_array_t *ordered_array, uint32 i);
static inline void ordered_array_prev_adjust(s_ordered_array_t *ordered_array, uint32 i);
static inline void ordered_array_remove_i(s_ordered_array_t *ordered_array, uint32 i);
static inline void ordered_array_value_append(s_ordered_array_t *ordered_array, void *val);
static inline void ordered_array_value_set(s_ordered_array_t *ordered_array, uint32 i, void *val);
uint32 ordered_array_limit(s_ordered_array_t *ordered_array);
uint32 ordered_array_value_index_find(s_ordered_array_t *ordered_array, void *val);
void * ordered_array_place(s_ordered_array_t *ordered_array, void *addr, uint32 size, ordered_compare_t compare);
void * ordered_array_value(s_ordered_array_t *ordered_array, uint32 i);
void linked_list_initialize(s_linked_list_t *node);
void ordered_array_adjust(s_ordered_array_t *ordered_array, uint32 i);
void ordered_array_destroy(s_ordered_array_t *oa);
void ordered_array_insert(s_ordered_array_t *ordered_array, void *val);
void ordered_array_remove(s_ordered_array_t *ordered_array, uint32 i);

#endif
