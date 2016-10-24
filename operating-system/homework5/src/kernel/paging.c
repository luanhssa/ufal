#include "system.h"

struct page_entry_struct {
	int present 		: 1;
	int read			: 1;
	int user			: 1;
	int write			: 1;
	int cache			: 1;
	int accessed		: 1;
	int size			: 1;
	int ignored			: 1;
	int available		: 4;
	int frame_base		: 20;
};

struct page_table_struct {
	
	page_entry pages[1024];
	
};

struct page_dir_struct {
	
	page_table* tables[1024];
	
};

void page_fault(registers_t regs) {
	// A page fault has occurred.
	// The faulting address is stored in the CR2 register.
	unsigned int faulting_address;
	sys("mov %%cr2, %0" : "=r" (faulting_address));

	// The error code gives us details of what happened.
	int present   = !(regs.err_code & 0x1); // Page not present
	int rw = regs.err_code & 0x2;           // Write operation?
	int us = regs.err_code & 0x4;           // Processor was in user-mode?
	int reserved = regs.err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?
	int id = regs.err_code & 0x10;          // Caused by an instruction fetch?

	// Output an error message.
	puts("Page fault! ( ");
	if (present) 
		puts("present ");
	if (rw) 
		puts("read-only ");
	if (us) 
		puts("user-mode ");
	if (reserved) 
		puts("reserved ");
	puts(") at 0x");
	puthex(faulting_address);
	puts("\n");
	PANIC("Page fault");
}

void paging_install() {

	page_dir* directory;
	page_table* table0;
	
	int i;

	directory = (page_dir*)   0x10000;
	table0 	  = (page_table*) 0x11000;
	
	
	//int size = 4 * 1024;
	for(i = 0; i < 1024; ++i) {
		
		table0->pages[i].present 	 = 1;
		table0->pages[i].read		 = 1;
		table0->pages[i].user		 = 1;
		table0->pages[i].write		 = 0;
		table0->pages[i].frame_base = i;
		
	}

	unsigned int *tmp = (((unsigned int) table0) | 0x07);
	
	directory->tables[0] = (page_table*) tmp;
		
	update_directory(directory);
	
	// Before we enable paging, we must register our page fault handler.
	register_interrupt_handler(14, page_fault);

	enable_paging();
}