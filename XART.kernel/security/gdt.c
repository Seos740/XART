#include <stdint.h>

#define GDT_ENTRY_COUNT 5

// GDT Entry structure (64-bit)
struct gdt_entry {
    uint16_t limit_low;      // Lower 16 bits of limit
    uint16_t base_low;       // Lower 16 bits of base
    uint8_t  base_middle;    // Bits 16-23 of base
    uint8_t  access;         // Access flags
    uint8_t  granularity;    // Granularity and limit high
    uint8_t  base_high;      // Bits 24–31 of base
} __attribute__((packed));

// GDTR structure
struct gdt_ptr {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

// Actual GDT and pointer
static struct gdt_entry gdt[GDT_ENTRY_COUNT];
static struct gdt_ptr gdtr;

// Assembly function to load the GDT
extern void gdt_flush(uint16_t code_seg, uint16_t data_seg);

static void set_gdt_entry(int idx, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    gdt[idx].limit_low    = limit & 0xFFFF;
    gdt[idx].base_low     = base & 0xFFFF;
    gdt[idx].base_middle  = (base >> 16) & 0xFF;
    gdt[idx].access       = access;
    gdt[idx].granularity  = ((limit >> 16) & 0x0F) | (flags & 0xF0);
    gdt[idx].base_high    = (base >> 24) & 0xFF;
}

void init_gdt() {
    set_gdt_entry(0, 0, 0, 0, 0);                // Null descriptor
    set_gdt_entry(1, 0, 0xFFFFF, 0x9A, 0xA0);     // Kernel code: ring 0, exec
    set_gdt_entry(2, 0, 0xFFFFF, 0x92, 0xA0);     // Kernel data: ring 0, write
    set_gdt_entry(3, 0, 0xFFFFF, 0xFA, 0xA0);     // User code: ring 3, exec
    set_gdt_entry(4, 0, 0xFFFFF, 0xF2, 0xA0);     // User data: ring 3, write

    gdtr.limit = sizeof(gdt) - 1;
    gdtr.base = (uint64_t)&gdt;

    gdt_flush(0x08, 0x10); // Kernel CS and DS
}
