
all: init bootloader kernel
	cat dist/boot.bin dist/kernel.bin > dist/floppy.bin
	sudo dd if=dist/floppy.bin of=/dev/fd0

init:
	mkdir -p dist

bootloader:
	nasm src/bootloader/boot.asm -f bin -o dist/boot.bin

kernel:
# kernel.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o dist/kernel.o src/kernel/kernel.c
# hang.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o dist/hang.o src/kernel/hang.c
# gdt.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o dist/gdt.o src/kernel/gdt.c
# gdt_load.asm
	nasm src/kernel/gdt_load.asm -f elf -o dist/gdt_load.o
# util.asm
	nasm src/util.asm -f elf -o dist/util.o
# link
	ld -T src/link.ld --oformat=binary dist/kernel.o dist/hang.o dist/gdt.o dist/gdt_load.o dist/util.o -o dist/kernel.bin


clean:
	rm -Rf dist