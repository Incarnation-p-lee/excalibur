#ifndef SRC_VFS_DECLARATION_H
#define SRC_VFS_DECLARATION_H

s_directory_t * filesystem_readdir(s_fs_node_t *fs_node, uint32 index);
static inline bool filesystem_node_closable_p(s_fs_node_t *fs_node);
static inline bool filesystem_node_dir_findable_p(s_fs_node_t *fs_node);
static inline bool filesystem_node_dir_readable_p(s_fs_node_t *fs_node);
static inline bool filesystem_node_dir_unfindable_p(s_fs_node_t *fs_node);
static inline bool filesystem_node_dir_unreadable_p(s_fs_node_t *fs_node);
static inline bool filesystem_node_directory_p(s_fs_node_t *fs_node);
static inline bool filesystem_node_illegal_p(s_fs_node_t *fs_node);
static inline bool filesystem_node_legal_p(s_fs_node_t *fs_node);
static inline bool filesystem_node_not_directory_p(s_fs_node_t *fs_node);
static inline bool filesystem_node_openable_p(s_fs_node_t *fs_node);
static inline bool filesystem_node_readable_p(s_fs_node_t *fs_node);
static inline bool filesystem_node_unclosable_p(s_fs_node_t *fs_node);
static inline bool filesystem_node_unopenable_p(s_fs_node_t *fs_node);
static inline bool filesystem_node_unreadable_p(s_fs_node_t *fs_node);
static inline bool filesystem_node_unwritable_p(s_fs_node_t *fs_node);
static inline bool filesystem_node_writable_p(s_fs_node_t *fs_node);
uint32 filesystem_close(s_fs_node_t *fs_node);
uint32 filesystem_open(s_fs_node_t *fs_node);
uint32 filesystem_read(s_fs_node_t *fs_node, uint32 offset, uint32 size, uint8 *buf);
uint32 filesystem_write(s_fs_node_t *fs_node, uint32 offset, uint32 size, uint8 *buf);

#endif
