static inline bool
print_format_param_prefix_p(char c)
{
    if (c == '%') {
        return true;
    } else {
        return false;
    }
}

static inline bool
print_buffer_legal_p(s_pr_buf_t *pr_buf)
{
    if (pr_buf == NULL) {
        return false;
    } else if (pr_buf->index > PRINT_BUF_SIZE) {
        return false;
    } else if (pr_buf->start > pr_buf->index) {
        return false;
    } else {
        return true;
    }
}

static inline bool
print_backup_buffer_legal_p(s_pr_backup_buf_t *pr_backup_buf)
{
    if (pr_backup_buf == NULL) {
        return false;
    } else if (pr_backup_buf->index > BACKUP_BUF_SIZE) {
        return false;
    } else {
        return true;
    }
}

static inline bool
print_buffer_illegal_p(s_pr_buf_t *pr_buf)
{
    return !print_buffer_legal_p(pr_buf);
}

static inline bool
print_backup_buffer_illegal_p(s_pr_backup_buf_t *pr_backup_buf)
{
    return !print_backup_buffer_legal_p(pr_backup_buf);
}

static inline s_pr_buf_t *
print_buffer(void)
{
    return &print_buf;
}

static inline uint32
print_buffer_index(s_pr_buf_t *pr_buf)
{
    kassert(print_buffer_legal_p(pr_buf));

    return pr_buf->index;
}

static inline void
print_buffer_index_advance(s_pr_buf_t *pr_buf, uint32 len)
{
    kassert(print_buffer_legal_p(pr_buf));
    kassert(print_buffer_index(pr_buf) + len <= PRINT_BUF_SIZE);

    pr_buf->index += len;
}

static inline void
print_buffer_index_set(s_pr_buf_t *pr_buf, uint32 index)
{
    kassert(print_buffer_legal_p(pr_buf));
    kassert(index <= PRINT_BUF_SIZE);

    pr_buf->index = index;
}

static inline uint32
print_buffer_start(s_pr_buf_t *pr_buf)
{
    kassert(print_buffer_legal_p(pr_buf));

    return pr_buf->start;
}

static inline void
print_buffer_start_set(s_pr_buf_t *pr_buf, uint32 start)
{
    kassert(print_buffer_legal_p(pr_buf));
    kassert(start <= print_buffer_index(pr_buf));

    pr_buf->start = start;
}

static inline char *
print_buffer_array(s_pr_buf_t *pr_buf)
{
    kassert(print_buffer_legal_p(pr_buf));

    return pr_buf->array;
}

static inline char *
print_backup_buffer_array(s_pr_backup_buf_t *pr_backup_buf)
{
    kassert(print_backup_buffer_legal_p(pr_backup_buf));

    return pr_backup_buf->array;
}

static inline uint32
print_backup_buffer_index(s_pr_backup_buf_t *pr_backup_buf)
{
    kassert(print_backup_buffer_legal_p(pr_backup_buf));

    return pr_backup_buf->index;
}

static inline void
print_backup_buffer_index_set(s_pr_backup_buf_t *pr_backup_buf, uint32 index)
{
    kassert(print_backup_buffer_legal_p(pr_backup_buf));
    kassert(index <= BACKUP_BUF_SIZE);

    pr_backup_buf->index = index;
}

static inline uint32
print_buffer_critical_size(s_pr_buf_t *pr_buf)
{
    kassert(print_buffer_legal_p(pr_buf));

    return print_buffer_index(pr_buf) - print_buffer_start(pr_buf);
}

static inline void
print_buffer_copy(s_pr_buf_t *pr_buf, char *s, uint32 len)
{
    char *array;
    uint32 size;

    kassert(s);
    kassert(print_buffer_legal_p(pr_buf));

    array = print_buffer_array(pr_buf);

    if (len == 0) {
        return;
    } else if (print_buffer_index(pr_buf) + len >= PRINT_BUF_SIZE) {
        size = print_buffer_critical_size(pr_buf);
        kmemory_copy(array, array + print_buffer_start(pr_buf), size);
        print_buffer_index_set(pr_buf, size);
        print_buffer_start_set(pr_buf, 0);
    }

    kmemory_copy(array + print_buffer_index(pr_buf), s, len);
    print_buffer_index_advance(pr_buf, len);
}

