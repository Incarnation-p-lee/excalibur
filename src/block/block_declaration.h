#ifndef SRC_BLOCK_DECLARATION_H
#define SRC_BLOCK_DECLARATION_H

bool block_buffer_illegal_p(s_block_buf_t *block_buffer);
bool block_buffer_legal_p(s_block_buf_t *block_buffer);
s_block_buf_t * block_buffer_create(uint32 size);
static inline bool block_buffer_illegal_ip(s_block_buf_t *block_buffer);
static inline bool block_buffer_legal_ip(s_block_buf_t *block_buffer);
static inline s_block_buf_t * block_buffer_create_i(uint32 size);
static inline uint32 block_buffer_copy_i(void *d, s_block_buf_t *block_buf, uint32 offset, uint32 size);
static inline uint32 block_buffer_index_i(s_block_buf_t *block_buffer);
static inline uint32 block_buffer_limit_i(s_block_buf_t *block_buffer);
static inline uint32 block_buffer_size_i(s_block_buf_t *block_buffer);
static inline uint8 * block_buffer_array_i(s_block_buf_t *block_buffer);
static inline void block_buffer_array_set_i(s_block_buf_t *block_buffer, uint8 *array);
static inline void block_buffer_destroy_i(s_block_buf_t *block_buf);
static inline void block_buffer_dword_append_i(s_block_buf_t *block_buf, uint32 val);
static inline void block_buffer_index_set_i(s_block_buf_t *block_buffer, uint32 index);
static inline void block_buffer_size_set_i(s_block_buf_t *block_buffer, uint32 size);
uint32 block_buffer_copy(void *d, s_block_buf_t *block_buf, uint32 offset, uint32 size);
uint32 block_buffer_index(s_block_buf_t *block_buffer);
uint32 block_buffer_limit(s_block_buf_t *block_buffer);
uint32 block_buffer_size(s_block_buf_t *block_buffer);
uint8 * block_buffer_array(s_block_buf_t *block_buffer);
void block_buffer_array_set(s_block_buf_t *block_buffer, uint8 *array);
void block_buffer_destroy(s_block_buf_t **block_buf);
void block_buffer_dword_append(s_block_buf_t *block_buf, uint32 val);
void block_buffer_index_set(s_block_buf_t *block_buffer, uint32 index);
void block_buffer_size_set(s_block_buf_t *block_buffer, uint32 size);
void block_initialize(void);

#endif
