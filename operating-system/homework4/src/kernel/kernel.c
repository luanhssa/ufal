#include "system.h"

#define sys(value) __asm__ __volatile__ (value)

void kmain() {

	gdt_install();
	breackpoint();
	idt_install();
	breackpoint();
	isrs_install();
	irq_install();
    init_video();
	timer_install();
	keyboard_install();
	breackpoint();

    sys("sti");
    puts((unsigned char*) "Hello World");
	breackpoint();


	hang();

}
