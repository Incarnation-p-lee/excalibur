static inline void
printf_k(char *format, void *param)
{
     uint32 len;
     char buf[PR_BUF_SIZE + 1];

     kassert(format);
     kassert(param);

     buf[PR_BUF_SIZE] = '\0';
     len = string_len(format);

     while (len > PR_BUF_SIZE) {
         kmemory_copy(buf, format, PR_BUF_SIZE);
         param = printf_k_one_buf(buf, param);
         len -= PR_BUF_SIZE;
         format += PR_BUF_SIZE;
     }

     if (len) {
         kmemory_copy(buf, format, len);
         printf_k_one_buf(buf, param);
     }
}

static inline void *
printf_k_one_buf(char *buf, void *base)
{
    char *s;
    char *trvl;

    kassert(buf);
    kassert(base);

    s = buf;
    trvl = buf;

    while ('\0' != *trvl) {
        if ('%' == *trvl) {
            *trvl = CHAR_NULL;
            screen_monitor_write_string(s);

            trvl++;
            switch (*trvl) {
                case 'd':
                    screen_monitor_write_uint32(*(uint32 *)base);
                    base += sizeof(uint32);
                    break;
                case 'x':
                    screen_monitor_write_uint32_hex(*(uint32 *)base);
                    base += sizeof(uint32);
                    break;
                case 's':
                    screen_monitor_write_string(*(char **)base);
                    base += sizeof(char *);
                    break;
                default:
                    break;
            }
            s = trvl + 1;
        }
        trvl++;
    }

    screen_monitor_write_string(s);

    return base;
}

