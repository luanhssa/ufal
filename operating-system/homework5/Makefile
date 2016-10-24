
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
# util.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o dist/util.o src/kernel/util.c
# gdt.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o dist/gdt.o src/kernel/gdt.c
# idt.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o dist/idt.o src/kernel/idt.c
# isrs.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o dist/isrs.o src/kernel/isrs.c
# irq.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o dist/irq.o src/kernel/irq.c
# timer.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o dist/timer.o src/kernel/timer.c
# kb.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o dist/kb.o src/kernel/kb.c
# paging.c
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o dist/paging.o src/kernel/paging.c
# concatenate gdt idt isrs irq paging to start.asm
	rm src/kernel/start.asm
	cat src/kernel/kmain.asm src/kernel/gdt.asm src/kernel/idt.asm src/kernel/isrs.asm src/kernel/irq.asm src/kernel/paging.asm > src/kernel/start.asm
# start.asm
	nasm src/kernel/start.asm -f elf -o dist/start.o
# link
	ld -T src/link.ld --oformat=binary -o dist/kernel.bin dist/start.o dist/kernel.o dist/util.o dist/gdt.o dist/idt.o dist/isrs.o dist/irq.o dist/timer.o dist/kb.o dist/paging.o


clean:
	rm -Rf dist
