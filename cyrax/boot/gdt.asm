# Do not remove any labels, they are used to compute offsets!

# The GDT starts with 8 zero bytes:
gdt_start:
    .long 0x0
    .long 0x0

# GDT for code segment. base = 0x00000000, length = 0xFFFFF
gdt_code: 
    .word 0xFFFF        # segment length, bits 0-15
    .word 0x0           # segment base, bits 0-15
    .byte 0x0           # segment base, bits 16-23
    .byte 0b10011010    # flags (8 bits)
    .byte 0b11001111    # flags (4 bits) + segment length, bits 16-19
    .byte 0x0           # segment base, bits 24-31

# GDT for data segment. Base and length identical to code segment, but with different flags.
gdt_data:
    .word 0xFFFF
    .word 0x0
    .byte 0x0
    .byte 0b10010010
    .byte 0b11001111
    .byte 0x0

gdt_end:

# GDT descriptor
gdt_descriptor:
    .word gdt_end - gdt_start - 1          # Size (16 bit) - 1
    .long gdt_start                        # Address (32 bit)

.equ CODE_SEG, gdt_code - gdt_start
.equ DATA_SEG, gdt_data - gdt_start
