/* (C) Copyright Mario Sieg 2020! */

#include "kstd.hpp"
#include "../drivers/screen.hpp"

auto kmemcpy(void *const _dst, const void *const _src, const size_t _size) -> void* {
    auto* dst = static_cast<uint8_t*>(_dst);
    const auto* src = static_cast<const uint8_t*>(_src);
    const auto* const end = src + _size - 1; 
    while(src != end) {
        *dst++ = *src++;
    }
    return _dst;
}

auto kvmemcpy(volatile void *const _dst, const volatile  void *const _src, const volatile size_t _size) -> volatile void* {
    volatile auto* dst = static_cast<volatile uint8_t*>(_dst);
    volatile const auto* src = static_cast<volatile const uint8_t*>(_src);
    volatile const auto* const end = src + _size - 1; 
    while(src != end)
        *dst++ = *src++;
    return _dst;
}

auto memset(void *const _dst, const uint8_t _value, const size_t _size) -> void* {
    auto* dst = static_cast<uint8_t*>(_dst);
    const auto* end = dst + _size - 1; 
    while(dst != end) {
        *dst++ = _value;
    }
    return _dst;
}

auto kvmemset(volatile void *const _dst, const uint8_t _value, const size_t _size) -> volatile void* {
    volatile auto* dst = static_cast<volatile uint8_t*>(_dst);
    volatile const auto* end = dst + _size - 1; 
    while(dst != end) {
        *dst++ = _value;
    }
    return _dst;
}

void kitoa(int32_t _x, char* _out) {
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