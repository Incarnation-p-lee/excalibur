#ifndef SRC_INITRD_DECLARATION_H
#define SRC_INITRD_DECLARATION_H

int main(int argc, char **argv);
static inline bool initrd_image_release_p(uint32 argc, char **argv);
static inline char * initrd_image_file_basename(char *fullname);
static inline s_initrd_header_t * initrd_header_array_header(uint32 i);
static inline uint32 initrd_header_size(void);
static inline uint32 initrd_image_file_length(FILE *fd);
static inline void initrd_file_copy(FILE *fd, FILE *fs, s_initrd_header_t *header);
static inline void initrd_header_initialize(s_initrd_header_t *header, char *fullname, uint32 *offset);
static inline void initrd_image_make(uint32 argc, char **argv);
static inline void initrd_image_release(char *name);

#endif
