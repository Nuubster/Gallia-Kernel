#include "interrupt.h"

void interrupt_dispatch(struct interrupt_frame *frame)
{
    asm volatile("cli");

    for(;;)
    {   asm volatile("hlt");  }
}
