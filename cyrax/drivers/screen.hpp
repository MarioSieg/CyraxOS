/* (C) Copyright Mario Sieg 2020! */

#ifndef SCREEN_H
#define SCREEN_H

#include "../inc/clibc/stdint.h"
#include "../inc/clibc/stddef.h"

namespace cyrax::drivers::screen {
    /* VGA buffer address */
    static constexpr uintptr_t VIDEO_ADDRESS = 0xb8000;

    static constexpr auto MAX_ROWS = 25;
    static constexpr auto MAX_COLS = 80;

    /* Represents a vga color with a 4-bit foreground and background color. */
    struct vga_color final {
        uint8_t foreground : 4;
        uint8_t background : 4;

        constexpr vga_color() noexcept;

        explicit constexpr vga_color(const uint8_t _scalar) noexcept;

        constexpr vga_color(const uint8_t _foreground, const uint8_t _background) noexcept;

        vga_color(const vga_color&) noexcept = default;

        vga_color(vga_color&&) noexcept = default;

        auto operator=(const vga_color&) noexcept -> vga_color& = default;

        auto operator=(vga_color&&) noexcept -> vga_color& = default;

        ~vga_color() = default;

        constexpr operator uint8_t() const noexcept;

        constexpr operator bool() const noexcept;
    };

    constexpr vga_color::vga_color() noexcept : foreground(0), background(0) {

    }

    constexpr vga_color::vga_color(const uint8_t _scalar) noexcept : foreground(_scalar), background(_scalar << 4) {

    }

    constexpr vga_color::vga_color(const uint8_t _foreground, const uint8_t _background) noexcept : foreground(_foreground), background(_background){

    }

    constexpr vga_color::operator uint8_t() const noexcept {
        union {
            vga_color self;
            uint8_t byte;
        } castor = { *this };
        return castor.byte;
    }

    constexpr vga_color::operator bool() const noexcept {
        return static_cast<uint8_t>(*this);
    }

    /* VGA colors */

    static constexpr auto BLACK         = 0x0;
    static constexpr auto BLUE          = 0x1;
    static constexpr auto GREEN         = 0x2;
    static constexpr auto CYAN          = 0x3;
    static constexpr auto RED           = 0x4;
    static constexpr auto MAGENTA       = 0x5;
    static constexpr auto BROWN         = 0x6;
    static constexpr auto LIGHT_GREY    = 0x7;
    static constexpr auto DARK_GREY     = 0x8;
    static constexpr auto LIGHT_BLUE    = 0x9;
    static constexpr auto LIGHT_GREEN   = 0xA;
    static constexpr auto LIGHT_CYAN    = 0xB;
    static constexpr auto LIGHT_RED     = 0xC;
    static constexpr auto PINK          = 0xD;
    static constexpr auto YELLOW        = 0xE;
    static constexpr auto WHITE         = 0xF;

    static constexpr auto DEFAULT_COLOR = vga_color(WHITE, BLACK);
    static constexpr auto ERROR_COLOR = vga_color(RED, BLACK);

    /* Screen port for IO */
    static constexpr uint16_t REG_SCREEN_CTRL = 0x3D4;

    /* Screen port for data */
    static constexpr uint16_t REG_SCREEN_DATA = 0x3D5;

    /* Prints some screen info. */
    extern void dump_screen_info() noexcept;

    /* Clears all text on the screen. */
    extern void clear_screen() noexcept;

    /* Prints text via VGA at the specified position. Formatting is not supported. */
    extern void kprint_at(const char* _msg, int32_t _col, int32_t _row, const vga_color _color) noexcept;

    /* Prints text via VGA at the specified position. Formatting is not supported. Only prints the count specified. */
    extern void kprintn_at(const char* _msg, int32_t _col, int32_t _row, const vga_color _color, const size_t _count) noexcept;

    /* Prints text via VGA at the current cursor position. Formatting is not supported. Only prints the count specified.  */
    static inline void kprintn(const char* const _msg, const vga_color _color, const size_t _count) {
        kprintn_at(_msg, -1, -1, _color, _count);
    }

    /* Prints text via VGA at the current cursor position. Formatting is not supported. */
    static inline void kcprint(const char* const _msg, const vga_color _color) noexcept {
        kprint_at(_msg, -1, -1, _color);
    }

    static inline void kprint(const char* const _msg) noexcept {
        kprint_at(_msg, -1, -1, DEFAULT_COLOR);
    }

}

#endif