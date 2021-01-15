CXX_SOURCES = $(wildcard kernel/*.cpp drivers/*.cpp src/*.cpp)
HEADERS = $(wildcard kernel/*.hpp drivers/*.hpp inc/*.hpp)
OBJ = ${CXX_SOURCES:.cpp=.o}

CXX = g++
GDB = gdb

CXXFLAGS = -c -m32 -elf -Wall -Wextra -Werror -Wold-style-cast -fno-stack-protector -ffreestanding -nostdlib -fno-common -fno-exceptions -fno-non-call-exceptions -fno-rtti -std=c++17 -fno-pie

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

%.o: %.cpp ${HEADERS}
	${CXX} ${CXXFLAGS} $< -o $@
	${CXX} ${CXXFLAGS} -S $< -o $<.asm

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o *.elf cyrax.iso
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o src/*.o
	rm -rf kernel/*.cpp.asm drivers/*.cpp.asm src/*.cpp.asm