static inline void
print_buffer_uint32_copy(s_pr_buf_t *pr_buf, uint32 u)
{
    uint8 tmp;
    uint32 len;
    char buf[11];
    uint32 index;

    kassert(print_buffer_legal_p(pr_buf));

    index = ARRAY_CNT_OF(buf) - 1;

    do {
        tmp = u % 10;
        tmp += CHAR_ZERO;

        buf[index--] = (char)tmp;
        u = u / 10;
    } while (u);

    index++;
    len = ARRAY_CNT_OF(buf) - index;

    print_buffer_copy(pr_buf, buf + index, len);
}

static inline void
print_buffer_uint32_hex_copy(s_pr_buf_t *pr_buf, uint32 u)
{
    uint8 tmp;
    char buf[10];
    uint32 index;

    kassert(print_buffer_legal_p(pr_buf));

    buf[0] = '0';
    buf[1] = 'x';
    index = ARRAY_CNT_OF(buf) - 1;

    while (u) {
        tmp = u % 16;

        if (tmp < 10) {
            tmp += CHAR_ZERO;
        } else {
            tmp = tmp - 10 + CHAR_a;
        }

        buf[index--] = (char)tmp;
        u = u / 16;
    }

    while (index > 1) {
        buf[index--] = CHAR_ZERO;
    }

    print_buffer_copy(pr_buf, buf, ARRAY_CNT_OF(buf));
}

static inline void
print_buffer_string_copy(s_pr_buf_t *pr_buf, char *s)
{
    uint32 len;

    kassert(s);
    kassert(print_buffer_legal_p(pr_buf));

    len = string_len(s);
    len--;

    print_buffer_copy(pr_buf, s, len);
}

static inline void
print_buffer_char_copy(s_pr_buf_t *pr_buf, char c)
{
    kassert(print_buffer_legal_p(pr_buf));

    print_buffer_copy(pr_buf, &c, sizeof(c));
}

static inline uint32
print_format_placeholder_process(s_pr_buf_t *pr_buf, char placeholder,
    void *param)
{
    void *p;
    uint32 offset;

    kassert(param);
    kassert(print_buffer_legal_p(pr_buf));

    p = param;
    offset = 0;

    switch (placeholder) {
        case 'd':
            print_buffer_uint32_copy(pr_buf, *(uint32 *)p);
            offset = sizeof(uint32);
            break;
        case 'x':
            print_buffer_uint32_hex_copy(pr_buf, *(uint32 *)p);
            offset = sizeof(uint32);
            break;
        case 's':
            print_buffer_string_copy(pr_buf, *(char **)p);
            offset = sizeof(char *);
            break;
        case 'c':
            print_buffer_char_copy(pr_buf, *(char *)p);
            offset = sizeof(char);
            break;
        default:
            KERNEL_PANIC("Unsupported print format.\n");
    }

    return offset;
}

static inline void
print_format_vga(s_pr_buf_t *pr_buf)
{
    char *s;
    char *array;
    uint32 index;

    kassert(print_buffer_legal_p(pr_buf));

    array = print_buffer_array(pr_buf);
    index = print_buffer_index(pr_buf);

    array[index] = CHAR_NULL;
    s = array + print_buffer_start(pr_buf);

    screen_monitor_string_write(s);
}

static inline void
print_format(s_pr_buf_t *pr_buf, char *format, void *param)
{
    void *p;
    uint32 len;
    char *s, *c;

    kassert(format);
    kassert(param);
    kassert(print_buffer_legal_p(pr_buf));

    print_buffer_start_set(pr_buf, print_buffer_index(pr_buf));

    c = s = format;
    p = param;

    while (*c) {
        if (*c == '%') {
            len = (uint32)(c++ - s);
            print_buffer_copy(pr_buf, s, len);

            p += print_format_placeholder_process(pr_buf, *c++, p);
            s = c;
        }

        c++;
    }

    len = (uint32)(c - s);
    print_buffer_copy(pr_buf, s, len);
    print_format_vga(pr_buf);
}

