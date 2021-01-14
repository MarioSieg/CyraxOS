C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)
OBJ = ${C_SOURCES:.c=.o}

CC = gcc
GDB = gdb

CFLAGS = -m32 -elf -fno-pie -Ofast -Wall -Wextra -Werror

../iso/cyrax.iso: boot/bootsect.bin kernel.bin
	cat $^ > ../iso/cyrax.iso

kernel.bin: boot/kernel_entry.o ${OBJ}
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: boot/kernel_entry.o ${OBJ}
	ld -o $@ -Ttext 0x1000 $^ 

run: ../iso/cyrax.iso
	qemu-system-i386 -fda ../iso/cyrax.iso

debug: ../iso/cyrax.iso kernel.elf
	qemu-system-i386 -s -fda ../iso/cyrax.iso&
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o
