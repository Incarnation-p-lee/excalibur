int
main(char argc, char **argv)
{
    if (argv == NULL) {
        return -1;
    } else if (argc < 2) {
        return -1;
    } else if ((argc & 0x1) != 0x1) {
        return -1;
    } else {
        initrd_image_make(argc, argv);
        return 0;
    }
}

