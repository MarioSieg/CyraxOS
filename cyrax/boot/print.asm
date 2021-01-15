.code16

print:
    pusha
start:
    movb (%bx), %al
    cmpb $0, %al
    je done
    movb $0xE, %ah
    int $0x10
    inc %bx
    jmp start
done:
    popa
    retw
print_nl:
    pusha
    movb $0xE, %ah
    movb $0xA, %al
    int $0x10
    movb $0xD, %al
    int $0x10  
    popa
    retw
