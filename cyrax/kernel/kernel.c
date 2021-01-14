/* (C) Copyright Mario Sieg 2020! */

#include "kstd.h"
#include "../drivers/screen.h"

extern void dump_info();

void main() {
    clear_screen();
    dump_info();
    dump_screen_info();
    kcprint("SYSTEM ONLINE!\n", vga_color(LIGHT_GREEN, BLACK));
}

void dump_info() {
    kcprint("CYRAX HACKER OS (C) COPYRIGHT MARIO SIEG \"KERBO\" 2020!\n", vga_color(CYAN, BLACK));
    kcprint("CONTACT: mt3000@gmx.de\n", vga_color(CYAN, BLACK));
    kcprint("LICENSED UNDER \"3-Clause BSD LICENSE\"! SEE LICENSE FILE!\n", vga_color(CYAN, BLACK));
    kprint("16-BIT REAL MODE BOOT... OK!\n");
    kprint("32-BIT PROTECTED MODE BOOT... OK!\n");
}