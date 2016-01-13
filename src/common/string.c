uint32
string_len_k(char *s)
{
    uint32 len;
    char *trvl;

    len = 0;

    if (s) {
        trvl = s;

        while (CHAR_NULL != *trvl++) {
            len++;
        }

        len++;
    }

    return len;
}

