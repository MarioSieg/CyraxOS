/* (C) Copyright Mario Sieg 2020! */

#include "screen.h"
#include "ports.h"
#include "../kernel/kstd.h"

extern int32_t print_char(const char, int32_t, int32_t, struct vga_color);

inline int32_t get_cursor_offset() {
    port_byte_out(REG_SCREEN_CTRL, 14);
    int32_t offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset << 1;
}

inline int32_t get_offset(const int32_t _col, const int32_t _row) { 
    return (_row * MAX_COLS + _col) << 1; 
}

inline int32_t get_offset_row(const int32_t _offset) { 
    return _offset / (MAX_COLS << 1); 

}

inline int32_t get_offset_col(const int32_t _offset) { 
    return (_offset - (get_offset_row(_offset) * (MAX_COLS << 1))) >> 1; 
}

inline void set_cursor_offset(int32_t _offset) {
    _offset >>= 1;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (uint8_t)(_offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (uint8_t)(_offset & 0xff));
}

inline void clear_screen() {
    int32_t screen_size = MAX_COLS * MAX_ROWS;
    volatile char* vga = (volatile char*)VIDEO_ADDRESS;
    for (int32_t i = 0; i < screen_size; i++) {
        *(vga + (i << 1)) = ' ';
        *(vga + ((i << 1) + 1)) = 0xF;
    }
    set_cursor_offset(get_offset(0, 0));
}

void kprint_at(register const char* _msg, int32_t _col, int32_t _row, const struct vga_color _color) {
    int32_t offset;
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


void kprintn_at(register const char* _msg, int32_t _col, int32_t _row, const struct vga_color _color, const size_t _count) {
    int32_t offset;
    if (_col >= 0 && _row >= 0)
        offset = get_offset(_col, _row);
    else {
        offset = get_cursor_offset();
        _row = get_offset_row(offset);
        _col = get_offset_col(offset);
    }

    for(register size_t i = 0; i < _count && *_msg; ++i) {
        offset = print_char(*_msg++, _col, _row, _color);
        _row = get_offset_row(offset);
        _col = get_offset_col(offset);
    }
}

int32_t print_char(const char _c, int32_t _col, int32_t _row, struct vga_color _attr) {
    volatile uint8_t* vga = (volatile uint8_t*)VIDEO_ADDRESS;
    if(!vga_color_2u8(_attr))
        _attr = DEFAULT_COLOR;

    if (_col >= MAX_COLS || _row >= MAX_ROWS) {
        *(vga + ((MAX_COLS << 1) * (MAX_ROWS) - 2)) = 'E';
        *(vga + ((MAX_COLS << 1) * (MAX_ROWS) - 1)) = vga_color_2u8(ERROR_COLOR);
        return get_offset(_col, _row);
    }

    int32_t offset = _col >= 0 && _row >= 0 ? get_offset(_col, _row) : get_cursor_offset();

    if (_c == '\n') {
        _row = get_offset_row(offset);
        offset = get_offset(0, _row + 1);
    } else {
        *(vga + offset++) = _c;
        *(vga + offset++) = vga_color_2u8(_attr);
    }

    if (offset >= MAX_ROWS * (MAX_COLS << 1)) {
        for (register int32_t i = 1; i < MAX_ROWS; i++) 
            kvmemcpy((volatile void*)(get_offset(0, i-1) + VIDEO_ADDRESS), (volatile void*)(get_offset(0, i) + VIDEO_ADDRESS), MAX_COLS << 1);

        register volatile char* last = (volatile char*)(get_offset(0, MAX_ROWS-1) + VIDEO_ADDRESS);
        register volatile char* const end = last + (MAX_COLS << 1) - 1;
        while(end != last)
            *last++ = 0;

        offset -= MAX_COLS << 1;
    }

    set_cursor_offset(offset);
    return offset;
}

void dump_screen_info() {
    kprint("VIDEO ADDRESS @" STR(VIDEO_ADDRESS) "\n");
    kprint("MAX ROWS " STR(MAX_ROWS) "\n");
    kprint("MAX COLS " STR(MAX_COLS) "\n");
    kprint("IO SCREEN PORT " STR(REG_SCREEN_CTRL) "\n");
    kprint("DATA SCREEN PORT " STR(REG_SCREEN_DATA) "\n");
}