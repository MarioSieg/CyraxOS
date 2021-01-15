.code32

.equ VIDEO_MEMORY, 0xB8000
.equ WHITE_OB_BLACK, 0xF

print_string_pm:
    pusha
    movl VIDEO_MEMORY, %edx
print_string_pm_loop:
    movb (%ebx), %al                # (%ebx) is the address of the char
    movb WHITE_OB_BLACK, %ah
    cmpb $0, %al                    # Check for null-terminator.
    je print_string_pm_done
    movw %ax, (%edx)                # store character + attribute in video memory
    incl %ebx                       # increment ptr
    addl $2, %edx                   # increment vram ptr
    jmp print_string_pm_loop
print_string_pm_done:
    popa
    retw
