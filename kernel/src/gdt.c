#include <stdint.h>

#define NUM_GDT_ENTRIES 3
#define NULL_SELECTOR 0x00
#define KERNEL_CS 0x08
#define KERNEL_DS 0x10

uint64_t gdtEntries[NUM_GDT_ENTRIES];

struct GDTR {
    uint16_t limit;
    uint32_t address;
} __attribute__((packed));

struct GDTR exampleGDTR;

extern void load_gdt(const struct GDTR *gdtr);

static void gdt_set(int i, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
    gdtEntries[i]  = limit & 0xFFFF;                        // Limit 0-15
    gdtEntries[i] |= (uint64_t)(base & 0xFFFFFF) << 16;     // base 0-23
    gdtEntries[i] |= (uint64_t)access << 40;                // P, DPL, S, type
    gdtEntries[i] |= (uint64_t)((limit >> 16) & 0xF) << 48; // limit 16-19
    gdtEntries[i] |= (uint64_t)(flags & 0xF) << 52;         // G, D/B, L, AVL
    gdtEntries[i] |= (uint64_t)(base >> 24) << 56;          // base 24-31
}

void GDT_init(void)
{
    gdtEntries[0] = 0;

    gdt_set(1, 0, 0xFFFFF, 0x9A, 0xC); // kernel code
    gdt_set(2, 0, 0xFFFFF, 0x92, 0xC); // kernel data

    exampleGDTR.limit = sizeof(gdtEntries) - 1;
    exampleGDTR.address = (uint32_t)(uintptr_t)gdtEntries;

    load_gdt(&exampleGDTR);
}


