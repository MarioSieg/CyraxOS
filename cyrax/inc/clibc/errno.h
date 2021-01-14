/* (C) Copyright Mario Sieg 2020! */
/* Part of the CYRAX C Library (clibc)! */

#ifndef ERRNO_H
#define ERRNO_H

/* Global errno variable. */
extern int errno;

/* TODO */

#define EDOM    20
#define EILSEQ  21
#define ERANGE  22
#define EBADF   23
#define EINVAL  24
#define ENFILE  25
#define ENOENT  26
#define EBUSY   27
#define ENOTDIR 28
#define EXDEV   29
#define ENOMEM  30
#define EAGAIN  31
#define EMLINK  32
#define ECHILD  33

#endif