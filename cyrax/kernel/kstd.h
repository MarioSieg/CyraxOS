/* (C) Copyright Mario Sieg 2020! */

#ifndef KSTD_H
#define KSTD_H

#define FORMATBUF_SIZE 0xFF
#define STRIMPL(_x) #_x
#define STR(_x) STRIMPL(_x)

/* Kernel standard library contains common kernel routines and helpers. */

#include "../inc/clibc/stdint.h"
#include "../inc/clibc/stddef.h"

/* Copies a block of memory from <_src> into <_dst>. Returns <_dst>. Basically the same as the standard memcpy. */
extern void* kmemcpy(void *const _dst, const void *const _src, const size_t _size);

/* The same as kmemcpy, but treats the memory as volatile. */
extern volatile void* kvmemcpy(volatile void *const _dst, const volatile void *const _src, const size_t _size);

/* Sets the value of the first bytes of <_dst> to <_value> until <_size> is reached. Basically the same as the standart memcpy. */
extern void* kmemset(void *const _dst, const uint8_t _value, const size_t _size);

/* The same as kmemset, but treats the memory as volatile. */
extern volatile void* kvmemset(volatile void *const _dst, const uint8_t _value, const size_t _size);

/* Converts an i32 to an ascii string (K & R) implementation. */
extern void i32_to_ascii(register int32_t _x, register char* _out);

#endif