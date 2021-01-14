/* (C) Copyright Mario Sieg 2020! */
/* Part of the CYRAX C Library (clibc)! */

#ifndef STDDEF_H
#define STDDEF_H

typedef signed long         ptrdiff_t;
typedef unsigned long       max_align_t;
typedef unsigned long       size_t;
typedef unsigned short      wchar_t;

#define NULL ((void*)0)
#define offsetof(st, m) ((size_t)((char *)&((st*)0)->m - (char*)0))

#endif