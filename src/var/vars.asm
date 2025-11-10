section .data

ZEROADDR    DQ     0x0000000000000000
ENDADDR     DQ     0xffffffffffffffff

VGA_START   DW     0xb8000    ;VGA zone start
DMX_START   DW     0xf0000    ;DMX zone start

BITMODE     DB     64         ;64-bit mode

REG_ADDR    DW     0xff000    ;Registry address (hopefully)


BUF_WIDTH   DB     32         ;Command Buffer width
BUF_HEIGHT  DW     9001       ;Command Buffer height


ZMAX        DB     255
ZMIN        DB     0


CORE_MAX    DB     128
CORE_MIN    DB     1


DMX         DW     00,  15,  25,  32,  64, 100


LM          DQ     0xC0000080 ;Longmode #
MBZN        DQ     0x36d76289
MBMN        DQ     0xe85250d6 ;Multiboot Magic #


PTABLE_ZONE DW     512
