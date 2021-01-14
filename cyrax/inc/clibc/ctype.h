/* (C) Copyright Mario Sieg 2020! */
/* Part of the CYRAX C Library (clibc)! */

#ifndef CTYPE_H
#define CTYPE_H

extern int isalnum(const int _c);
extern int isalpha(const int _c);
extern int isdigit(const int _c);
extern int isblank(const int _c);
extern int iscntrl(const int _c);
extern int isgraph(const int _c);
extern int islower(const int _c);
extern int isprint(const int _c);
extern int ispunct(const int _c);
extern int isspace(const int _c);
extern int isupper(const int _c);
extern int isxdigit(const int _c);
extern int tolower(const int _c);
extern int toupper(const int _c);

#endif