static inline s_initrd_header_t *
initrd_header_array_header(uint32 i)
{
    assert(i < ARRAY_CNT_OF(header_array));

    return &header_array[i];
}

static inline uint32
initrd_header_size(void)
{
    return sizeof(header_array) + sizeof(ARRAY_CNT_OF(header_array));
}

static inline uint32
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

    i = 1;
    limit = argc;
    offset = initrd_header_size();

    fd = fopen(INITRD_NAME, "w");
    fwrite(header_array, sizeof(s_initrd_header_t), INITRD_HEADER_MAX, fd);
    fwrite(&limit, sizeof(limit), 1, fd);

    while (i < limit) {
        name = argv[i];
        header = initrd_header_array_header(i);

        fs = fopen(name, "r");
        if (fs == NULL) {
            printf("Failed to locate file %s.\n", name);
        }

        strcpy(header->name, name);

        fseek(fs, 0, SEEK_END);

        header->offset = offset;
        header->magic = INITRD_MAGIC;
        header->length = ftell(fd);
        offset += header->length;

        initrd_file_copy(fd, fs, header);
        fclose(fs);

        i++;
    }

    fclose(fd);
}

