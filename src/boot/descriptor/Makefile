CFLAGS+=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32 -c
CFLAGS+=-I/home/pli/workspace/excalibur/src/inc
ASFLAGS+=-felf

TARGET=descriptor.o
all:$(TARGET)

.s.o:
	nasm $(ASFLAGS) -o $@ $<
.c.o:
	cc $(CFLAGS) -o $@ $<
