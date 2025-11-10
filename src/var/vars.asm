section .data

ZEROADDR    DQ     0x0000000000000000
ENDADDR     DQ     0xffffffffffffffff

VGA_START   DW     0xb8000   ;VGA zone start
DMX_START   DW     0xf0000   ;DMX zone start

BITMODE     DB     64        ;64-bit mode

REG_ADDR    DW     0xff000   ;Registry address (hopefully)


BUF_WIDTH   DB     32        ;Command Buffer width
BUF_HEIGHT  DW     9001      ;Command Buffer height


ZMAX        DD     255
ZMIN        DD     0