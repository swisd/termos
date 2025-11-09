#include "print.h"
#include <stdint.h>
#include "string.h"
#include "keyboard.h"
extern void keyboard_handler();

// Include outb/inb if not already present
static inline uint8_t inb(uint16_t port) {
    uint8_t result;
    __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

static inline void outb(uint16_t port, uint8_t value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

void enable_keyboard_irq() {
    uint8_t mask = inb(0x21);
    mask &= ~(1 << 1);       // Clear bit 1 to enable IRQ1 (keyboard)
    outb(0x21, mask);
}

void idt_init() {
    // Assuming set_idt_gate exists and works for long mode
    set_idt_gate(33, (uint64_t)keyboard_handler);
    // Enable IRQ1
}

void init_keyboard() {
    register_interrupt_handler(33, keyboard_handler);
}
void kernel_main() {
    print_clear();
    idt_init();
    asm volatile("sti"); // Enable interrupts globally
    print_set_color(PRINT_COLOR_LIGHT_CYAN, PRINT_COLOR_BLACK);
    print_str("CPU   [OK]\n")
    print_str("GPU   [OK]\n")
    print_str("MB    [OK]\n")
    print_str("LAN   [OK]\n\n\n")
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    print_str("64-bit kernel\n");
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str(">>")
    enable_keyboard_irq();
}

void process_command(const char *cmd) {
    if (strcmp(cmd, "help") == 0) {
        print_str("Available commands: help, clear, about, mode\n");
    } else if (strcmp(cmd, "clear") == 0) {
        print_clear();
    } else if (strcmp(cmd, "about") == 0) {
        print_str("termos terminal\n");
    } else if (strcmp(cmd, "mode") == 0 {
        print_str("64\n")
    } else {
        print_str("Unknown command.\n");
    }
    print_str("> ")
}