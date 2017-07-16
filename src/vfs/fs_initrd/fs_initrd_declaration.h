#ifndef SRC_VFS_FS_INITRD_DECLARATION_H
#define SRC_VFS_FS_INITRD_DECLARATION_H

s_vfs_node_t * fs_initrd_initialize(ptr_t location);
static inline bool fs_initrd_header_legal_p(s_initrd_header_t *header);
static inline char * fs_initrd_header_name(s_initrd_header_t *header);
static inline ptr_t fs_initrd_addr_start(void);
static inline s_initrd_header_t * fs_initrd_header(uint32 i);
static inline s_vfs_node_t * fs_initrd_finddir(s_vfs_node_t *fs_node, char *name);
static inline s_vfs_node_t * fs_initrd_initialize_i(ptr_t location);
static inline s_vfs_node_t * fs_initrd_readdir(s_vfs_node_t *fs_node, uint32 index);
static inline uint32 fs_initrd_header_count(ptr_t location);
static inline uint32 fs_initrd_header_length(s_initrd_header_t *header);
static inline uint32 fs_initrd_read(s_vfs_node_t *fs_node, uint32 offset, uint32 size, uint8 *buf);
static inline uint32 fs_initrd_write(s_vfs_node_t *fs_node, uint32 offset, uint32 size, uint8 *buf);
static inline void fs_initrd_addr_start_set(ptr_t addr);
static inline void fs_initrd_header_set(ptr_t location);

#endif
