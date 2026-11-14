.section .text
.code32

.extern interrupt_dispatch

.global interrupt_stub
.type interrupt_stub, @function

interrupt_stub:
    cld

    pusha

    movl %esp, %ebp
    andl $-16, %esp
    subl $12, %esp

    pushl %ebp
    call interrupt_dispatch

    movl %ebp, %esp
    popa
    addl $8, %esp

    iret

// no CPU Error codes

.macro ISR_NOERR number

.global vector_\number\()_handler
.type vector_\number\()_handler, @function

vector_\number\()_handler:
    pushl $0
    pushl $\number
    jmp interrupt_stub

.endm


 // yes CPU Error codes

.macro ISR_ERR number

.global vector_\number\()_handler
.type vector_\number\()_handler, @function

vector_\number\()_handler:
    pushl $\number
    jmp interrupt_stub

.endm


// Generating the 32 exception handlers

// No error codes 
ISR_NOERR 0
ISR_NOERR 1
ISR_NOERR 2
ISR_NOERR 3
ISR_NOERR 4
ISR_NOERR 5
ISR_NOERR 6
ISR_NOERR 7
ISR_NOERR 9
ISR_NOERR 15
ISR_NOERR 16
ISR_NOERR 18
ISR_NOERR 19
ISR_NOERR 20
ISR_NOERR 22
ISR_NOERR 23
ISR_NOERR 24
ISR_NOERR 25
ISR_NOERR 26
ISR_NOERR 27
ISR_NOERR 28
ISR_NOERR 29
ISR_NOERR 31

// Yes error codes
ISR_ERR 8
ISR_ERR 10
ISR_ERR 11
ISR_ERR 12
ISR_ERR 13
ISR_ERR 14
ISR_ERR 17
ISR_ERR 21
ISR_ERR 30


// Fallback handler

.global default_interrupt_handler
.type default_interrupt_handler, @function

default_interrupt_handler:
    pushl $0
    pushl $255
    jmp interrupt_stub


/*
    Table containing the addresses of
    all 32 exception handlers.
*/

.section .rodata
.align 4

.global isr_stub_table

isr_stub_table:

.long vector_0_handler
.long vector_1_handler
.long vector_2_handler
.long vector_3_handler
.long vector_4_handler
.long vector_5_handler
.long vector_6_handler
.long vector_7_handler
.long vector_8_handler
.long vector_9_handler
.long vector_10_handler
.long vector_11_handler
.long vector_12_handler
.long vector_13_handler
.long vector_14_handler
.long vector_15_handler
.long vector_16_handler
.long vector_17_handler
.long vector_18_handler
.long vector_19_handler
.long vector_20_handler
.long vector_21_handler
.long vector_22_handler
.long vector_23_handler
.long vector_24_handler
.long vector_25_handler
.long vector_26_handler
.long vector_27_handler
.long vector_28_handler
.long vector_29_handler
.long vector_30_handler
.long vector_31_handler

.section .note.GNU-stack,"",@progbits
