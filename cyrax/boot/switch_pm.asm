.code16
switch_to_pm:
    cli                             # 1. disable interrupts
    lgdt (gdt_descriptor)           # 2. load the GDT descriptor
    movl %cr0, %eax
    orl $0x1, %eax                  # 3. set 32-bit mode bit in cr0
    movl %eax, %cr0
    jmp $CODE_SEG, $init_pm         # 4. far jump by using a different segment

                                    # We can now use 32-bit instructions:
.code32
init_pm:
    movw DATA_SEG, %ax              # 5. update the segment registers
    movw %ax, %ds
    movw %ax, %ss
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    movl $0x90000, %ebp              # 6. update the stack right at the top of the free space
    movl %ebp, %esp

    calll BEGIN_PM                   # 7. Call a well-known label with useful code
