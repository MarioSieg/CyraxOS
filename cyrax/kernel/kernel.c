/* (C) Copyright Mario Sieg 2020! */

#include "../drivers/screen.h"
#include "kstd.h"

extern void dump_info();

void main() {
    clear_screen();
    dump_info();
}

void dump_info() {
    kprint("CyraxOS (C) Copyright Mario Sieg 2020!\n");
    kprint("Kernel online!\n");
}