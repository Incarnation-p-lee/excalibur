#ifndef SRC_DISK_DECLARATION_H
#define SRC_DISK_DECLARATION_H

bool disk_buffer_illegal_p(s_disk_buf_t *disk_buffer);
bool disk_buffer_legal_p(s_disk_buf_t *disk_buffer);
s_disk_buf_t * disk_buffer_create(uint32 size);
static inline bool disk_buffer_illegal_ip(s_disk_buf_t *disk_buffer);
static inline bool disk_buffer_legal_ip(s_disk_buf_t *disk_buffer);
static inline s_disk_buf_t * disk_buffer_create_i(uint32 size);
static inline uint32 disk_buffer_index_i(s_disk_buf_t *disk_buffer);
static inline uint32 disk_buffer_limit_i(s_disk_buf_t *disk_buffer);
static inline uint32 disk_buffer_size_i(s_disk_buf_t *disk_buffer);
static inline uint8 * disk_buffer_array_i(s_disk_buf_t *disk_buffer);
static inline void disk_buffer_array_set_i(s_disk_buf_t *disk_buffer, uint8 *array);
static inline void disk_buffer_destroy_i(s_disk_buf_t *disk_buf);
static inline void disk_buffer_dword_append_i(s_disk_buf_t *disk_buf, uint32 val);
static inline void disk_buffer_index_set_i(s_disk_buf_t *disk_buffer, uint32 index);
static inline void disk_buffer_size_set_i(s_disk_buf_t *disk_buffer, uint32 size);
uint32 disk_buffer_index(s_disk_buf_t *disk_buffer);
uint32 disk_buffer_limit(s_disk_buf_t *disk_buffer);
uint32 disk_buffer_size(s_disk_buf_t *disk_buffer);
uint8 * disk_buffer_array(s_disk_buf_t *disk_buffer);
void disk_buffer_array_set(s_disk_buf_t *disk_buffer, uint8 *array);
void disk_buffer_destroy(s_disk_buf_t **disk_buf);
void disk_buffer_dword_append(s_disk_buf_t *disk_buf, uint32 val);
void disk_buffer_index_set(s_disk_buf_t *disk_buffer, uint32 index);
void disk_buffer_size_set(s_disk_buf_t *disk_buffer, uint32 size);
void disk_initialize(void);

#endif
