#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "io.h"
#include "terminal.h"
#include "conf.h"

// Scancode port: 0x60; Status port: 0x64
uint8_t keyboard_read(void);
uint8_t keyboard_readStatus(void);

char ScancodeToChar[256] = {'\0', '\0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 'B', '0', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 
    'o', 'p', '[', ']', '\n', 'c', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', '\0', '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', 
    '/', '\0', '\0', ' ', '\0'};

void kernel_main(void)
{
    terminal_initialize();
    bool ShiftPressed = false;
    bool ShiftReleased = true;

    terminal_writeString("HelloWorld(Console.WriteLine)\n");
    terminal_writeString("THIS IS NOT A KIRNIL\n");
    terminal_writeString("1234\n");

    while(1)
    {
        uint8_t KeyStatus = keyboard_readStatus();

        if (KeyStatus & 0x1)
        {
            unsigned char Scancode = keyboard_read();
            if (Scancode == 0x2A) { 
                ShiftPressed = true; ShiftReleased = false;
            }
            char charPressed = ScancodeToChar[Scancode]; 
            if (ShiftPressed == true && ShiftReleased == false && charPressed != ScancodeToChar[0x2A]) charPressed -= 0x20;
            terminal_putChar(charPressed);

            if (Scancode == 0xAA) { ShiftPressed = false; ShiftReleased = true; }
        }
    }
}
