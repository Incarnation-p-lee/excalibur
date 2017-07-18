#!/bin/sh
# dd if=/dev/zero of=disk.img count=10080
# fdisk disk.img
# hexdump disk.img
sudo losetup -o 1048576 /dev/loop0 disk.img
sudo mkfs.ext4 /dev/loop0
sudo mount -o loop /dev/loop0 /mnt
sudo mkdir -v /mnt/boot
sudo cp -rv ./config/grub /mnt/boot/
sudo umount /mnt
sudo losetup -d /dev/loop0
