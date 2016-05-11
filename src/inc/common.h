#ifndef HAVE_DEFINED_COMMON_H
#define HAVE_DEFINED_COMMON_H

#define __x86_32_

#define NULL ((void *)0)

typedef unsigned bool;

#if defined __x86_32_
    typedef unsigned int   uint32;
    typedef signed int     sint32;
    typedef unsigned short uint16;
    typedef signed short   sint16;
    typedef unsigned char  uint8;
    typedef signed char    sint8;
    typedef unsigned int   ptr_t;
#endif

#endif
