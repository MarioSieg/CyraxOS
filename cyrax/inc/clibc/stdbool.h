/* (C) Copyright Mario Sieg 2020! */
/* Part of the CYRAX C Library (clibc)! */

#ifndef STDBOOL_H
#define STDBOOL_H

/* CCC does not have support for _Bool at the moment. */
typedef unsigned char bool;

#define true 1
#define false 0

#define __bool_true_false_are_defined 1

#endif