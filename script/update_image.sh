#!/bin/bash

# for floppy image #
#sudo losetup /dev/loop0 floppy.img
#sudo mount -v -t ext4 /dev/loop0 /mnt
#sudo cp -v bin/kernel /mnt/boot/kernel
#sudo cp -v initrd.img /mnt/boot/initrd
#sudo umount -v /dev/loop0
#sudo losetup -v -d /dev/loop0

# for disk image #
sudo losetup -o 1048576 /dev/loop0 disk.img
sudo mount -o loop /dev/loop0 /mnt
sudo cp -v bin/kernel /mnt/boot/kernel
sudo cp -v initrd.img /mnt/boot/initrd
sudo umount /mnt
sudo losetup -d /dev/loop0

# ./configure --enable-debugger --enable-disasm --with-nogui
# bochs -q -f config/bochsrc.txt

