#ifndef HAVE_DEFINED_PIC_H
#define HAVE_DEFINED_PIC_H


// The end of interrupt command
#define PIC_CMD_EOI             0x20
#define PIC_CMD_INIT            0x11

#define PIC_MASTER_CMD          0x20
#define PIC_SLAVE_CMD           0xA0
#define PIC_MASTER_DATA         0x21
#define PIC_SLAVE_DATA          0xA1

#define PIC_MASTER_REMAP_OFFSET 0x20
#define PIC_SLAVE_REMAP_OFFSET  0x28

#define PIC_8086                0x1

#endif

