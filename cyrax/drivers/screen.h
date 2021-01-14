/* (C) Copyright Mario Sieg 2020! */

#ifndef SCREEN_H
#define SCREEN_H

#include "../inc/clibc/stdint.h"
#include "../inc/clibc/stddef.h"

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

#define BLACK 0x0
#define BLUE 0x1
#define GREEN 0x2
#define CYAN 0x3
#define RED 0x4
#define MAGENTA 0x5
#define BROWN 0x6
#define LIGHT_GREY 0x7
#define DARK_GREY 0x8
#define LIGHT_BLUE 0x9
#define LIGHT_GREEN 0xA
#define LIGHT_CYAN 0xB
#define LIGHT_RED 0xC
#define PINK 0xD
#define YELLOW 0xE
#define WHITE 0x0F

#define ERROR_COLOR vga_color(RED, BLACK)
#define DEFAULT_COLOR vga_color(LIGHT_GREY, BLACK)

/* Represents a vga color with a 4-bit foreground and background color. */
struct vga_color {
    uint8_t foreground : 4;
    uint8_t background : 4;
};

static inline struct vga_color vga_color(const uint8_t _foreground, const uint8_t _background) {
    struct vga_color result = {
        .foreground = _foreground,
        .background = _background
    };
    return result;
}

static inline uint8_t vga_color_2u8(const struct vga_color _color) {
    union {
        struct vga_color color;
        uint8_t byte;
    } castor = {
        .color = _color
    };
    return castor.byte;
}

/* Screen port for IO */
#define REG_SCREEN_CTRL 0x3d4

/* Screen port for data */
#define REG_SCREEN_DATA 0x3d5

/* Prints some screen info. */
void dump_screen_info();

/* Clears all text on the screen. */
void clear_screen();

/* Prints text via VGA at the specified position. Formatting is not supported. */
void kprint_at(register const char* _msg, int32_t _col, int32_t _row, const struct vga_color _color);

/* Prints text via VGA at the specified position. Formatting is not supported. Only prints the count specified. */
void kprintn_at(register const char* _msg, int32_t _col, int32_t _row, const struct vga_color _color, const size_t _count);

/* Prints text via VGA at the current cursor position. Formatting is not supported. Only prints the count specified.  */
static inline void kprintn(const char* const _msg, const struct vga_color _color, const size_t _count) {
    kprintn_at(_msg, -1, -1, _color, _count);
}

/* Prints text via VGA at the current cursor position. Formatting is not supported. */
static inline void kcprint(const char* const _msg, const struct vga_color _color) {
    kprint_at(_msg, -1, -1, _color);
}

static inline void kprint(const char* const _msg) {
    kprint_at(_msg, -1, -1, DEFAULT_COLOR);
}

#endif