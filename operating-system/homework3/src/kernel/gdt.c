// This struct contains the value of one GDT entry
// We use the attribute 'packed' to tell GCC not to change
// any of the aligment in the structure.
struct gdt_entry_struct {

	unsigned short limit_low;	// the lower 16 bits of the limit
	unsigned short base_low;	// the lower 16 bits of the base
	unsigned char base_middle;	// the next 8 bits of the base
	unsigned char access;		// access flags, determine what ring this segment can be used in
	unsigned char granularity;
	unsigned char base_high;	// the last 8 bits of the base
	
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry;

struct gdt_ptr_struct {
	unsigned short limit;		// the upper 16 bits of all selector limits
	unsigned int base;		// the address of the first gdt_entry struct
	
}__attribute((packed));
typedef struct gdt_ptr_struct gdt_ptr;



extern void gdt_load(gdt_ptr*);
extern void breakpoint(void);



gdt_entry gdt[3];
gdt_ptr gp;



void gdt_add_seg(int seg, unsigned long base, unsigned long limit,
		unsigned char ring, unsigned char type) {

	gdt[seg].base_low = (base & 0xFFFF);
	gdt[seg].base_middle = (base >> 16) & 0xFF;
	gdt[seg].base_high = (base >> 24) & 0xFF;

	gdt[seg].limit_low = (limit & 0xFFFF);
	gdt[seg].granularity = ((limit >> 16) & 0x0F);
	
	if (limit !=0) {
		gdt[seg].granularity |= 0xC0;

		ring = ring << 8;

		gdt[seg].access = (type & 0xF);
		gdt[seg].access |= ring;
		gdt[seg].access |= 0x90;
	}
}

void gdt_init() {

	gdt_add_seg(0, 0, 0, 0, 0); //null segment
	gdt_add_seg(1, 0, 0xFFFFFFFF, 0x0, 0x2); //data segment
	gdt_add_seg(2, 0, 0xFFFFFFFF, 0x0, 0xA); //code segment

	gp.limit = (sizeof(gdt_entry) * 3) - 1;
	gp.base = &gdt;

	gdt_load(&gp);
}
