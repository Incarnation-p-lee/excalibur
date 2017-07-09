#ifndef SRC_SCREEN_DECLARATION_H
#define SRC_SCREEN_DECLARATION_H

static inline uint16 * screen_monitor_location(uint32 x, uint32 y);
static inline void screen_monitor_cursor_apply(void);
static inline void screen_monitor_one_line_scroll(void);
void screen_monitor_clear(void);
void screen_monitor_put_char(char c);
void screen_monitor_write_string(char *c);
void screen_monitor_write_uint32(uint32 u);
void screen_monitor_write_uint32_hex(uint32 u);

#endif
