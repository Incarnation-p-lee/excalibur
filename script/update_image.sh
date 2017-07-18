#!/bin/bash

sudo losetup /dev/loop0 disk.img
sudo mount -v -t ext4 /dev/loop0 /mnt
#sudo cp -v bin/kernel /mnt/boot/kernel
#sudo cp -v initrd.img /mnt/boot/initrd
#sudo umount -v /dev/loop0
#sudo losetup -v -d /dev/loop0

# ./configure --enable-debugger --enable-disasm --with-nogui
# bochs -q -f config/bochsrc.txt

