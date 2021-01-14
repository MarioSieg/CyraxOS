/* (C) Copyright Mario Sieg 2020! */

#include "kstd.h"
#include "../drivers/screen.h"

void* kmemcpy(void *const _dst, const void *const _src, const usize _size) {
    register u8* dst = (u8*)dst;
    register const u8* src = (const u8*)_src;
    register const u8* end = src + _size - 1; 
    while(src != end) {
        *dst++ = *src++;
    }
    return _dst;
}

volatile void* kvmemcpy(volatile void *const _dst, const volatile  void *const _src, const volatile usize _size) {
    register volatile u8* dst = (u8*)dst;
    register volatile const u8* src = (const u8*)_src;
    register volatile const u8* end = src + _size - 1; 
    while(src != end)
        *dst++ = *src++;
    return _dst;
}

void* kmemset(void *const _dst, const u8 _value, const usize _size) {
    register u8* dst = (u8*)dst;
    register const u8* end = dst +  _size - 1; 
    while(dst != end) {
        *dst++ = _value;
    }
    return _dst;
}

volatile void* kvmemset(volatile void *const _dst, const u8 _value, const usize _size) {
    register volatile u8* dst = (u8*)dst;
    register volatile const u8* end = dst +  _size - 1; 
    while(dst != end) {
        *dst++ = _value;
    }
    return _dst;
}

void kitoa(register i32 _x, register char8* _out) {
    i32 sign;
    if ((sign = _x) < 0) 
        _x = -_x;
    do
        *_out++ = _x % 10 + '0';
    while ((_x /= 10) > 0);
    if (sign < 0) 
        *_out++ = '-';
    *_out = '\0';
}

void kprint(register const char* _msg) {
    kprint_auto(_msg, WHITE_ON_BLACK);
}

void kcprint(register const char* _msg, const u8 _col) {
    kprint_auto(_msg, _col);
}

    /* TODO: */
void kcprintf(register const char8* _fmt, const void** _args, const u8 _col) {
    if(_args == NULL) {
        kprint_auto(_fmt, _col);
        return;
    }
    char formatbuf[FORMATBUF_SIZE];
    kmemset(formatbuf, 0, sizeof(formatbuf));
    while(*_fmt) {
        if(*_fmt == '%') {
            const char8 formatter = *(_fmt + 1);
            switch(formatter) {
                case 'i':
                    _fmt += 2;

                break;
            }
        }
    }
}

void kprintf(register const char8* _fmt, const void** _args) {
    kcprintf(_fmt, _args, WHITE_ON_BLACK);
}