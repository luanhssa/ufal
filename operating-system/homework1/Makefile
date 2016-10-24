
all: init compile

	cat dist/boot.bin dist/kernel.bin > dist/floppy.bin
	sudo dd if=dist/floppy.bin of=/dev/fd0
	rm -f dist/floppy.bin

init:
	mkdir -p dist

compile:
	nasm src/bootloader/boot.asm -f bin -o dist/boot.bin
	nasm src/kernel/kernel.asm -f bin -o dist/kernel.bin

clean:
	rm -Rf dist