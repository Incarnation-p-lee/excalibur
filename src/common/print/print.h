#ifndef HAVE_DEFINED_PRINT_H
#define HAVE_DEFINED_PRINT_H

#define PRINT_BUF_SIZE             40960
#define BACKUP_BUF_SIZE            1024
#define PRINT_BUF_NAME             "excalibur_print_buf"

typedef struct print_buffer        s_pr_buf_t;
typedef struct print_backup_buffer s_pr_backup_buf_t;
typedef enum print_buffer_status   e_pr_buf_status_t;

enum print_buffer_status {
    BUFFER_FREE,
    BUFFER_BUSY,
    BUFFER_BACKUP,
};

struct print_backup_buffer {
    char   array[BACKUP_BUF_SIZE];
    uint32 index;
};

struct print_buffer {
    char              array[PRINT_BUF_SIZE];
    uint32            start;
    uint32            index;
    e_pr_buf_status_t status;
    s_pr_backup_buf_t backup;
};

static s_pr_buf_t print_buf = {
    {0,}, 0, 0, BUFFER_FREE, {{0,}, 0},
};

#endif

