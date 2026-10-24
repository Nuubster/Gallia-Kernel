#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "terminal.h"
#include "conf.h"

size_t terminalRow;
size_t terminalColumn;
uint8_t terminalColor;
uint16_t* terminalBuffer = (uint16_t*)VGA_MEMORY;

uint8_t VgaEntryColor(enum Vga_Color fg, enum Vga_Color bg)
{
    return fg | bg << 4;
}

uint16_t VgaEntry(unsigned char uc, uint8_t color)
{
    return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str)
{
    size_t len = 0;
    while (str[len]) len++;
    return len;
}

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

// SHORTEN AND ADD CHECK FUNCTION!!
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
