include ../Makefile.in
CFLAGS += -I/home/pli/workspace/excalibur/src/inc

TARGET = bus.o
all:$(TARGET)

.s.o:
	nasm $(ASFLAGS) -o $@ $<
.c.o:
	cc $(CFLAGS) -o $@ $<
