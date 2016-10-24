
all: init bootloader kernel
	cat dist/boot.bin dist/kernel.bin > dist/floppy.bin
	sudo dd if=dist/floppy.bin of=/dev/fd0

init:
	mkdir -p dist

bootloader:
	nasm src/bootloader/boot.asm -f bin -o dist/boot.bin

kernel:
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o dist/kernel.o src/kernel/kernel.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o dist/hang.o src/kernel/hang.c
	ld -T src/link.ld dist/kernel.o dist/hang.o -o dist/kernel.bin

clean:
	rm -Rf dist