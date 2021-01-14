/* (C) Copyright Mario Sieg 2020! */

#ifndef KSTD_H
#define KSTD_H

#define FORMATBUF_SIZE 0xFF

/* Kernel standard library contains common kernel routines and helpers. */

#include "../inc/types.h"

/* Copies a block of memory from <_src> into <_dst>. Returns <_dst>. Basically the same as the standard memcpy. */
extern void* kmemcpy(void *const _dst, const void *const _src, const usize _size);

/* The same as kmemcpy, but treats the memory as volatile. */
extern volatile void* kvmemcpy(volatile void *const _dst, const volatile void *const _src, const usize _size);

/* Sets the value of the first bytes of <_dst> to <_value> until <_size> is reached. Basically the same as the standart memcpy. */
extern void* kmemset(void *const _dst, const u8 _value, const usize _size);

/* The same as kmemset, but treats the memory as volatile. */
extern volatile void* kvmemset(volatile void *const _dst, const u8 _value, const usize _size);

/* Converts an i32 to an ascii string (K & R) implementation. */
extern void i32_to_ascii(register i32 _x, register char8* _out);

/* Prints to the screen via VGA. Formatting with %i is supported! The arguments should be pointer to the values like: */
/*
    int x = 3;
    const void* args[] = { &x };
    kprintf("X is: %i", args);
*/
/* You can also pass NULL if you don't have any args. */
extern void kprintf(register const char8* _fmt, const void** _args);

/* Same as kprintf but color can be set. */ 
extern void kcprintf(register const char8* _fmt, const void** _args, const u8 _col);

/* Prints to the screen via VGA. No formatting is supported. Use kprintf for formatting. */
extern void kprint(register const char* _msg);

/* Same as kprint but color can be set. */
extern void kcprint(register const char* _msg, const u8 _col);

#endif