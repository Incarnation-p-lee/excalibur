int
main(int argc, char **argv)
{
    if (argv == NULL) {
        return -1;
    } else if (argc < 2) {
        return -1;
    } else if (initrd_image_release_p(argc, argv)) {
        initrd_image_release(INITRD_NAME);
        return 0;
    } else {
        initrd_image_make(argc, argv);
        return 0;
    }
}

