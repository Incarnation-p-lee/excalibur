static inline bool
print_format_param_prefix_p(char c)
{
    if (c == '%') {
        return true;
    } else {
        return false;
    }
}

static inline s_print_buffer_t *
print_buffer(void)
{
    return &print_buf;
}

static inline void
print_buffer_start_set(void)
{
    s_print_buffer_t *pr_buf;

    pr_buf = print_buffer();

    pr_buf->start = pr_buf->index;
}

static inline char *
print_buffer_start(void)
{
    s_print_buffer_t *pr_buf;

    pr_buf = print_buffer();

    return pr_buf->buf + pr_buf->start;
}

static inline void
print_buffer_copy(char *s, uint32 len)
{
    char *buf;
    s_print_buffer_t *pr_buf;

    kassert(s);

    if (len) {
        pr_buf = print_buffer();
        buf = pr_buf->buf + pr_buf->index;

        kmemory_copy(buf, s, len);
        pr_buf->index += len;
    }
}

static inline void
print_buffer_uint32_copy(uint32 u)
{
    uint8 tmp;
    uint32 len;
    char buf[11];
    uint32 index;

    index = ARRAY_CNT_OF(buf) - 1;

    do {
        tmp = u % 10;
        tmp += CHAR_ZERO;

        buf[index--] = (char)tmp;
        u = u / 10;
    } while (u);

    index++;
    len = ARRAY_CNT_OF(buf) - index;

    print_buffer_copy(buf + index, len);
}

static inline void
print_buffer_uint32_hex_copy(uint32 u)
{
    uint8 tmp;
    char buf[10];
    uint32 index;

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

    print_buffer_copy(buf, ARRAY_CNT_OF(buf));
}

static inline void
print_buffer_string_copy(char *s)
{
    uint32 len;

    kassert(s);

    len = string_len(s);
    len--;

    print_buffer_copy(s, len);
}

static inline void
print_buffer_char_copy(char c)
{
    print_buffer_copy(&c, sizeof(c));
}

static inline uint32
print_format_placeholder_process(char placeholder, void *param)
{
    void *p;
    uint32 offset;

    kassert(param);

    p = param;
    offset = 0;

    switch (placeholder) {
        case 'd':
            print_buffer_uint32_copy(*(uint32 *)p);
            offset = sizeof(uint32);
            break;
        case 'x':
            print_buffer_uint32_hex_copy(*(uint32 *)p);
            offset = sizeof(uint32);
            break;
        case 's':
            print_buffer_string_copy(*(char **)p);
            offset = sizeof(char *);
            break;
        case 'c':
            print_buffer_char_copy(*(char *)p);
            offset = sizeof(char);
            break;
        default:
            KERNEL_PANIC("Unsupported print format.\n");
    }

    return offset;
}

static inline void
print_format_vga(void)
{
    s_print_buffer_t *pr_buf;

    pr_buf = print_buffer();

    pr_buf->buf[pr_buf->index] = CHAR_NULL;

    screen_monitor_write_string(print_buffer_start());
}

static inline void
print_format(char *format, void *param)
{
    void *p;
    uint32 len;
    char *s, *c;

    kassert(format);
    kassert(param);

    print_buffer_start_set();

    c = s = format;
    p = param;
    len = string_len(c);

    while (*c) {
        if (*c == '%') {
            len = (uint32)(c - s);
            print_buffer_copy(s, len);

            c++;
            p += print_format_placeholder_process(*c, p);
            s = c + 1;
        }

        c++;
    }

    len = (uint32)(c - s);
    print_buffer_copy(s, len);

    print_format_vga();
}