static inline bool
print_buffer_status_free_p(s_pr_buf_t *pr_buf)
{
    kassert(print_buffer_legal_p(pr_buf));

    if (pr_buf->status == BUFFER_FREE) {
        return true;
    } else {
        return false;
    }
}

static inline bool
print_buffer_status_busy_p(s_pr_buf_t *pr_buf)
{
    kassert(print_buffer_legal_p(pr_buf));

    if (pr_buf->status == BUFFER_BUSY) {
        return true;
    } else {
        return false;
    }
}

static inline bool
print_buffer_status_backup_p(s_pr_buf_t *pr_buf)
{
    kassert(print_buffer_legal_p(pr_buf));

    if (pr_buf->status == BUFFER_BACKUP) {
        return true;
    } else {
        return false;
    }
}

static inline void
print_buffer_status_set(s_pr_buf_t *pr_buf, e_pr_buf_status_t status)
{
    kassert(print_buffer_legal_p(pr_buf));

    pr_buf->status = status;
}

static inline s_pr_backup_buf_t *
print_backup_buffer(s_pr_buf_t *pr_buf)
{
    kassert(print_buffer_legal_p(pr_buf));

    return &pr_buf->backup;
}

static inline void
print_buffer_backup(s_pr_buf_t *pr_buf)
{
    uint32 size, start;
    char *array, *array_backup;
    s_pr_backup_buf_t *backup_buf;

    kassert(print_buffer_legal_p(pr_buf));
    kassert(print_buffer_status_busy_p(pr_buf));

    start = print_buffer_start(pr_buf);
    backup_buf = print_backup_buffer(pr_buf);
    array = print_buffer_array(pr_buf);
    array_backup = print_backup_buffer_array(backup_buf);

    if (print_buffer_index(pr_buf) == start) {
        return;
    } else {
        size = print_buffer_critical_size(pr_buf);
        kmemory_copy(array_backup, array + start, size);

        print_backup_buffer_index_set(backup_buf, size);
        print_buffer_index_set(pr_buf, start);
        print_buffer_status_set(pr_buf, BUFFER_BACKUP);
    }
}

static inline void
print_buffer_restore(s_pr_buf_t *pr_buf)
{
    uint32 size;
    char *array_backup;
    s_pr_backup_buf_t *backup_buf;

    kassert(print_buffer_legal_p(pr_buf));
    kassert(print_buffer_status_backup_p(pr_buf));

    backup_buf = print_backup_buffer(pr_buf);
    array_backup = print_backup_buffer_array(backup_buf);
    size = print_backup_buffer_index(backup_buf);

    print_buffer_start_set(pr_buf, print_buffer_index(pr_buf));
    print_buffer_copy(pr_buf, array_backup, size);

    print_backup_buffer_index_set(backup_buf, 0);
}

static inline void
print_internal(char *format, void *param)
{
    s_pr_buf_t *pr_buf;

    kassert(format);
    kassert(param);

    pr_buf = print_buffer();

    if (print_buffer_status_busy_p(pr_buf)) {
        print_buffer_backup(pr_buf);
    } else {
        kassert(print_buffer_status_free_p(pr_buf));
        print_buffer_status_set(pr_buf, BUFFER_BUSY);
    }

    print_format(pr_buf, format, param);

    if (print_buffer_status_backup_p(pr_buf)) {
        print_buffer_restore(pr_buf);
        print_buffer_status_set(pr_buf, BUFFER_BUSY);
    } else {
        kassert(print_buffer_status_busy_p(pr_buf));
        print_buffer_status_set(pr_buf, BUFFER_FREE);
    }
}

void
print_buffer_fs_initrd_write(void)
{
    char *array;
    uint32 length;
    s_pr_buf_t *pr_buf;
    s_vfs_node_t *vfs_node;

    pr_buf = print_buffer();
    array = print_buffer_array(pr_buf);
    length = print_buffer_index(pr_buf);

    vfs_node = fs_initrd_file_create(PRINT_BUF_NAME);
    vfs_write(vfs_node, 0, length, (void *)array);
}

