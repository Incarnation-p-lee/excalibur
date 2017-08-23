#ifndef SRC_VFS_FS_INITRD_DECLARATION_H
#define SRC_VFS_FS_INITRD_DECLARATION_H

s_vfs_node_t * fs_initrd_file_create(char *name);
s_vfs_node_t * fs_initrd_vfs_node_root(void);
static inline bool fs_initrd_header_legal_p(s_initrd_header_t *header);
static inline char * fs_initrd_header_name(s_initrd_header_t *header);
static inline ptr_t fs_initrd_addr_start(void);
static inline s_initrd_header_t * fs_initrd_header(uint32 i);
static inline s_vfs_node_t * fs_initrd_file_create_i(char *name);
static inline s_vfs_node_t * fs_initrd_finddir(s_vfs_node_t *fs_node, char *name);
static inline s_vfs_node_t * fs_initrd_module_initialize(char *root_path, ptr_t location);
static inline s_vfs_node_t * fs_initrd_readdir(s_vfs_node_t *fs_node, uint32 index);
static inline s_vfs_node_t * fs_initrd_vfs_node_root_i(void);
static inline uint32 fs_initrd_header_count(ptr_t location);
static inline uint32 fs_initrd_header_inode_to_offset(uint32 inode);
static inline uint32 fs_initrd_header_length(s_initrd_header_t *header);
static inline uint32 fs_initrd_header_offset(s_initrd_header_t *header);
static inline uint32 fs_initrd_inode(void);
static inline uint32 fs_initrd_inode_allocate(void);
static inline uint32 fs_initrd_read(s_vfs_node_t *fs_node, uint32 offset, uint32 size, uint8 *buf);
static inline uint32 fs_initrd_write(s_vfs_node_t *vfs_node, uint32 offset, uint32 size, uint8 *buf);
static inline void fs_initrd_addr_start_set(ptr_t addr);
static inline void fs_initrd_header_count_inc(void);
static inline void fs_initrd_header_initialize(s_initrd_header_t *header, s_vfs_node_t *vfs_node);
static inline void fs_initrd_header_length_set(s_initrd_header_t *header, uint32 length);
static inline void fs_initrd_header_magic_set(s_initrd_header_t *header);
static inline void fs_initrd_header_name_copy(s_initrd_header_t *header, char *name);
static inline void fs_initrd_header_set(ptr_t location);
static inline void fs_initrd_initialize_i(s_vfs_node_t *root);
static inline void fs_initrd_inode_set(uint32 inode);
static inline void fs_initrd_vfs_root_node_set(s_vfs_node_t *node);
void fs_initrd_initialize(s_vfs_node_t *root);

#endif
