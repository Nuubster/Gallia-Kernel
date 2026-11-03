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

void GDT_init(void)
{
    // Null descriptor
    gdtEntries[0] = 0;

    uint64_t kernel_code = 0;
    kernel_code |= (uint64_t)0b1011 << 8;
    kernel_code |= (uint64_t)1 << 12;
    kernel_code |= (uint64_t)0 << 13;
    kernel_code |= (uint64_t)1 << 15;
    kernel_code |= (uint64_t)1 << 22;
    kernel_code |= (uint64_t)1 << 23;

    gdtEntries[1] = kernel_code << 32;

    uint64_t kernel_data = 0;
    kernel_data |= (uint64_t)0b0011 << 8;
    kernel_data |= (uint64_t)1 << 12;
    kernel_data |= (uint64_t)0 << 13;
    kernel_data |= (uint64_t)1 << 15;
    kernel_data |= (uint64_t)1 << 22;
    kernel_data |= (uint64_t)1 << 23;

    gdtEntries[2] = kernel_data << 32;

    exampleGDTR.limit = sizeof(gdtEntries) - 1;

    exampleGDTR.address = (uint32_t)(uintptr_t)gdtEntries;

    load_gdt(&exampleGDTR);
}


