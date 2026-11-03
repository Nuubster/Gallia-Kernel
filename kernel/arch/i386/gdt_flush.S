.section .text
.global load_gdt
.type load_gdt, @function

load_gdt:
    mov 4(%esp), %eax
    lgdt (%eax)

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss

    ljmp $0x08, $reload_cs

reload_cs:
    ret

.size load_gdt, . - load_gdt
