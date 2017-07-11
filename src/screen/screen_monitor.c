static inline void
screen_monitor_cursor_apply(void)
{
    uint16 cursor;

    cursor = cursor_y * SCREEN_X + cursor_x;

    io_bus_write_byte(VGA_CTRL_REG, VGA_CURSOR_HIGH);
    io_bus_write_byte(VGA_DATA_REG, cursor >> 8);

    io_bus_write_byte(VGA_CTRL_REG, VGA_CURSOR_LOW);
    io_bus_write_byte(VGA_DATA_REG, cursor);
}

static inline uint16 *
screen_monitor_location(uint32 x, uint32 y)
{
    kassert(x < SCREEN_X);
    kassert(x < SCREEN_Y);

    return &video[y * SCREEN_X + x];
}

static inline void
screen_monitor_one_line_scroll(void)
{
    uint32 i;
    uint16 blank;
    uint8 attribute;
    uint16 *line, *line_next;

    i = 0;

    while (i < SCREEN_Y - 1) {
        line = screen_monitor_location(0, i);
        line_next = screen_monitor_location(0, i + 1);

        kmemory_copy(line, line_next, SCREEN_X_BYTES);
        i++;
    }

    attribute = (BLACK << 4) | WHITE;
    blank = BLANK | (attribute << 8);

    cursor_y = SCREEN_Y - 1;
    line = screen_monitor_location(0, SCREEN_Y - 1);
    kmemset_u16(line, blank, SCREEN_X); // Bug here.
}

static inline void
screen_monitor_put_char(char c)
{
    uint16 attribute;
    uint16 *location;

    attribute = ((BLACK << 4) | WHITE) << 8;

    if (c == BACKSPACE) {
        cursor_x--;
    } else if (c == H_TAB) {
        cursor_x = (cursor_x + 8) & ~(8 - 1);
    } else if (c == CARRIAGE_RET) { /* '\r' */
        cursor_x = 0;
    } else if (c == NEW_LINE) { /* '\n' */
        cursor_x = 0;
        cursor_y++;
    } else if (c >= BLANK) {
        location = video + (cursor_y * SCREEN_X + cursor_x);
        *location = c | attribute;
        cursor_x++;
    }

    if (cursor_x >= SCREEN_X) {
        cursor_x = 0;
        cursor_y++;
    }

    if (cursor_y >= SCREEN_Y) {
        screen_monitor_one_line_scroll();
    }

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

