#include "system.h"

/* Defines an IDT entry */
struct idt_entry_struct {
    unsigned short base_lo;
    unsigned short sel;        // kernel segment
    unsigned char always0;     // always will be 0
    unsigned char flags;       /* Set using the above table! */
    unsigned short base_hi;
} __attribute__((packed));

/* Defines an IDT Pointer */
struct idt_ptr_struct {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));


/* Declare an IDT of 256 entries. Although we will only use the
*  first 32 entries in this tutorial, the rest exists as a bit
*  of a trap. If any undefined IDT entry is hit, it normally
*  will cause an "Unhandled Interrupt" exception. Any descriptor
*  for which the 'presence' bit is cleared (0) will generate an
*  "Unhandled Interrupt" exception */
idt_entry idt[256];
idt_ptr idtp;

/* Use this function to set an entry in the IDT. Alot simpler
*  than twiddling with the GDT ;) */
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags) {
    /* The interrupt routine's base address */
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;

    /* The segment or 'selector' that this IDT entry will use
    *  is set here, along with any access flags */
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

/* Installs the IDT */
void idt_install() {
    /* Sets the special IDT pointer up, just like in 'gdt.c' */
    idtp.limit = (sizeof (idt_entry) * 256) - 1;
    idtp.base = (unsigned int) &idt;

    /* Clear out the entire IDT, initializing it to zeros */
    memset(&idt, 0, sizeof(idt_entry) * 256);

    /* Add any new ISRs to the IDT here using idt_set_gate */



    /* Points the processor's internal register to the new IDT */
    idt_load((unsigned int) &idtp);
}
