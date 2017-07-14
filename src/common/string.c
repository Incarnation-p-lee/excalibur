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

static inline char *
string_basename_i(char *fullname)
{
    char *c;
    char *basename;

    kassert(fullname);

    c = basename = fullname;

    while (*c) {
        if (*c == CHAR_SLASH) {
            basename = c + 1;
        }

        c++;
    }

    return basename;
}

char *
string_basename(char *fullname)
{
    if (fullname == NULL) {
        return PTR_INVALID;
    } else {
        return string_basename_i(fullname);
    }
}

static inline sint32
string_compare_i(char *a, char *b)
{
    kassert(a);
    kassert(b);

    while (*a && *b) {
        if (*a > *b) {
            return 1;
        } else if (*a < *b) {
            return -1;
        } else {
            a++;
            b++;
        }
    }

    if (*a) {
        return 1;
    } else if (*b) {
        return -1;
    } else {
        return 0;
    }
}

sint32
string_compare(char *a, char *b)
{
    if (a == NULL && b == NULL) {
        return 0;
    } else if (a == NULL) {
        return -1;
    } else if (b == NULL) {
        return 1;
    } else {
        return string_compare_i(a, b);
    }
}

