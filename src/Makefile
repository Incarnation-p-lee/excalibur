SOURCES=boot.o main.o

CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32 -c
LDFLAGS=-Tlink.ld -m elf_i386
ASFLAGS=-felf

all: $(SOURCES)

clean:
	rm -rfv *.o kernel

link:
	ld $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) -o $@ $<
.c.o:
	cc $(CFLAGS) -o $@ $<

