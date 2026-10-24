#ifndef TERMINAL_H
#define TERMINAL_H

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

void terminal_initialize(void);
void terminal_setColor(uint8_t color);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void terminal_putChar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writeString(const char* data);
size_t strlen(const char* str);
uint8_t VgaEntryColor(enum Vga_Color fg, enum Vga_Color bg);
uint16_t VgaEntry(unsigned char uc, uint8_t color);

#endif
