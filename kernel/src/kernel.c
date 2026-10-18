#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "io.h"

enum Vga_Color {
    VGA_BLACK = 0,
    VGA_BLUE = 1,
    VGA_GREEN = 2,
    VGA_CYAN = 3,
    VGA_RED = 4,
    VGA_MAGENTA = 5,
    VGA_BROWN = 6,
    VGA_LIGHT_GREY = 7,
    VGA_DARK_GREY = 8,
    VGA_LIGHT_BLUE = 9,
    VGA_LIGHT_GREEN = 10,
    VGA_LIGHT_CYAN = 11,
    VGA_LIGHT_RED = 12,
    VGA_LIGHT_MAGENTA = 13,
    VGA_LIGHT_BROWN = 14,
    VGA_WHITE = 15,
};

static inline uint8_t VgaEntryColor(enum Vga_Color fg, enum Vga_Color bg)
{
    return fg | bg << 4;
}

static inline uint16_t VgaEntry(unsigned char uc, uint8_t color)
{
    return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str)
{
    size_t len = 0;
    while (str[len]) len++;
    return len;
}

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000

// Scancode port: 0x60; Status port: 0x64
/*
 * uint8_t Status = keyboard_readStatus; 
 * if (Status & 0x1)  
*/
uint8_t keyboard_read(void);
uint8_t keyboard_readStatus(void);

size_t terminalRow;
size_t terminalColumn;
uint8_t terminalColor;
uint16_t* terminalBuffer = (uint16_t*)VGA_MEMORY;

void terminal_initialize(void)
{
    terminalRow = 0;
    terminalColumn = 0;
    terminalColor = VgaEntryColor(VGA_LIGHT_GREY, VGA_BLACK);

    // Custom font colors can be changed with this:
    // terminalColor = VgaEntryColor(VGA_GREEN, VGA_MAGENTA);

    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminalBuffer[index] = VgaEntry(' ', terminalColor);
        }
    }
}

void terminal_setColor(uint8_t color)
{
    terminalColor = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminalBuffer[index] = VgaEntry(c, color);
}

void terminal_putChar(char c)
{
    // quick check for newline, will  be changed in the future
    if(c == '\n') 
    { 
        terminal_putentryat(c, terminalColor, 0, terminalRow + 1); 
        terminalRow++; terminalColumn = 0;
        return;   
    }
    else if (c == '\0') { return; }
    else { terminal_putentryat(c, terminalColor, terminalColumn, terminalRow); }

    if (++terminalColumn == VGA_WIDTH) {
        terminalColumn = 0;
        if (++terminalRow == VGA_HEIGHT)
            terminalRow = 0;
    }
}

void terminal_write(const char* data, size_t size)
{
    for (size_t i = 0; i < size; i++)
        terminal_putChar(data[i]);
}

void terminal_writeString(const char* data)
{
    terminal_write(data, strlen(data));
}

char ScancodeToChar[256] = {'\0', '\0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 'B', '0', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 
    'o', 'p', '[', ']', '\n', 'c', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', '\0'};

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
