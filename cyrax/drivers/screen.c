/* (C) Copyright Mario Sieg 2020! */

#include "screen.h"
#include "ports.h"
#include "../kernel/kstd.h"

extern i32 print_char(const char8, i32, i32, char8);

inline i32 get_cursor_offset() {
    port_byte_out(REG_SCREEN_CTRL, 14);
    i32 offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset << 1;
}

inline i32 get_offset(const i32 _col, const i32 _row) { 
    return (_row * MAX_COLS + _col) << 1; 
}

inline i32 get_offset_row(const i32 _offset) { 
    return _offset / (MAX_COLS << 1); 

}

inline i32 get_offset_col(const i32 _offset) { 
    return (_offset - (get_offset_row(_offset) * (MAX_COLS << 1))) >> 1; 
}

inline void set_cursor_offset(i32 _offset) {
    _offset >>= 1;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (u8)(_offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (u8)(_offset & 0xff));
}

inline void clear_screen() {
    i32 screen_size = MAX_COLS * MAX_ROWS;
    volatile char8* vga = (volatile char8*)VIDEO_ADDRESS;
    for (i32 i = 0; i < screen_size; i++) {
        *(vga + (i << 1)) = ' ';
        *(vga + ((i << 1) + 1)) = WHITE_ON_BLACK;
    }
    set_cursor_offset(get_offset(0, 0));
}

void kprint_at(register const char8* _msg, i32 _col, i32 _row, const u8 _color) {
    i32 offset;
    if (_col >= 0 && _row >= 0)
        offset = get_offset(_col, _row);
    else {
        offset = get_cursor_offset();
        _row = get_offset_row(offset);
        _col = get_offset_col(offset);
    }

    while (*_msg) {
        offset = print_char(*_msg++, _col, _row, _color);
        _row = get_offset_row(offset);
        _col = get_offset_col(offset);
    }
}

i32 print_char(const char8 _c, i32 _col, i32 _row, char8 _attr) {
    volatile u8* vga = (volatile u8*)VIDEO_ADDRESS;
    if(!_attr)
        _attr = WHITE_ON_BLACK;

    if (_col >= MAX_COLS || _row >= MAX_ROWS) {
        *(vga + ((MAX_COLS << 1) * (MAX_ROWS) - 2)) = 'E';
        *(vga + ((MAX_COLS << 1) * (MAX_ROWS) - 1)) = RED_ON_WHITE;
        return get_offset(_col, _row);
    }

    i32 offset = _col >= 0 && _row >= 0 ? get_offset(_col, _row) : get_cursor_offset();

    if (_c == '\n') {
        _row = get_offset_row(offset);
        offset = get_offset(0, _row + 1);
    } else {
        *(vga + offset++) = _c;
        *(vga + offset++) = _attr;
    }

    if (offset >= MAX_ROWS * (MAX_COLS << 1)) {
        for (register i32 i = 1; i < MAX_ROWS; i++) 
            kvmemcpy((volatile void*)(get_offset(0, i-1) + VIDEO_ADDRESS), (volatile void*)(get_offset(0, i) + VIDEO_ADDRESS), MAX_COLS << 1);

        register volatile char8* last = (volatile char8*)(get_offset(0, MAX_ROWS-1) + VIDEO_ADDRESS);
        register volatile char8* const end = last + (MAX_COLS << 1) - 1;
        while(end != last)
            *last++ = 0;

        offset -= MAX_COLS << 1;
    }

    set_cursor_offset(offset);
    return offset;
}
