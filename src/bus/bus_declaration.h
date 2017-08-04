#ifndef SRC_BUS_DECLARATION_H
#define SRC_BUS_DECLARATION_H

static inline uint32 io_bus_read_i(uint16 port, void *buf, uint32 size);
uint16 io_bus_read_word(uint16 port);
uint32 io_bus_dword_read(uint16 port);
uint32 io_bus_read(uint16 port, void *buf, uint32 size);
uint8 io_bus_byte_read(uint16 port);
void io_bus_byte_write(uint16 port, uint8 val);
void io_bus_dword_write(uint16 port, uint32 val);
void io_bus_write_word(uint16 port, uint16 val);

#endif
