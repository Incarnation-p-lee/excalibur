#!/bin/bash

sudo losetup /dev/loop0 floppy.img
sudo mount -v /dev/loop0 /mnt
sudo cp -v src/kernel /mnt/kernel
sudo umount -v /dev/loop0
sudo losetup -d /dev/loop0

# ./configure --enable-debugger --enable-disasm --with-nogui
# bochs -q -f config/bochsrc.txt

