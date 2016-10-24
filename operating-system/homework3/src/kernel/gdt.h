
typedef struct gdt_entry {

	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char ganularity;
	unsigned char base_high;
	
}__attribute((packed));

typedef struct gdt_ptr {

	unsigned short limit;
	unsigned int base;
	
}__attribute((packed));

