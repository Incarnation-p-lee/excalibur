#ifndef SRC_SCREEN_DECLARATION_H
#define SRC_SCREEN_DECLARATION_H

static inline uint16 * screen_monitor_location(uint32 x, uint32 y);
static inline void screen_monitor_cursor_apply(void);
static inline void screen_monitor_one_line_scroll(void);
static inline void screen_monitor_put_char(char c);
void screen_monitor_char_write(char c);
void screen_monitor_clear(void);
void screen_monitor_string_write(char *c);

#endif
