#include <stdint.h>

struct interrupt_descriptor
{
    uint16_t address_low;
    uint16_t selector;
    uint8_t  reserved;      // IST infact doesn't exist in 32-bit
    uint8_t  flags;
    uint16_t address_high;  // No address_mid or extra either
} __attribute__((packed));

struct interrupt_descriptor idt[256];

struct idtr
{
    uint16_t limit;
    uint32_t base;          // 32-bit base now
} __attribute__((packed));

extern void (*isr_stub_table[32])(void);
extern void default_interrupt_handler(void);

void set_idt_entry(uint8_t vector, void (*handler)(void), uint8_t dpl)
{
    uint32_t handler_addr = (uint32_t)handler;

    struct interrupt_descriptor* entry = &idt[vector];

    entry->address_low  = handler_addr & 0xFFFF;
    entry->address_high = (handler_addr >> 16) & 0xFFFF;

    entry->selector = 0x8;  // Yes the Kernel Code selector infact IS 0x8
    entry->flags = 0b1110 | ((dpl & 0b11) << 5) | (1 << 7); // gate type + DPL + present
    entry->reserved = 0;
}

void load_idt(void* idt_addr)
{
    struct idtr idt_reg;
    idt_reg.limit = sizeof(idt) - 1;    // 0x7FF NOT 0xFFF
    idt_reg.base = (uint32_t)idt_addr;
    asm volatile("lidt %0" :: "m"(idt_reg));
}

void IDT_init(void)
{
    // Gives every vector the fallback handler
    for (unsigned int i = 0; i < (sizeof(idt) / sizeof(idt[0])); i++)
    {   set_idt_entry(i, default_interrupt_handler, 0); }

    // Replaces the first 32 entries with CPU exception handlers
    for (unsigned int i = 0; i < 32; i++)
    {   set_idt_entry(i, isr_stub_table[i], 0); }

    load_idt(&idt[0]);
}
