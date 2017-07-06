static inline uint32
string_len_i(char *s)
{
    char *c;
    uint32 len;

    kassert(s);

    c = s;
    len = 1;

    while (*c++ != CHAR_NULL) {
       len++;
    }

    return len;
}

uint32
string_len(char *s)
{
    if (s == NULL) {
        return 0;
    } else {
        return string_len_i(s);
    }
}

static inline uint32
string_copy_i(char *d, char *s)
{
    char *c;

    kassert(d);
    kassert(s);

    c = s;

    while (*c != CHAR_NULL) {
        *d++ = *c++;
    }

    *d = CHAR_NULL;

    return (uint32)(c - s) + 1;
}

uint32
string_copy(char *d, char *s)
{
    if (d == NULL) {
        return 0;
    } else if (s == NULL) {
        return 0;
    } else {
        return string_copy_i(d, s);
    }
}

