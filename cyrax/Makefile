C_SOURCES = $(wildcard kernel/*.c drivers/*.c src/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h inc/*.h)
OBJ = ${C_SOURCES:.c=.o}

CC = gcc
GDB = gdb

CFLAGS = -m32 -elf -fno-pie -Ofast -Wall -Wextra -Werror

cyrax.iso: boot/bootsect.bin kernel.bin
	cat $^ > cyrax.iso

kernel.bin: boot/kernel_entry.o ${OBJ}
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: boot/kernel_entry.o ${OBJ}
	ld -o $@ -Ttext 0x1000 $^ 

run: cyrax.iso
	qemu-system-i386 -fda cyrax.iso

debug: cyrax.iso kernel.elf
	qemu-system-i386 -s -fda cyrax.iso&
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -nostdlib -c $< -o $@
	${CC} ${CFLAGS} -ffreestanding -nostdlib -c -S $< -o $<.asm

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o *.elf cyrax.iso
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o src/*.o
	rm -rf kernel/*.c.asm drivers/*.c.asm src/*.c.asm
