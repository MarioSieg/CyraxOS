.code16
.equ KERNEL_OFFSET, 0x1000

entry:
    xorw %ax, %ax
    movw %ax, %es
    movw %ax, %ds
    movw %ax, %ss
    movb %dl, (BOOT_DRIVE)      # Remember that the BIOS sets us the boot drive in 'dl' on boot
    movw $0x9000, %bp
    movw %bp, %sp
    movw $MSG_REAL_MODE, %bx
    callw print
    callw print_nl
    callw load_kernel            # read the kernel from disk
    callw switch_to_pm           # disable interrupts, load GDT,  etc. Finally jumps to 'BEGIN_PM'

.include "boot/print.asm"
.include "boot/disk.asm"
.include "boot/gdt.asm"
.include "boot/32bit_print.asm"
.include "boot/switch_pm.asm"

.code16
load_kernel:
    movw $MSG_LOAD_KERNEL, %bx
    callw print
    callw print_nl
    movw %bx, KERNEL_OFFSET     # Read from disk and store in 0x1000
    movb $16, %dh               # Make a big space.
    movb (BOOT_DRIVE), %dl
    callw disk_load
    retw

.code32
BEGIN_PM:
    movl $MSG_PROT_MODE, %ebx
    calll print_string_pm
    calll KERNEL_OFFSET
    hlt

BOOT_DRIVE:         .byte 0     # Stored in memory because dl might get overwritten

MSG_REAL_MODE:      .asciz "STARTED IN 16 BIT REAL MODE!"
MSG_PROT_MODE:      .asciz "LANDED IN 32 BIT PROTECTED MODE!"
MSG_LOAD_KERNEL:    .asciz "LOADING KERNEL..."

.fill 510-(.-entry), 1, 0       # Fill 510 bytes padding.
.word 0xAA55                    # Magic word to make sector bootable.
