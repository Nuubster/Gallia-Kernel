#include "interrupt.h"
#include "terminal.h"
#include <stddef.h>

void interrupt_dispatch(struct interrupt_frame *frame)
{
    asm volatile("cli");

    terminal_writeString("EXCEPTION!!!!!");
    for(;;)
    {   asm volatile("hlt");  }
}
