/* (C) Copyright Mario Sieg 2020! */

#ifndef SCREEN_H
#define SCREEN_H

#include "../inc/types.h"

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f
#define RED_ON_WHITE 0xf4

/* Screen port for IO */
#define REG_SCREEN_CTRL 0x3d4

/* Screen port for data */
#define REG_SCREEN_DATA 0x3d5

/* Clears all text on the screen. */
void clear_screen();

/* Prints text via VGA at the specified position. Formatting is not supported. */
void kprint_at(register const char8* _msg, i32 _col, i32 _row, const u8 _color);

/* Prints text via VGA at the current cursor position. Formatting is not supported. */
static inline void kprint_auto(const char8* const _msg, const u8 _color) {
    kprint_at(_msg, -1, -1, _color);
}

#endif