static inline void
screen_monitor_cursor_apply(void)
{
    uint16 cursor;

    cursor = cursor_y * 80 + cursor_x;

    io_bus_write_byte(VGA_CTRL_REG, VGA_CURSOR_HIGH);
    io_bus_write_byte(VGA_DATA_REG, cursor >> 8);

    io_bus_write_byte(VGA_CTRL_REG, VGA_CURSOR_LOW);
    io_bus_write_byte(VGA_DATA_REG, cursor);
}

static inline void
screen_monitor_one_line_scroll(void)
{
    uint8 attribute;
    uint16 blank;
    uint32 i;

    attribute = (BLACK << 4) | WHITE;
    blank = BLANK | (attribute << 8);

    if (cursor_y >= 25) {
        i = 0;

        /*
         * mov up one line
         */
        while (i < (SCREEN_Y - 1) * SCREEN_X) {
            video[i] = video[i + SCREEN_X];
            i++;
        }

        /*
         * set the last one line to blank
         */
        memory_set_k(video[i], blank, SCREEN_X);
        cursor_y = SCREEN_Y - 1;
        memory_set_k(video[SCREEN_X * SCREEN_Y], blank, SCREEN_X);
    }
}

void
screen_monitor_put_char(char c)
{
    uint16 attribute;
    uint16 *location;

    attribute = ((BLACK << 4) | WHITE) << 8;

    if (BACKSPACE == c) {
        cursor_x--;
    } else if (H_TAB == c) {
        cursor_x = (cursor_x + 8) & ~(8 - 1);
    } else if (CARRIAGE_RET == c) { /* '\r' */
        cursor_x = 0;
    } else if (NEW_LINE == c) { /* '\n' */
        cursor_x = 0;
        cursor_y++;
    } else if (c >= BLANK) {
        location = video + (cursor_y * 80 + cursor_x);
        *location = c | attribute;
        cursor_x++;
    }

    if (cursor_x >= 80) {
        cursor_x = 0;
        cursor_y++;
    }

    screen_monitor_one_line_scroll();
    screen_monitor_cursor_apply();
}

void
screen_monitor_clear(void)
{
    uint32 i;
    uint16 blank;

    i = 0;
    blank = (((BLACK << 4) | WHITE) << 8) | BLANK;

    while (i < SCREEN_X * SCREEN_Y) {
        video[i++] = blank;
    }

    cursor_x = 0;
    cursor_y = 0;

    screen_monitor_cursor_apply();
}

void
screen_monitor_write_string(char *c)
{
    int i;

    i = 0;
    while (c[i]) {
        screen_monitor_put_char(c[i++]);
    }
}

void
screen_monitor_write_uint32(uint32 u)
{
    uint32 index;
    char buf[9];
    uint32 tmp;

    screen_monitor_write_string("0x");

    index = 0;
    while (index < ARRAY_CNT_OF(buf)) {
        buf[index++] = CHAR_ZERO;
    }
    buf[--index] = CHAR_NULL;

    while (u) {
        tmp = u % 16;

        if (tmp < 10) {
            tmp += CHAR_ZERO;        // Offset to char 0 - 9.
        } else {
            tmp = tmp - 10 + CHAR_a; // Offset to char a - f.
        }

        buf[--index] = (char)tmp;
        u = u >> 4;
    }

    screen_monitor_write_string(buf);
}

