/* (C) Copyright Mario Sieg 2020! */
/* Part of the CYRAX C Library (clibc)! */

#include "../inc/clibc/inttypes.h"
#include "../inc/clibc/errno.h"
#include "../inc/clibc/ctype.h"

/* TODO */
/* Need this because the fucking linker is missing a reference to __divmoddi4! */
static uint64_t udivmoddi4_unchecked(uint64_t dvnd, uint64_t dvsr, uint64_t *rem_ptr) {
    (void)dvnd;
    (void)dvsr;
    (void)rem_ptr;
    return 0;
}

/* TODO */
/* Need this because the fucking linker is missing a reference to __divmoddi4! */
__attribute__((__weak__)) uint64_t __udivmoddi4(uint64_t dvnd, uint64_t dvsr, uint64_t *rem_ptr) {
    uint64_t uquo, urem = 0;
    uquo = udivmoddi4_unchecked(dvnd, dvsr, &urem);
    if(rem_ptr){
        *rem_ptr = urem;
    }
    return uquo;
}

/* TODO */
/* Need this because the fucking linker is missing a reference to __divmoddi4! */
__attribute__((__weak__)) int64_t __divmoddi4(int64_t dvnd, int64_t dvsr, int64_t *rem_ptr) {
    int64_t quo, rem;
    uint64_t uquo, urem = 0;
    if(dvnd >= 0){
        if(dvsr >= 0){
            uquo = udivmoddi4_unchecked((uint64_t)dvnd, (uint64_t)dvsr, &urem);
            quo = (int64_t)uquo;
        } else {
            uquo = udivmoddi4_unchecked((uint64_t)dvnd, (uint64_t)-dvsr, &urem);
            quo = -(int64_t)uquo;
        }
        rem = (int64_t)urem;
    } else {
        if(dvsr >= 0){
            uquo = udivmoddi4_unchecked((uint64_t)-dvnd, (uint64_t)dvsr, &urem);
            quo = -(int64_t)uquo;
        } else {
            uquo = udivmoddi4_unchecked((uint64_t)-dvnd, (uint64_t)-dvsr, &urem);
            quo = (int64_t)uquo;
        }
        rem = -(int64_t)urem;
    }
    if(rem_ptr){
        *rem_ptr = rem;
    }
    return quo;
}


intmax_t imaxabs(const intmax_t _x) {
    return _x >= 0 ? _x : -_x;
}

imaxdiv_t imaxdiv(const intmax_t _numerator, const intmax_t _denominator) {
    imaxdiv_t result;
    result.quotient = _numerator / _denominator;
    result.remainder = _numerator % _denominator;
    return result;
}

intmax_t strtoimax(const char *restrict _ptr, char** const restrict _endptr, const int _base) {
    intmax_t result;
    int sign;

    if (*_ptr == '-') {
        _ptr++;
        sign = -1;
    } else {
        sign = 1;
        if (*_ptr == '+')
            _ptr++;
    }

    result = strtoumax(_ptr, _endptr, _base);

    if (result == (intmax_t)UINTMAX_MAX) {
        errno = ERANGE;
        return sign == -1 ? INTMAX_MIN : INTMAX_MAX;
    }

    return sign * result;
}

uintmax_t strtoumax(const char *restrict _ptr, char** const restrict _endptr, const int _base) {
    uintmax_t result = 0;
    while (isalnum(*_ptr) && ((tolower(*_ptr) - '0') < _base)) {
        if (result > result * _base) {
            errno = ERANGE;
            result = UINTMAX_MAX;
            break;
        }
        result = (*_ptr - '0') + result * _base;
        _ptr++;
    }

    if (_ptr)
        *_endptr = (char*)_ptr;
    return result;
}

intmax_t wcstoimax(const wchar_t *restrict _ptr, wchar_t** const restrict _endptr, const int _base) {
    intmax_t result;
    int sign;
    if (*_ptr == '-') {
        _ptr++;
        sign = -1;
    } else {
        sign = 1;
        if (*_ptr == '+')
            _ptr++;
    }
    result = wcstoumax(_ptr, _endptr, _base);
    if (result == (intmax_t)INTMAX_MAX) {
        errno = ERANGE;
        if (sign == -1)
            return INTMAX_MIN;
        else
            return INTMAX_MAX;
    } else {
        return sign * result;
    }
}

uintmax_t wcstoumax(const wchar_t *restrict _ptr, wchar_t** const restrict _endptr, const int _base) {
    uintmax_t result;
    result = 0;
    while (isalnum(*_ptr) && ((tolower(*_ptr) - '0') < _base)) {
        if (result > result * _base) {
            errno = ERANGE;
            result = UINTMAX_MAX;
            break;
        }
        result = (*_ptr - '0') + result * _base;
        _ptr++;
    }
    if (_endptr)
        *_endptr = (wchar_t*)_ptr;
    return result;
}