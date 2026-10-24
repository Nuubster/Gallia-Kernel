CC	= i686-elf-gcc
CFLAGS	= -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Ikernel/include

build: Gallia

boot.o: kernel/arch/i386/boot.s
	$(CC) -c kernel/arch/i386/boot.s -o boot.o

kernel.o: kernel/src/kernel.c
	$(CC) $(CFLAGS) -c kernel/src/kernel.c -o kernel.o 

terminal.o: kernel/src/terminal.c
	$(CC) $(CFLAGS) -c kernel/src/terminal.c -o terminal.o

keyboard.o: kernel/drivers/keyboard.S
	$(CC) -c kernel/drivers/keyboard.S -o keyboard.o

io.o: kernel/drivers/io.s
	$(CC) -c kernel/drivers/io.s -o io.o

Gallia: boot.o kernel.o keyboard.o io.o terminal.o
	$(CC) -T kernel/arch/i386/linker.ld -o Gallia -ffreestanding -O2 -nostdlib boot.o kernel.o keyboard.o io.o terminal.o -lgcc

run :
	qemu-system-i386 -kernel Gallia

clean:
	rm -f *.o Gallia

