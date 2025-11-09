section .data

VGA_START   DB     0xb8000   ;VGA zone start
DMX_START   DB     0xf0000   ;DMX zone start

BITMODE     DB     64        ;64-bit mode

REG_ADDR    DB     0xff000   ;Registry address