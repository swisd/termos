// src/impl/kernel/keyboard.c

#include <stdint.h>
#include "print.h" // for putchar or kprint

#define KEYBOARD_PORT 0x60
#define CMD_BUFFER_SIZE 256

static char cmd_buffer[CMD_BUFFER_SIZE];
static int cmd_index = 0;

char scancode_to_ascii[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8',
    '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r',
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
    '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n',
    'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0,
    // Fill in more as needed
};

static inline uint8_t inb(uint16_t port) {
    uint8_t result;
    __asm__ volatile("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

void process_command(const char *cmd); // Forward declaration

void keyboard_isr() {
    uint8_t scancode = inb(KEYBOARD_PORT);

    if (scancode & 0x80) return; // Key release

    char c = scancode_to_ascii[scancode];
    if (!c) return;

    if (c == '\b') {
        if (cmd_index > 0) {
            cmd_index--;
            putchar('\b'); // Optional: visually delete char
        }
    } else if (c == '\n') {
        putchar('\n');
        cmd_buffer[cmd_index] = '\0'; // Null-terminate
        process_command(cmd_buffer);
        cmd_index = 0; // Reset for next command
    } else {
        if (cmd_index < CMD_BUFFER_SIZE - 1) {
            cmd_buffer[cmd_index++] = c;
            putchar(c); // Echo typed char
        }
    }
}