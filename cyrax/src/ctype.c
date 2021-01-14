/* (C) Copyright Mario Sieg 2020! */
/* Part of the CYRAX C Library (clibc)! */

#include "../inc/clibc/ctype.h"

int isalnum(const int _c) {
    return isalpha(_c) || isdigit(_c);
}

int isalpha(const int _c) {
    return isupper(_c) || islower(_c);
}

int isdigit(const int _c) {
    return _c >= '0' && _c <= '9';
}

int isblank(const int _c) {
    return _c == ' ' || _c == '\t';
}

int iscntrl(const int _c) {
    return _c >= 0 && (_c == 0x7F || _c <= 0x1F);
}

int isgraph(const int _c) {
    return _c > 0x20 && _c <= 0x7E;
}

int islower(const int _c) {
    return _c >= 'a' && _c <= 'z';
}

int isprint(const int _c) {
    return _c >= 0x20 && _c <= 0x7E;
}

int ispunct(const int _c) {
    return isprint(_c) && !isspace(_c) && !isalnum(_c);
}

int isspace(const int _c) {
    return _c == ' ' || _c == '\f' || _c == '\n' || _c == '\t' || _c == '\r';
}

int isupper(const int _c) {
    return _c >= 'A' && _c <= 'Z';
}

int isxdigit(const int _c) {
    return  (_c >= '0' && _c <= '9') || 
            (_c >= 'a' && _c <= 'f') ||
            (_c >= 'A' && _c <= 'F');
}

int tolower(const int _c) {
    return _c | ' ';
}

int toupper(const int _c) {
    return _c & ~' ';
}