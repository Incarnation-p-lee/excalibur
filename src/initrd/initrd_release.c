static inline bool
initrd_release_image_p(char argc, char **argv)
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

