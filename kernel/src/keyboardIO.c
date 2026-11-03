#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <io.h>

#define MAX_KEY_BUFFER_SIZE 255

typedef struct {
    uint8_t code;
} key_event;

key_event keyboardBuffer[MAX_KEY_BUFFER_SIZE];
uint8_t bufferPosition = 0;

void keyboard_IRQ_handler()
{
    uint8_t scancode = keyboard_read();

    keyboardBuffer[bufferPosition].code = scancode;
    bufferPosition = (bufferPosition + 1) % MAX_KEY_BUFFER_SIZE;
}
