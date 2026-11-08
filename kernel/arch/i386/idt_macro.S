.section .text

interrupt_stub:
    pusha                   # saves eax, ecx, edx, ebx, esp, ebp, esi, edi

    call interrupt_dispatch

    popa

    add $8, %esp            # remove vector number + error code (4 bytes each)

    iret

.align 16
.global vector_0_handler
vector_0_handler:
    pushl $0                # dummy error code
    pushl $0                # vector number
    jmp interrupt_stub

.align 16
.global vector_1_handler
vector_1_handler:
    pushl $0
    pushl $1
    jmp interrupt_stub

.align 16
.global vector_13_handler
vector_13_handler:
    pushl $13               # the CPU already pushed a real error code for #GP
    jmp interrupt_stub
