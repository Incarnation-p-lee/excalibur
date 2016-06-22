#!/bin/bash

sudo losetup /dev/loop0 floppy.img
sudo mount -v -t ext4 /dev/loop0 /mnt
sudo cp -v output/kernel /mnt/boot/kernel
sudo umount -v /dev/loop0
sudo losetup -v -d /dev/loop0

# ./configure --enable-debugger --enable-disasm --with-nogui
# bochs -q -f config/bochsrc.txt

