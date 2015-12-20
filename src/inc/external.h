#ifndef HAVE_DEFINED_EXTERNAL_H
#define HAVE_DEFINED_EXTERNAL_H

#include "common.h"

extern void screen_monitor_write_string(char *);
extern void screen_monitor_write_uint32(uint32);
extern void screen_monitor_clear(void);
extern void descriptor_table_idt_init(void);
extern void descriptor_table_gdt_init(uint32);

#endif

