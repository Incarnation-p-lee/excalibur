extern void screen_monitor_write(char *c);
extern void screen_monitor_clear(void);

int
main(struct multiboot *mboot_ptr)
{
     screen_monitor_clear();
     screen_monitor_write("Hello, The world of OS\n");

     return 0xdeadbaba;
}

