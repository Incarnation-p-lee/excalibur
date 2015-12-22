CFLAGS+=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32 -c
CFLAGS+=-I/home/pli/workspace/personal/excalibur/src/inc
ASFLAGS+=-felf

TARGET=isr.o
all:$(TARGET)

.s.o:
	nasm $(ASFLAGS) -o $@ $<
.c.o:
	cc $(CFLAGS) -o $@ $<
