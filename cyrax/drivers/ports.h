/* (C) Copyright Mario Sieg 2020! */

#ifndef PORTS_H
#define PORTS_H

#include "../inc/types.h"

extern u8 port_byte_in(const u16 _port);
extern void port_byte_out(const u16 _port, const u8 _data);
extern u16 port_word_in(const u16 _port);
extern void port_word_out(const u16 _port, const u16 _data);

#endif