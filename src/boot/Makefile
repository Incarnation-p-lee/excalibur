CFLAGS+=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32 -c
ASFLAGS+=-felf

TARGET=boot.o
all:$(TARGET)

.s.o:
	nasm $(ASFLAGS) -o $@ $<
.c.o:
	cc $(CFLAGS) -o $@ $<
