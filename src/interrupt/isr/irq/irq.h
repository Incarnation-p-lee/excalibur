#ifndef HAVE_DEFINED_IRQ_H
#define HAVE_DEFINED_IRQ_H

#define IRQ_1_KEYBOARD_DATA      0x60
#define IRQ_1_KEYBOARD_STATUS    0x64
#define IRQ_1_KEYBOARD_CMD       0x64
#define IRQ_1_KEYBOARD_KEY_MASK  0x7f
#define IRQ_1_KEYBOARD_REL_MASK  0x80 /* Release mask */

#define KEYBOARD_PRESSED_MAX     8
#define KEYBOARD_KEY_NULL        0

typedef struct keyboard_data     s_keyboard_data_t;
typedef struct keyboard_pressed  s_keyboard_pressed_t;
typedef struct key_ascii_map     s_key_ascii_map_t;

enum KEYBOARD_KEY {
    KEYBOARD_KEY_0       = 0x0b,
    KEYBOARD_KEY_1       = 0x02,
    KEYBOARD_KEY_2       = 0x03,
    KEYBOARD_KEY_3       = 0x04,
    KEYBOARD_KEY_4       = 0x05,
    KEYBOARD_KEY_5       = 0x06,
    KEYBOARD_KEY_6       = 0x07,
    KEYBOARD_KEY_7       = 0x08,
    KEYBOARD_KEY_8       = 0x09,
    KEYBOARD_KEY_9       = 0x0a,

    KEYBOARD_KEY_Q       = 0x10,
    KEYBOARD_KEY_W       = 0x11,
    KEYBOARD_KEY_E       = 0x12,
    KEYBOARD_KEY_R       = 0x13,
    KEYBOARD_KEY_T       = 0x14,
    KEYBOARD_KEY_Y       = 0x15,
    KEYBOARD_KEY_U       = 0x16,
    KEYBOARD_KEY_I       = 0x17,
    KEYBOARD_KEY_O       = 0x18,
    KEYBOARD_KEY_P       = 0x19,

    KEYBOARD_KEY_A       = 0x1e,
    KEYBOARD_KEY_S       = 0x1f,
    KEYBOARD_KEY_D       = 0x20,
    KEYBOARD_KEY_F       = 0x21,
    KEYBOARD_KEY_G       = 0x22,
    KEYBOARD_KEY_H       = 0x23,
    KEYBOARD_KEY_J       = 0x24,
    KEYBOARD_KEY_K       = 0x25,
    KEYBOARD_KEY_L       = 0x26,

    KEYBOARD_KEY_Z       = 0x2c,
    KEYBOARD_KEY_X       = 0x2d,
    KEYBOARD_KEY_C       = 0x2e,
    KEYBOARD_KEY_V       = 0x2f,
    KEYBOARD_KEY_B       = 0x30,
    KEYBOARD_KEY_N       = 0x31,
    KEYBOARD_KEY_M       = 0x32,

    KEYBOARD_KEY_SHIFT_L = 0x2A,
    KEYBOARD_KEY_SHIFT_R = 0x36,
};

struct keyboard_data {
    uint8 key:7;
    uint8 release:1;
};

struct keyboard_pressed {
    uint8  array[KEYBOARD_PRESSED_MAX];
};

struct key_ascii_map {
    uint8 ascii;
    uint8 shifted;
};

static uint32 tick;
static s_keyboard_pressed_t keyboard_pressed;

static const s_key_ascii_map_t ascii_map[] = {
    [KEYBOARD_KEY_0] = {'0', ')'},
    [KEYBOARD_KEY_1] = {'1', '!'},
    [KEYBOARD_KEY_2] = {'2', '@'},
    [KEYBOARD_KEY_3] = {'3', '#'},
    [KEYBOARD_KEY_4] = {'4', '$'},
    [KEYBOARD_KEY_5] = {'5', '%'},
    [KEYBOARD_KEY_6] = {'6', '^'},
    [KEYBOARD_KEY_7] = {'7', '&'},
    [KEYBOARD_KEY_8] = {'8', '*'},
    [KEYBOARD_KEY_9] = {'9', '('},

    [KEYBOARD_KEY_Q] = {'q', 'Q'},
    [KEYBOARD_KEY_W] = {'w', 'W'},
    [KEYBOARD_KEY_E] = {'e', 'E'},
    [KEYBOARD_KEY_R] = {'r', 'R'},
    [KEYBOARD_KEY_T] = {'t', 'T'},
    [KEYBOARD_KEY_Y] = {'y', 'Y'},
    [KEYBOARD_KEY_U] = {'u', 'U'},
    [KEYBOARD_KEY_I] = {'i', 'I'},
    [KEYBOARD_KEY_O] = {'o', 'O'},
    [KEYBOARD_KEY_P] = {'q', 'Q'},

    [KEYBOARD_KEY_A] = {'a', 'A'},
    [KEYBOARD_KEY_S] = {'s', 'S'},
    [KEYBOARD_KEY_D] = {'d', 'D'},
    [KEYBOARD_KEY_F] = {'f', 'F'},
    [KEYBOARD_KEY_G] = {'g', 'G'},
    [KEYBOARD_KEY_H] = {'h', 'H'},
    [KEYBOARD_KEY_J] = {'j', 'J'},
    [KEYBOARD_KEY_K] = {'k', 'K'},
    [KEYBOARD_KEY_L] = {'l', 'L'},

    [KEYBOARD_KEY_Z] = {'z', 'Z'},
    [KEYBOARD_KEY_X] = {'x', 'X'},
    [KEYBOARD_KEY_C] = {'c', 'C'},
    [KEYBOARD_KEY_V] = {'v', 'V'},
    [KEYBOARD_KEY_B] = {'b', 'B'},
    [KEYBOARD_KEY_N] = {'n', 'N'},
    [KEYBOARD_KEY_M] = {'m', 'M'},
};

#endif

