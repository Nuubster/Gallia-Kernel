build: Gallia

boot.o: boot.s
	i686-elf-as boot.s -o boot.o

kernel.o: kernel.c
	i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

Gallia: boot.o kernel.o
	i686-elf-gcc -T linker.ld -o Gallia -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

run :
	qemu-system-i386 -kernel Gallia

