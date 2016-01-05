#ifndef BUS_DECLARATION_H
#define BUS_DECLARATION_H


uint16 io_bus_read_word(uint16 port);
uint8 io_bus_read_byte(uint16 port);
void io_bus_write_byte(uint16 port, uint8 val);

#endif
