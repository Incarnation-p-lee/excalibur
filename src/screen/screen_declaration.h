#ifndef SCREEN_DECLARATION_H
#define SCREEN_DECLARATION_H

static inline void screen_monitor_cursor_move(void);
static inline void screen_monitor_one_line_scroll(void);
uint16 screen_io_read_port_word(uint16 port);
uint8 screen_io_read_port_byte(uint16 port);
void screen_io_write_port_byte(uint16 port, uint8 val);
void screen_monitor_clear(void);
void screen_monitor_put_char(char c);
void screen_monitor_write_string(char *c);
void screen_monitor_write_uint32(uint32 u);

#endif
