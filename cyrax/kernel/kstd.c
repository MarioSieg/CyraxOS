/* (C) Copyright Mario Sieg 2020! */

#include "kstd.h"
#include "../drivers/screen.h"

void* kmemcpy(void *const _dst, const void *const _src, const size_t _size) {
    register uint8_t* dst = (uint8_t*)dst;
    register const uint8_t* src = (const uint8_t*)_src;
    register const uint8_t* end = src + _size - 1; 
    while(src != end) {
        *dst++ = *src++;
    }
    return _dst;
}

volatile void* kvmemcpy(volatile void *const _dst, const volatile  void *const _src, const volatile size_t _size) {
    register volatile uint8_t* dst = (uint8_t*)dst;
    register volatile const uint8_t* src = (const uint8_t*)_src;
    register volatile const uint8_t* end = src + _size - 1; 
    while(src != end)
        *dst++ = *src++;
    return _dst;
}

void* kmemset(void *const _dst, const uint8_t _value, const size_t _size) {
    register uint8_t* dst = (uint8_t*)dst;
    register const uint8_t* end = dst +  _size - 1; 
    while(dst != end) {
        *dst++ = _value;
    }
    return _dst;
}

volatile void* kvmemset(volatile void *const _dst, const uint8_t _value, const size_t _size) {
    register volatile uint8_t* dst = (uint8_t*)dst;
    register volatile const uint8_t* end = dst +  _size - 1; 
    while(dst != end) {
        *dst++ = _value;
    }
    return _dst;
}

void kitoa(register int32_t _x, register char* _out) {
    int32_t sign;
    if ((sign = _x) < 0) 
        _x = -_x;
    do
        *_out++ = _x % 10 + '0';
    while ((_x /= 10) > 0);
    if (sign < 0) 
        *_out++ = '-';
    *_out = '\0';
}