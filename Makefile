build: Gallia

boot.o: kernel/arch/i386/boot.s
	i686-elf-as boot.s -o boot.o

kernel.o: kernel/src/kernel.c
	i686-elf-gcc -c kernel/src/kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

keyboard.o: kernel/arch/i386/keyboard.S
	i686-elf-gcc -c kernel/arch/i386/keyboard.S -o keyboard.o

Gallia: boot.o kernel.o keyboard.o
	i686-elf-gcc -T kernel/arch/i386/linker.ld -o Gallia -ffreestanding -O2 -nostdlib boot.o kernel.o keyboard.o -lgcc

run :
	qemu-system-i386 -kernel Gallia

