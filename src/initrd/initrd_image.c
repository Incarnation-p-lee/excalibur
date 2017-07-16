static inline s_initrd_header_t *
initrd_header_array_header(uint32 i)
{
    assert(i < ARRAY_CNT_OF(header_array));

    return &header_array[i];
}

static inline uint32
initrd_header_size(void)
{
    return sizeof(header_array) + sizeof(uint32);
}

static inline void
initrd_file_copy(FILE *fd, FILE *fs, s_initrd_header_t *header)
{
    uint8 *buf;
    uint32 length;

    assert(fd);
    assert(fs);
    assert(header);

    printf("Copy file %s -> length %x.\n", header->name, header->length);

    length = header->length;
    buf = malloc(length);

    fseek(fs, 0, SEEK_SET);
    fread(buf, length, 1, fs);
    fwrite(buf, length, 1, fd);

    free(buf);
}

static inline uint32
initrd_image_file_length(FILE *fd)
{
    assert(fd);

    fseek(fd, 0, SEEK_END);

    return ftell(fd);
}

static inline char *
initrd_image_file_basename(char *fullname)
{
    char *c;

    assert(fullname);

    c = strrchr(fullname, '/');

    if (c == NULL) {
        return fullname;
    } else {
        return c + 1;
    }
}

static inline void
initrd_header_initialize(s_initrd_header_t *header, char *fullname,
    uint32 *offset)
{
    FILE *fd;

    assert(header);
    assert(fullname);
    assert(offset);

    fd = fopen(fullname, "r");
    assert(fd);

    strcpy(header->name, initrd_image_file_basename(fullname));

    header->offset = *offset;
    header->magic = INITRD_MAGIC;
    header->length = initrd_image_file_length(fd);
    *offset += header->length;

    fclose(fd);
}

static inline void
initrd_image_make(uint32 argc, char **argv)
{
    char *name;
    FILE *fd, *fs;
    uint32 i, offset, limit;
    s_initrd_header_t *header;

    assert(argv);
    assert(argc > 1);
    assert(argc - 1 <= INITRD_HEADER_MAX);

    i = 0;
    limit = argc - 1;
    offset = initrd_header_size();

    fd = fopen(INITRD_NAME, "w");
    fwrite(&limit, sizeof(limit), 1, fd);

    while (i < limit) {
        name = argv[i + 1];
        header = initrd_header_array_header(i);
        initrd_header_initialize(header, name, &offset);

        i++;
    }

    i = 0;
    fwrite(header_array, sizeof(s_initrd_header_t), INITRD_HEADER_MAX, fd);

    while (i < limit) {
        name = argv[i + 1];
        header = initrd_header_array_header(i);

        fs = fopen(name, "r");
        initrd_file_copy(fd, fs, header);
        fclose(fs);

        i++;
    }

    fclose(fd);
}

static inline bool
initrd_image_release_p(uint32 argc, char **argv)
{
    assert(argv);

    if (argc != 2) {
        return false;
    } else if (strcmp(argv[1], INITRD_NAME) != 0) {
        return false;
    } else {
        return true;
    }
}

static inline void
initrd_image_release(char *name)
{
    FILE *fd;
    char *buf;
    uint32 length;
    uint32 i, limit;
    s_initrd_header_t *header;

    assert(name);
    assert(strcmp(name, INITRD_NAME) == 0);

    fd = fopen(INITRD_NAME, "r");

    length = initrd_image_file_length(fd);
    buf = malloc(length);
    fseek(fd, 0, SEEK_SET);
    fread(buf, length, 1, fd);
    fclose(fd);

    i = 0;
    limit = *(uint32 *)buf;
    header = (void *)(buf + sizeof(limit));

    while (i < limit) {
        fd = fopen(header->name, "w");
        fwrite(buf + header->offset, header->length, 1, fd);
        fclose(fd);
        printf("Release file %s -> length %x.\n", header->name, header->length);

        header++;
        i++;
    }

    free(buf);
}

