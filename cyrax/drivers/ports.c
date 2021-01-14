/* (C) Copyright Mario Sieg 2020! */

#include "ports.h"

uint8_t port_byte_in(const uint16_t _port) {
    uint8_t result;
    asm volatile("in %%dx, %%al" : "=a" (result) : "d" (_port));
    return result;
}

void port_byte_out(const uint16_t _port, const uint8_t _data) {
    asm volatile("out %%al, %%dx" : : "a" (_data), "d" (_port));
}

uint16_t port_word_in(const uint16_t _port) {
    uint16_t result;
    asm volatile("in %%dx, %%ax" : "=a" (result) : "d" (_port));
    return result;
}

void port_word_out(const uint16_t _port, const uint16_t _data) {
    asm volatile("out %%ax, %%dx" : : "a" (_data), "d" (_port));
}
