/* (C) Copyright Mario Sieg 2020! */

#include "ports.h"

u8 port_byte_in(const u16 _port) {
    u8 result;
    asm volatile("in %%dx, %%al" : "=a" (result) : "d" (_port));
    return result;
}

void port_byte_out(const u16 _port, const u8 _data) {
    asm volatile("out %%al, %%dx" : : "a" (_data), "d" (_port));
}

u16 port_word_in(const u16 _port) {
    u16 result;
    asm volatile("in %%dx, %%ax" : "=a" (result) : "d" (_port));
    return result;
}

void port_word_out(const u16 _port, const u16 _data) {
    asm volatile("out %%ax, %%dx" : : "a" (_data), "d" (_port));
}
