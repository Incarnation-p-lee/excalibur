#ifndef SRC_BUS_DECLARATION_H
#define SRC_BUS_DECLARATION_H

uint16 io_bus_read_word(uint16 port);
uint32 io_bus_read_dword(uint16 port);
uint8 io_bus_read_byte(uint16 port);
void io_bus_write_byte(uint16 port, uint8 val);
void io_bus_write_dword(uint16 port, uint32 val);
void io_bus_write_word(uint16 port, uint16 val);

#endif
