#ifndef HAVE_DEFINED_SCREEN_H
#define HAVE_DEFINED_SCREEN_H

#define VGA_CTRL_REG    0x3D4
#define VGA_DATA_REG    0x3D5
#define VGA_CURSOR_HIGH 14
#define VGA_CURSOR_LOW  15

#define BLACK           0
#define BLUE            1
#define GREEN           2
#define CYAN            3
#define RED             4
#define MAGENTA         5
#define BROWN           6
#define L_GREY          7
#define D_GREY          8
#define L_BLUE          9
#define L_GREEN         10
#define L_CAYN          11
#define L_RED           12
#define L_MAGENTA       13
#define L_BROWN         14
#define WHITE           15

#define SCREEN_X        80
#define SCREEN_Y        25
#define SCREEN_X_BYTES  (sizeof(*video) * SCREEN_X)

#define BACKSPACE       0x8
#define H_TAB           0x9
#define NEW_LINE        0xA
#define CARRIAGE_RET    0xD
#define BLANK           0x20

extern void io_bus_write_byte(uint16 port, uint8 val);

static uint16 cursor_x = 0;
static uint16 cursor_y = 0;
/*
 * video memory start address of VGA controller dedicated.
 */
static uint16 *video = (uint16 *)0xB8000;

#endif

