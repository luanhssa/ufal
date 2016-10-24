/**
 * Author: Luan H. S. S. Almeida (luanhssa@gmail.com)
 */

#ifndef __SYSTEM_H
#define __SYSTEM_H

#define breackpoint() asm("xchg %bx, %bx")
#define PANIC(msg) panic(msg, __FILE__, __LINE__);
#define sys(value) __asm__ __volatile__ (value)

/*
 * This defines what the stack looks like after an ISR was running
 */
struct regs_struct {
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;    
};
typedef struct regs_struct regs;

/**
 * Global Descriptor Table (GDT)
 **/
typedef struct gdt_entry_struct gdt_entry;
typedef struct gdt_ptr_struct gdt_ptr;
extern void gdt_load(unsigned int);
extern void gdt_install();

/**
 * Interrupt Descriptor Table (IDT)
 **/
typedef struct idt_entry_struct idt_entry;
typedef struct idt_ptr_struct idt_ptr;
extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
extern void idt_load(unsigned int);
extern void idt_install();

/**
 * Interrupt Services Routines (ISRS)
 **/
extern void isrs_install();

/**
 * Interrupt Requests (IRQ)
 **/

extern void irq_install_handler(int irq, void (*handler)(regs *r));
extern void irq_uninstall_handler(int irq);
extern void irq_install();


/**
 * Programmable Interval Timer (PIT)
 **/
extern void timer_wait(int ticks);
extern void timer_install();


/**
 * Keyboard
 **/
extern void keyboard_install();

/**
 * Paging
 */
typedef struct page_entry_struct page_entry;
typedef struct page_table_struct page_table;
typedef struct page_dir_struct page_dir;
extern void paging_install();
extern void update_directory(page_dir*);
extern void enable_paging();

/**
 * UTIL
 **/
// Infinit Loop
extern void hang();
// Copy block of memory
extern void *memcpy(void *dest, const void *src, int count);
// Set bytes from one variable to another
extern void *memset(void *dest, char val, int count);
// Same as memset, but with 16-bit
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
// Count the length of a string
extern int strlen(const char *str);
// Input port
extern unsigned char inportb (unsigned short _port);
// Output port
extern void outportb (unsigned short _port, unsigned char _data);

extern void init_video(void);
extern void putch(unsigned char c);
extern void puts(unsigned char *text);
extern void puthex(unsigned int n);
extern void putdec(unsigned int n);
extern void cls();

extern void panic(const char *message, const char *file, u32int line);



#endif
