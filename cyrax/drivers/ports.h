/* (C) Copyright Mario Sieg 2020! */

#ifndef PORTS_H
#define PORTS_H

#include "../inc/clibc/stdint.h"
#include "../inc/clibc/stddef.h"

extern uint8_t port_byte_in(const uint16_t _port);
extern void port_byte_out(const uint16_t _port, const uint8_t _data);
extern uint16_t port_word_in(const uint16_t _port);
extern void port_word_out(const uint16_t _port, const uint16_t _data);

#endif