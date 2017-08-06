#ifndef SRC_DISK_DECLARATION_H
#define SRC_DISK_DECLARATION_H

bool disk_buffer_illegal_p(s_disk_buf_t *disk_buf);
bool disk_buffer_legal_p(s_disk_buf_t *disk_buf);
static inline bool disk_buffer_illegal_ip(s_disk_buf_t *disk_buf);
static inline bool disk_buffer_legal_ip(s_disk_buf_t *disk_buf);
static inline uint32 disk_buffer_index(s_disk_buf_t *disk_buf);
static inline uint32 disk_buffer_limit(s_disk_buf_t *disk_buf);
static inline uint32 disk_buffer_size_i(s_disk_buf_t *disk_buf);
static inline void * disk_buffer_obtain_i(s_disk_buf_t *disk_buf);
static inline void disk_buffer_dword_append_i(s_disk_buf_t *disk_buf, uint32 val);
static inline void disk_buffer_index_set_i(s_disk_buf_t *disk_buf, uint32 index);
uint32 disk_buffer_size(s_disk_buf_t *disk_buf);
void * disk_buffer_obtain(s_disk_buf_t *disk_buf);
void disk_buffer_dword_append(s_disk_buf_t *disk_buf, uint32 val);
void disk_buffer_index_set(s_disk_buf_t *disk_buf, uint32 index);
void disk_initialize(void);

#endif
